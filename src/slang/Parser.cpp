#include "slang/Parser.hpp"

namespace slang {
    using namespace std;

    Parser::Parser(Lexer& lexer)
            : m_lexer(lexer)
            {}

    bool Parser::hasNext() {
        return m_lexer.hasNext();
    }

    unique_ptr<Lexem> Parser::skipWhitespaces() {
        unique_ptr<Lexem> lex = m_lexer.next();
        while (m_lexer.hasNext() && lex->type == LexemType::WS) {
            lex = m_lexer.next();
        }
        return lex;
    }

    template<typename Collection>
    unique_ptr<Expression::Base> Parser::nextCollection(LexemType delim) {
        vector<Expression::Base*> acc;
        while (m_lexer.hasNext()) {
            auto lex = m_lexer.next();
            if (lex->type == delim) {
                break;
            }

            acc.push_back(next(move(lex)).release());
        }
        return unique_ptr<Expression::Base>(new Collection(acc));
    }

    unique_ptr<Expression::Base> Parser::nextStr(LexemType delim) {
        string acc;
        while (m_lexer.hasNext()) {
            shared_ptr<Lexem> lex = m_lexer.next();
            if (lex->type == delim) {
                break;
            }
            if (lex->type != LexemType::ATOM) {
                throw "invalid";
            }
            shared_ptr<AtomLexem> atom = dynamic_pointer_cast<AtomLexem>(lex);
            acc.append(*atom->value);
        }

        return unique_ptr<Expression::Base>(new Expression::Str(acc));
    }

    bool tryFloat(const string& value, unique_ptr<Expression::Base>& out) {
        bool floating = false;
        for (char ch : value) {
            if (ch < '0' || ch > '9') {
                if (ch != '.') {
                    return false;
                }
            }
            if (ch == '.') {
                if (floating) {
                    return false;
                }
                floating = true;
            }
        }

        if (!floating) {
            return false;
        }

        auto num = Expression::_priv::parseF64(value);
        out = unique_ptr<Expression::Base>(new Expression::Float(num));
        return true;
    }

    bool tryInteger(const string& value, unique_ptr<Expression::Base>& out) {
        for (char ch : value) {
            if (ch < '0' || ch > '9') {
                return false;
            }
        }

        auto num = Expression::_priv::parseI64(value);
        out = unique_ptr<Expression::Base>(new Expression::Integer(num));
        return true;
    }

    unique_ptr<Expression::Base> Parser::coerce(const string &value) {
        unique_ptr<Expression::Base> res;

        if (tryFloat(value, res)) {
            return res;
        } else if (tryInteger(value, res)) {
            return res;
        }
        return unique_ptr<Expression::Base>(new Expression::Atom(value));
    }

    unique_ptr<Expression::Base> Parser::next() {
        return next(m_lexer.next());
    }

    unique_ptr<Expression::Base> Parser::next(unique_ptr<Lexem> lex) {
        switch (lex->type) {
            case LexemType::ATOM:
            {
                auto atom = dynamic_cast<AtomLexem*>(lex.get());
                return coerce(*atom->value);
            }

            case LexemType::START_LIST:
                return nextCollection<Expression::List>(LexemType::END_LIST);

            case LexemType::START_VEC:
                return nextCollection<Expression::Vec>(LexemType::END_VEC);

            case LexemType::START_SET:
                return nextCollection<Expression::Set>(LexemType::END_SET);

            case LexemType::SINGLE_QUOTE:
            case LexemType::DOUBLE_QUOTE:
                return nextStr(lex->type);

            case LexemType::WS:
            {
                return next(skipWhitespaces());
            }

            case LexemType::END_OF_FILE:
                return unique_ptr<Expression::Base>(new Expression::Base(Expression::Type::END_OF_FILE));

            default:
                throw "should not happen";
        }
    }
};

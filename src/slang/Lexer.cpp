#include "slang/Lexer.hpp"

namespace slang {
    using namespace std;

    Lexer::Lexer(istream &input)
            : m_input(input), m_line(0), m_column(0), m_scanning(false), m_scanned(false), m_delim(0) { }

    bool Lexer::hasNext() const {
        return !m_input.eof() || !m_input.fail();
    }

    LexemPtr Lexer::next() {
        if (m_scanning && !m_scanned) {
            m_scanned = true;
            return scanString(m_delim);
        }

        char c;
        if (!m_input.get(c)) {
            return makeLexem(LexemType::END_OF_FILE);
        }

        LexemPtr lex;
        switch (c) {
            case '(':
                return makeLexem(LexemType::START_LIST);
            case ')':
                return makeLexem(LexemType::END_LIST);

            case '[':
                return makeLexem(LexemType::START_VEC);
            case ']':
                return makeLexem(LexemType::END_VEC);

            case '{':
                return makeLexem(LexemType::START_SET);
            case '}':
                return makeLexem(LexemType::END_SET);

            case '\n':
                lex = makeLexem(LexemType::WS);
                m_line++;
                m_column = 0;
                return lex;

            case ' ':
                return makeLexem(LexemType::WS);

            case '"':
                m_scanning = !m_scanned;
                m_scanned = false;
                m_delim = c;
                return makeLexem(LexemType::DOUBLE_QUOTE);

            case '\'':
                m_scanning = !m_scanned;
                m_scanned = false;
                m_delim = c;
                return makeLexem(LexemType::SINGLE_QUOTE);

            default:
                m_input.putback(c);
                return scanAtom();
        }
    }

    LexemPtr Lexer::makeLexem(const LexemType type) {
        auto lex = LexemPtr(new Lexem(m_line, m_column, type));
        m_column += 1;
        return lex;
    }

    LexemPtr Lexer::makeLexem(const string *value) {
        auto lex = LexemPtr(new AtomLexem(value, m_line, m_column));
        m_column += value->size();
        return lex;
    }

    LexemPtr Lexer::scanString(char delim) {
        string *acc = new string;

        char c;
        bool escape = false;
        while (m_input.get(c)) {
            if (escape) {
                acc->push_back(c);
                escape = false;
            } else {
                if (c == delim) {
                    m_input.putback(delim);
                    break;
                } else if (c == '\\') {
                    escape = true;
                } else {
                    acc->push_back(c);
                }
            }
        }

        return makeLexem(acc);
    }

    LexemPtr Lexer::scanAtom() {
        string *acc = new string;

        char c;
        bool scanning = true;
        while (scanning && m_input.get(c)) {
            switch (c) {
                case ')':
                case '}':
                case ']':
                case '\n':
                case ' ':
                    m_input.putback(c);
                    scanning = false;
                    break;

                default:
                    acc->push_back(c);
                    break;
            }
        }

        return makeLexem(acc);
    }
};

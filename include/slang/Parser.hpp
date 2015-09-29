#ifndef SLANG_PARSER_HPP
#define SLANG_PARSER_HPP

#include <memory>

#include "slang/Lexer.hpp"
#include "slang/Expression.hpp"

namespace slang {
    class Parser {
    public:
        Parser(Lexer& lexer);

        bool hasNext();
        std::unique_ptr<Expression::Base> next();

    private:
        std::unique_ptr<Lexem> skipWhitespaces();
        std::unique_ptr<Expression::Base> next(std::unique_ptr<Lexem> lex);
        template<typename Collection>
        std::unique_ptr<Expression::Base> nextCollection(LexemType delim);
        std::unique_ptr<Expression::Base> nextStr(LexemType delim);
        std::unique_ptr<Expression::Base> coerce(const std::string& value);

        Lexer& m_lexer;
    };
};


#endif//SLANG_PARSER_HPP

#ifndef SLANG_LEXER_HPP
#define SLANG_LEXER_HPP

#include <istream>
#include <string>
#include <memory>
#include <iostream>

namespace slang {
    enum class LexemType {
        START_LIST,
        END_LIST,
        START_VEC,
        END_VEC,
        START_SET,
        END_SET,
        SINGLE_QUOTE,
        DOUBLE_QUOTE,
        WS,
        END_OF_FILE,
        ATOM,
    };

    class Lexem {
    public:
        const unsigned int line;
        const unsigned int column;
        const LexemType type;

        Lexem(const unsigned int line, const unsigned int column, const LexemType type)
                : line(line), column(column), type(type) { }

        virtual ~Lexem() { }
    };

    class AtomLexem : public Lexem {
    public:
        const std::string *value;

        AtomLexem(const std::string *value, const unsigned int line, const unsigned int column)
                : Lexem(line, column, LexemType::ATOM), value(value) { }

        virtual ~AtomLexem() {
            delete value;
        }
    };

    typedef std::unique_ptr<Lexem> LexemPtr;

    class Lexer {
    public:
        Lexer(std::istream &);

        bool hasNext() const;

        LexemPtr next();

    private:
        LexemPtr makeLexem(LexemType type);
        LexemPtr makeLexem(const std::string *value);

        LexemPtr scanString(char delim);
        LexemPtr scanAtom();

        std::istream &m_input;

        unsigned int m_line;
        unsigned int m_column;

        bool m_scanning, m_scanned;
        char m_delim;
    };
};

#endif//SLANG_LEXER_HPP

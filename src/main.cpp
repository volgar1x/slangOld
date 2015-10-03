#include <iostream>
#include <sstream>

#include "slang/Lexer.hpp"
#include "slang/Parser.hpp"
#include "slang/Interpreter.hpp"

using namespace std;

void printLexer(slang::Lexer &);
void printLexem(const slang::Lexem &);

void printExpression(const slang::Expression::Base &);

int main(int, char **) {
    string program("(hello \"world\")\n"
                   "(bonjour \"monde\")\n"
                   "(puts \"you can use single quotes ' in double quotes \\\" strings \")\n"
                   "(puts 'you can use double quotes \" in single quotes \\' strings ')\n"
                   "(+ (* 1 2) 3)\n"
                   "(* \"abcd\" 3)\n"
                   "(sqrt 3.14)\n"
                   "[1 2 3]\n"
                   "{1 2 3}");

    istringstream input(program);

    slang::Lexer lexer(input);
//    printLexer(lexer);
    try {
        slang::Parser parser(lexer);
        while (parser.hasNext()) {
            shared_ptr<slang::Expression::Base> expression = parser.next();
            if (expression->type == slang::Expression::Type::END_OF_FILE) {
                break;
            }

            auto result = slang::Interpreter::interpret(expression);

            printExpression(*expression);
            cout << endl;

            cout << " => ";
            printExpression(*result);
            cout << endl;
        }
    } catch (const char* reason) {
        cout << "ERR: " << reason << endl;
    }

    return 0;
}

void printLexer(slang::Lexer &lexer) {
    while (lexer.hasNext()) {
        unique_ptr<slang::Lexem> lex = lexer.next();
        printLexem(*lex);
    }
}

void printLexem(const slang::Lexem &lex) {
    switch (lex.type) {
        case slang::LexemType::WS:
            cout << "WS:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::DOUBLE_QUOTE:
            cout << "DOUBLE_QUOTE:" << lex.line << ":" << lex.column << endl;
            break;
        case slang::LexemType::SINGLE_QUOTE:
            cout << "SINGLE_QUOTE:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::START_LIST:
            cout << "START_LIST:" << lex.line << ":" << lex.column << endl;
            break;
        case slang::LexemType::END_LIST:
            cout << "END_LIST:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::START_VEC:
            cout << "START_VEC:" << lex.line << ":" << lex.column << endl;
            break;
        case slang::LexemType::END_VEC:
            cout << "END_VEC:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::START_SET:
            cout << "START_SET:" << lex.line << ":" << lex.column << endl;
            break;
        case slang::LexemType::END_SET:
            cout << "END_SET:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::END_OF_FILE:
            cout << "EOF:" << lex.line << ":" << lex.column << endl;
            break;

        case slang::LexemType::ATOM:
        {
            const slang::AtomLexem& atom = static_cast<const slang::AtomLexem&>(lex);
            cout << "ATOM(" << *atom.value << "):" << lex.line << ":" << lex.column << endl;
        }
            break;
    }
}

void printExpression(const slang::Expression::Base &base) {
    switch (base.type) {
        case slang::Expression::Type::LIST:
        case slang::Expression::Type::SET:
        case slang::Expression::Type::VEC:
        {
            auto list = static_cast<const slang::Expression::Collection&>(base);
            switch (base.type) {
                case slang::Expression::Type::LIST:
                    cout << "(";
                    break;
                case slang::Expression::Type::SET:
                    cout << "{";
                    break;
                case slang::Expression::Type::VEC:
                    cout << "[";
                    break;
                default:
                    throw "impossible";
            }
            bool first = true;
            for (auto expression : list.expressions) {
                if (first) first = false;
                else cout << " ";
                printExpression(*expression);
            }
            switch (base.type) {
                case slang::Expression::Type::LIST:
                    cout << ")";
                    break;
                case slang::Expression::Type::SET:
                    cout << "}";
                    break;
                case slang::Expression::Type::VEC:
                    cout << "]";
                    break;
                default:
                    throw "impossible";
            }
        }
        break;

        case slang::Expression::Type::ATOM:
        {
            auto atom = static_cast<const slang::Expression::Atom&>(base);
            cout << atom.value;
        }
        break;

        case slang::Expression::Type::STR:
        {
            auto str = static_cast<const slang::Expression::Str&>(base);
            cout << '"' << str.value << '"';
        }
        break;

        case slang::Expression::Type::INTEGER:
        {
            auto num = static_cast<const slang::Expression::Integer&>(base);
            cout << num.value;
        }
        break;

        case slang::Expression::Type::FLOAT:
        {
            auto num = static_cast<const slang::Expression::Float&>(base);
            cout << num.value;
        }
        break;

        default:
            throw "todo printExpression";
    }
}

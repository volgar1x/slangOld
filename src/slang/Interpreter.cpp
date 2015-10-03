#include "slang/Interpreter.hpp"

namespace slang {
namespace Interpreter {
    using namespace std;

    shared_ptr<Expression::Base> interpret(shared_ptr<Expression::Base> expression) {
        switch (expression->type) {
            case Expression::Type::LIST:
            {
                auto list = static_pointer_cast<Expression::List>(expression);
                auto arguments = list->expressions;

                auto funExpression = *arguments.erase(arguments.begin());
                if (funExpression->type != Expression::Type::ATOM) {
                    return expression;
                }
                auto fun = static_cast<Expression::Atom*>(funExpression)->value;
                delete funExpression;

                return Interpreter::call(fun, arguments);
            }

            default:
                return expression;
        }
    }

    shared_ptr<Expression::Base> call(const string& fun, const vector<Expression::Base*>& args) {
        if (fun == "+") {
            Expression::_priv::i64 acc = 0;
            for (auto arg : args) {
                auto evalArg = interpret(arg);
                auto integer = static_cast<Expression::Integer*>(evalArg);
                acc += integer->value;
            }
            return shared_ptr<Expression::Base>(new Expression::Integer(acc));
        } else if (fun == '*') {
            Expression::_priv::i64 acc = args.at(0);
            for (auto arg : args) {
                auto evalArg = interpret(arg);
                auto integer = static_cast<Expression::Integer*>(evalArg);
                acc += integer->value;
            }
            return shared_ptr<Expression::Base>(new Expression::Integer(acc));
        }
        return shared_ptr<Expression::Base>(nullptr);
    }
}
}

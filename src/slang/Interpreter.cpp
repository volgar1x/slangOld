#include "slang/Interpreter.hpp"

namespace slang {
namespace Interpreter {
    using namespace std;

    unique_ptr<Expression::Base> interpret(const Expression::Base& expression) {
        switch (expression.type) {
            case Expression::Type::LIST:
            {
                auto list = static_cast<const Expression::List&>(expression);
                auto arguments = list.expressions;

                auto funExpression = unique_ptr<Expression::Base>(*arguments.erase(arguments.begin()));
                if (funExpression->type != Expression::Type::ATOM) {
                    return unique_ptr<Expression::Base>(move(expression));
                }
                auto fun = static_cast<Expression::Atom*>(funExpression.get())->value;

                return Interpreter::call(fun, arguments);
            }

            default:
                return unique_ptr<Expression::Base>(move(expression));
        }
    }

    unique_ptr<Expression::Base> call(const string& fun, const vector<Expression::Base*>& args) {
        return unique_ptr<Expression::Base>(nullptr);
    }
}
}
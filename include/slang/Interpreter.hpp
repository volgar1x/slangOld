#ifndef SLANG_INTERPRETER_HPP
#define SLANG_INTERPRETER_HPP

#include <memory>
#include <string>
#include <vector>

#include "slang/Expression.hpp"

namespace slang {
namespace Interpreter {
    std::shared_ptr<Expression::Base> interpret(std::shared_ptr<Expression::Base>);

    std::shared_ptr<Expression::Base> call(const std::string& fun, const std::vector<Expression::Base*>& args);
}
}

#endif //SLANG_INTERPRETER_HPP

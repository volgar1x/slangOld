#ifndef SLANG_STR_HPP
#define SLANG_STR_HPP

#include "slang/Expression/Base.hpp"

namespace slang {
namespace Expression {
    class Str : public Base {
    public:
        Str(const std::string value)
                : Base(Type::STR), value(value)
                {}

        const std::string value;
    };
}
}

#endif//SLANG_STR_HPP

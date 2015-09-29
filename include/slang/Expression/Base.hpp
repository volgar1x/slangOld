#ifndef SLANG_BASE_HPP
#define SLANG_BASE_HPP

#include "slang/Expression/Type.hpp"

namespace slang {
namespace Expression {

    class Base {
    public:
        Base(Type type) : type(type) {}
        virtual ~Base() {}

        const Type type;

    private:
    };

    const Base END_OF_FILE(Type::END_OF_FILE);

};
};

#endif //SLANG_BASE_HPP

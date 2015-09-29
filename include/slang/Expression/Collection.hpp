#ifndef SLANG_COLLECTION_HPP
#define SLANG_COLLECTION_HPP

#include "slang/Expression/Base.hpp"
#include <vector>

namespace slang {
namespace Expression {
    class Collection : public Base {
    public:
        typedef std::vector<Base*> Col;

        Collection(Type type, Col expressions)
                : Base(type), expressions(expressions)
                {}

        const Col expressions;
    };

    class List : public Collection {
    public:
        List(Col expressions)
                : Collection(Type::LIST, expressions)
                {}
    };

    class Vec : public Collection {
    public:
        Vec(Col expressions)
                : Collection(Type::VEC, expressions)
        {}
    };

    class Set : public Collection {
    public:
        Set(Col expressions)
                : Collection(Type::SET, expressions)
        {}
    };
}
}

#endif//SLANG_COLLECTION_HPP

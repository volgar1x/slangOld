#ifndef SLANG_ATOM_HTTP
#define SLANG_ATOM_HTTP

#include "slang/Expression/Base.hpp"

namespace slang {
    namespace Expression {
        class Atom : public Base {
        public:
            Atom(const std::string value)
                    : Base(Type::ATOM), value(value)
            {}

            const std::string value;
        };

        const Atom NIL("nil"), TRUE("true"), FALSE("false");
    }
}

#endif//SLANG_ATOM_HTTP

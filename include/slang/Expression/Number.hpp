#ifndef SLANG_NUMBER_HPP
#define SLANG_NUMBER_HPP

#include "slang/Expression/Base.hpp"

namespace slang {
    namespace Expression {
        namespace _priv {
            typedef long long i64;
            typedef double f64;
        }

        class Integer : public Base {
        public:
            Integer(_priv::i64 value)
                    : Base(Type::INTEGER), value(value)
                    {}

            const _priv::i64 value;
        };

        class Float : public Base {
        public:
            Float(_priv::f64 value)
                    : Base(Type::INTEGER), value(value)
                    {}

            const _priv::f64 value;
        };
    }
}

#endif//SLANG_NUMBER_HPP

#ifndef SLANG_NUMBER_HPP
#define SLANG_NUMBER_HPP

#include "slang/Expression/Base.hpp"

namespace slang {
    namespace Expression {
        namespace _priv {
            typedef long long i64;
            typedef double f64;

            static inline i64 parseI64(const std::string& s) { return std::stoll(s); }
            static inline f64 parseF64(const std::string& s) { return std::stod(s); }
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
                    : Base(Type::FLOAT), value(value)
                    {}

            const _priv::f64 value;
        };
    }
}

#endif//SLANG_NUMBER_HPP

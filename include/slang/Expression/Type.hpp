#ifndef SLANG_TYPE_HPP
#define SLANG_TYPE_HPP

namespace slang {
namespace Expression {
    enum class Type {
        END_OF_FILE,
        LIST,
        SET,
        VEC,
        INTEGER,
        FLOAT,
        ATOM,
        STR,
    };
}
}

#endif//SLANG_TYPE_HPP

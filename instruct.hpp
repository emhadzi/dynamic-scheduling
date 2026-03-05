#pragma once
#include <cstdint>
#include <variant>

enum class Opcode {
    ADD, SUB, MULT, DIV, LOAD, STORE, JUMP, CMP
};

// The sizes are not standard but should be enough
struct R_args {
    uint16_t rs, rt, rd;
};
struct I_args {
    uint16_t rs, rt;
    uint32_t imm;
};
struct J_args {
    uint64_t imm;
};

struct Instruction {
    Opcode opcode;
    std::variant<R_args, I_args, J_args> args;
};

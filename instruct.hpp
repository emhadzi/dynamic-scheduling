#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

class FuncUnit;

struct Instruction_type {
    std::string name;
    // Vector to acceptable functional units for this instruction
    std::vector <FuncUnit*> goodUnits;
};

struct Instruction {
    Instruction_type *type;
};

// The sizes are not standard but should be enough

struct R_instruction : public Instruction {
    uint16_t rs;
    uint16_t rt;
    uint16_t rd;
};

struct I_instruction : public Instruction {
    uint16_t rs;
    uint16_t rt;
    uint32_t imm;
};

struct J_instruction : public Instruction {
    uint64_t imm;
};

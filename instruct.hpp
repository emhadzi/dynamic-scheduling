#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

class Instruction_type {
    std::string name;
    // Vector to acceptable functional units for this instruction
    std::vector <FuncUnit*> goodUnits;
};

class Instruction {
    Instruction_type *type;
};

// The sizes are not standard but should be enough

class R_instruction : Instruction {
    uint16_t rs;
    uint16_t rt;
    uint16_t rd;
};

class I_instruction : Instruction {
    uint16_t rs;
    uint16_t rt;
    uint32_t imm;
};

class J_instruction : Instruction {
    uint64_t imm;
};

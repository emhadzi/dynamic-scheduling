#include "cpu.hpp"

struct ALU : FuncUnit {
    inline static std::unordered_map <Opcode, uint16_t> compTime{{Opcode::ADD, 2}, {Opcode::SUB, 2}, {Opcode::MULT, 4}, {Opcode::DIV, 20}};

    int16_t getCompTime(Opcode op) const override {
        auto it = compTime.find(op);
        if (it == compTime.end())
            return -1;
        return it->second;
    }
};

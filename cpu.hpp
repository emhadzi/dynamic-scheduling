#pragma once

#include <cstdint>
#include <memory>
#include "instruct.hpp"

class CPU;

class FuncUnit {
    std::string name;
    virtual void apply(CPU&, const Instruction&);
};

class RegisterFile {

};

class Memory {
private:
    uint64_t sz;
    std::unique_ptr <uint8_t[]> mem;
public:
    Memory(uint64_t sz) : sz(sz), mem(std::make_unique<uint8_t[]>(sz)) {}

    uint8_t getByte(uint64_t x) {
        if (x >= sz)
            throw std::out_of_range("[MEMORY] Out of bounds");
        return mem[x];
    }

    void setByte(uint64_t x, uint8_t val) {
        if (x >= sz)
            throw std::out_of_range("[MEMORY] Out of bounds");
        mem[x] = val;
    }
};

class CPU {
private:
    RegisterFile rf;
    Memory mem;
    vector <FuncUnit> funcUnits;
public:
    inline virtual void push_func(FuncUnit&& fu) {
        funcUnits.push_back(fu);
    };
    virtual void push(const Instruction&) = 0;
    virtual void run() = 0;
    virtual uint64_t getRegister() = 0;
};

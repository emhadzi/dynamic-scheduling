#pragma once

#include <cstdint>
#include <memory>
#include "instruct.hpp"

class CPU;

class FuncUnit {
    std::string name;
    virtual void apply(CPU&, const Instruction&);
};

template <typename T>
class RegisterFile {
private:
    std::vector <T> regVal;
public:
    RegisterFile(int rn) : regVal(rn) {}
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
    std::unique_ptr <Memory> mem;
    std::unique_ptr <RegisterFile <int64_t>> rf; // This can be changed!
    std::vector <std::unique_ptr<FuncUnit>> funcUnits;
public:
    CPU(std::unique_ptr<Memory> mem, std::unique_ptr<RegisterFile <int64_t>> rf, std::vector <std::unique_ptr<FuncUnit>>&& funcUnits)
        : rf(std::move(rf)), mem(std::move(mem)), funcUnits(std::move(funcUnits)) {}
    virtual void push(const Instruction&) = 0;
    virtual void run() = 0;
    virtual uint64_t getRegister() = 0;
};

#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include "instruct.hpp"
#include <unordered_map>

class CPU;

struct FuncUnit {
    bool busy;
    Opcode curOp;
    // Source and destination registers
    int16_t fj, fk, fi;
    std::string name;
    // How much time it takes to complete each available operation (which index of the program it is executing)
    std::vector <std::size_t> job;

    virtual int16_t getCompTime(Opcode op) const = 0;
    virtual void apply(CPU&, const Instruction&);
};

template <typename T>
class RegisterFile {
private:
    std::vector <T> regVal;
    std::vector <bool> writeLock;
public:
    RegisterFile(size_t rn) : regVal(rn), writeLock(rn) {}
    bool isLocked(uint16_t reg) {
        return writeLock[reg];
    }
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
protected:
    uint64_t t;
    size_t pc;
    std::unique_ptr <Memory> mem;
    std::unique_ptr <RegisterFile <uint64_t>> rf; // This can be changed!
    std::vector <std::unique_ptr<FuncUnit>> funcUnits;
    std::vector <Instruction> program;
public:
    CPU(std::unique_ptr<Memory> mem, std::unique_ptr<RegisterFile <uint64_t>> rf, std::vector <std::unique_ptr<FuncUnit>>&& funcUnits)
        : rf(std::move(rf)), mem(std::move(mem)), funcUnits(std::move(funcUnits)), t(0), pc(0) {}
    virtual void push(const Instruction&) = 0;
    virtual void run() = 0;
    virtual uint64_t getRegister() = 0;
};

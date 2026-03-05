#include "cpu.hpp"

class Scoreboard : public CPU {
    enum class InstrState {
        ISSUE, READ, EXEC, WRITE
    };

    std::vector <InstrState> iState;

    std::pair <bool, uint16_t> getDest(const Instruction& instr) {
        if (const R_args* r = std::get_if<R_args>(&instr.args))
            return {true, r->rd};
        else if (const I_args* i = std::get_if<I_args>(&instr.args))
            return {true, i->rt};
        return {false, 0};
    }

    void tick() {
        // ==========================================
        //                  ISSUE
        // ==========================================
        // See if program[pc] can be dispatched
        Instruction& curInstr = program[pc];

        // 1. Is there WAW hazard
        auto [hasDest, dest] = getDest(curInstr);

        if (hasDest && rf->isLocked(dest))
            return; // Stall

        // 2. Is there a FU that can perform the instruction?
        FuncUnit *candFu = nullptr;
        for (const auto& fu : funcUnits) {
            if (!fu->busy && fu->getCompTime(curInstr.opcode) != -1)
                candFu = fu.get();
        }

        if (!candFu)
            return; // Stall
    }

public:
    void run() override {
        while (pc < program.size()) {
            tick();
            t++;
        }
    }
};

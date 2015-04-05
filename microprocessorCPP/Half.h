#include "Chip8005.h"

void half(Chip8005* chip) {
    //get number -> R0
    //minus 2 at a time -> R0
    //add 1 at same time -> R1
    //check R0 == 0 -> load R1 -> chip.memory[1] -> finish
    //else repeat
    chip->MarkAddress("HalfIn", 250);
    chip->MarkAddress("HalfOut", 251);

    chip->LoadAddrToR0("HalfIn");

    chip->MarkNext("Minus");
    chip->MinusR0();
    chip->MinusR0();
    chip->AddR1();
    chip->jumpIfR0Not0("Minus");

    chip->LoadR1ToAddr("HalfOut");
    chip->LoadAddrToR0("HalfOut");
    chip->printR0();
}

void runHalf() {
    runHalf();
    Chip8005 chip;
    chip.Reset();

    //tests
    chip.SetAddrToVal(250, 10);
    half(&chip);
    chip.Interpret(); //as in interpret the code written to the memory
    chip.PrintOut();

    chip.Reset();
    chip.SetAddrToVal(250, 200);
    half(&chip);
    chip.Interpret();
    chip.PrintOut();

    chip.Reset();
    chip.SetAddrToVal(250, 254);
    half(&chip);
    chip.Interpret();
    chip.PrintOut();

    chip.Reset();
    chip.SetAddrToVal(250, 2);
    half(&chip);
    chip.Interpret();
    chip.PrintOut();
}
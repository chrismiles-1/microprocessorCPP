#include <iostream>
#include <stdlib.h>

#include "Chip8005.h"
//#include "Half.h"

void half(Chip8005* chip);
void isEven(Chip8005* chip);
void wondrousSequence(Chip8005* chip);
void runWondrous();
void markAddresses(Chip8005* chip);

int main() {
    Chip8005 chip;

    //test individual functions
    //half()
    markAddresses(&chip);
    chip.SetAddrToVal(250, 10);
    half(&chip);
    chip.LoadAddrToR0("halfOut");
    chip.printR0();
    chip.Interpret();
    chip.PrintOut();

    chip.Reset();
    //isEven()
    markAddresses(&chip);
    chip.SetAddrToVal(240, 10);
    isEven(&chip);
    chip.LoadAddrToR0("halfOut");
    chip.printR0();
    chip.Interpret();
    chip.PrintOut();

    chip.Reset();
    //nextTerm()

    int n;
    std::cin >> n; //get a user input before terminate, makes it easier to code on windows

    return EXIT_SUCCESS;
}

void markAddresses(Chip8005* chip) {
    //important position tags
    chip->MarkAddress("IsEvenIn", 240);
    chip->MarkAddress("IsEvenOut", 241);
    chip->MarkAddress("IsEvenR0Store", 242);
    chip->MarkAddress("IsEvenR1Store", 243);
    chip->MarkAddress("IsEven0", 244);
    chip->MarkAddress("nextTermIn", 245);
    chip->MarkAddress("nextTermOut", 246);
    chip->MarkAddress("halfIn", 250);
    chip->MarkAddress("halfOut", 251);

    chip->MarkAddress("0", 59); //for resetting registers

    chip->MarkAddress("main()", 0);
    chip->MarkAddress("isEven()", 60);
    chip->MarkAddress("returnEven()", 100);
    chip->MarkAddress("returnOdd()", 110);
    chip->MarkAddress("nextTerm()", 120);
    chip->MarkAddress("half()", 180);
}

void half(Chip8005* chip) {
    //chip->JumpWritePosition("half()");
    chip->LoadAddrToR0("HalfIn");

    chip->MarkNext("Minus");
    chip->MinusR0();
    chip->MinusR0();
    chip->AddR1();
    chip->jumpIfR0Not0("Minus");

    chip->LoadR1ToAddr("halfOut");
}

void isEven(Chip8005* chip) {
    //chip->JumpWritePosition("isEven()");
    //isEven()
    //load isEvenIn -> R0
    //load R0 -> R0Store
    //load R1 -> R1Store
    //mark address
    //check R0 is 0
    //    jump to return even
    //minus 1 -> R0
    //check R0 is 0
    //    jump to return odd
    //add 1 -> R0
    //minus 2 -> R0
    //plus 1 -> R1
    //load R0 -> R0Store
    //load R1 -> R1Store
    //jump to top
    chip->JumpWritePosition("returnEven()");
    chip->JumpWritePosition("returnOdd()");
}
void wondrousSequence(Chip8005* chip) {
    //main()
    //get num
    //tag here
    //load num to isEven's input
    //load isEven's output to R0
    //load R0 to nextTerm's input (call half or add 1 depending on )
    //get num from nextTerm's ouput
    //check is not 1
    //    jump back to tag

    chip->JumpWritePosition("isEven()");

    //writePositionJump (write to somewhere not specified by default)
    //nextTerm()
    chip->MarkNext("nextTerm_half_jumpPosition");


    //

    chip->jumpIfR0Is0("nextTerm_half_jumpPosition");
}

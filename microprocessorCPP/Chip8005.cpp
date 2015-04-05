#include "Chip8005.h"

void Chip8005::Reset(int codeSize) {
    this->R0 = 0;
    R1 = 0;
    SW = 0;
    OUT = "OUT> ";
    currentExecutionPoint = 0;
    tags = std::map<std::string, int>();
    for (int counter = 0; counter < _8005_MEMORY_SIZE; counter++) {
        codes[counter] = 0;
    }
    codeWritePosition = 0;
}

//helper functions
void Chip8005::SetAddrToVal(int address, int val) {
    codes[address] = val;
}
void Chip8005::PrintOut() {
    std::cout << OUT << std::endl;
}
//8005 codes
void Chip8005::Halt() {
    WriteCode(0);
}
void Chip8005::AddR0() {
    WriteCode(1);
}
void Chip8005::MinusR0() {
    WriteCode(2);
}
void Chip8005::AddR1() {
    WriteCode(3);
}
void Chip8005::MinusR1() {
    WriteCode(4);
}
void Chip8005::AddR0R1() {
    WriteCode(5);
}
void Chip8005::MinusR0R1() {
    WriteCode(6);
}
void Chip8005::printR0() {
    WriteCode(7);
}
void Chip8005::jumpIfR0Not0(std::string mark) {
    WriteCode(8, true, tags[mark]);
}
void Chip8005::jumpIfR0Is0(std::string mark) {
    WriteCode(9, true, tags[mark]);
}
void Chip8005::LoadAddrToR0(std::string mark) {
    WriteCode(10, true, tags[mark]);
}
void Chip8005::LoadAddrToR1(std::string mark) {
    WriteCode(11, true, tags[mark]);
}
void Chip8005::LoadR0ToAddr(std::string mark) {
    WriteCode(12, true, tags[mark]);
}
void Chip8005::LoadR1ToAddr(std::string mark) {
    WriteCode(13, true, tags[mark]);
}
void Chip8005::SwapR0WithAddr(std::string mark) {
    WriteCode(14, true, tags[mark]);
}
void Chip8005::SwapR1WithAddr(std::string mark) {
    WriteCode(15, true, tags[mark]);
}
void Chip8005::RingBell() {
    WriteCode(16);
}
void Chip8005::PrintR0AsChar() {
    WriteCode(17);
}

//mark the next code write, used for jumping
void Chip8005::MarkNext(std::string tag) {
    tags[tag] = codeWritePosition;
}
//mark memory address, used for frames
void Chip8005::MarkAddress(std::string tag, int address) {
    tags[tag] = address;
}

void Chip8005::WriteCode(int code, bool hasArgument, int argument) {
    codes[codeWritePosition] = code;
    codeWritePosition++;

    if (hasArgument == true) {
        codes[codeWritePosition] = argument;
        codeWritePosition++;
    }
}

//interprete the code in the code list
void Chip8005::Interpret() {
    for (int i = 0; i < _8005_MEMORY_SIZE; i++) {
        std::cout << codes[i] << " ";
    }
    std::cout << "\n";
    //int currentExecutionPoint = 0;

    while (currentExecutionPoint < _8005_MEMORY_SIZE)
    {
        switch (codes[currentExecutionPoint]) {
        case 0:
            currentExecutionPoint = _8005_MEMORY_SIZE; //got to end of memory to terminate
            break;
        case 1:
            R0 += 1;
            break;
        case 2:
            R0 -= 1;
            break;
        case 3:
            R1 += 1;
            break;
        case 4:
            R1 -= 1;
            break;
        case 5:
            R0 = R0 + R1;
            break;
        case 6:
            R0 = R0 - R1;
            break;
        case 7:
            OUT = OUT + std::to_string(R0);
            break;
        case 8:
            if (R0 != 0)
            {
                //jump
                currentExecutionPoint = codes[currentExecutionPoint + 1] - 1;
                //need to minus 1 since it advances by 1 each cycle
            }
            break;
        case 9:
            if (R0 == 0)
            {
                //jump
                currentExecutionPoint = codes[currentExecutionPoint + 1] - 1;
                //need to minus 1 since it advances by 1 each cycle
            }
            break;
        case 10:
            R0 = codes[codes[currentExecutionPoint + 1]];
            currentExecutionPoint++;
            //need to add 1 since its a 2 byte instruction
            break;
        case 11:
            R1 = codes[codes[currentExecutionPoint + 1]];
            currentExecutionPoint++;
            break;
        case 12:
            codes[codes[currentExecutionPoint + 1]] = R0;
            currentExecutionPoint++;
            break;
        case 13:
            codes[codes[currentExecutionPoint + 1]] = R1;
            currentExecutionPoint++;
            break;
        case 14:
            tmp = codes[codes[currentExecutionPoint + 1]];
            codes[codes[currentExecutionPoint + 1]] = R0;
            R0 = tmp;
            currentExecutionPoint++;
            break;
        case 15:
            tmp = codes[codes[currentExecutionPoint + 1]];
            codes[codes[currentExecutionPoint + 1]] = R1;
            R1 = tmp;
            currentExecutionPoint++;
            break;
        case 16:
            OUT += " *BING!* ";
            break;
        case 17:
            OUT += (char)R0;
            break;
        }
        currentExecutionPoint++;
    }
}
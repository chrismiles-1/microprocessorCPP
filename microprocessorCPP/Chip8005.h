#ifndef CHIP8005_HEADER
#define CHIP8005_HEADER

#include <iostream>
#include <map>
#include <string>

#define _8005_MEMORY_SIZE 256

class Chip8005 {
public:
    void Reset(int codeSize = _8005_MEMORY_SIZE);

    //helper functions
    void SetAddrToVal(int address, int val);
    void PrintOut();
    //8005 codes
    void Halt();
    void AddR0();
    void MinusR0();
    void AddR1();
    void MinusR1();
    void AddR0R1();
    void MinusR0R1();
    void printR0();
    void jumpIfR0Not0(std::string mark);
    void jumpIfR0Is0(std::string mark);
    void LoadAddrToR0(std::string mark);
    void LoadAddrToR1(std::string mark);
    void LoadR0ToAddr(std::string mark);
    void LoadR1ToAddr(std::string mark);
    void SwapR0WithAddr(std::string mark);
    void SwapR1WithAddr(std::string mark);
    void RingBell();
    void PrintR0AsChar();

    //mark the next code write, used for jumping
    void MarkNext(std::string tag);
    //mark memory address, used for frames
    void MarkAddress(std::string tag, int address);

    void WriteCode(int code, bool hasArgument = false, int argument = 0);
    void JumpWritePosition(std::string tag);

    //interprete the code in the code list
    void Interpret();
protected:
private:
    int R0;
    int R1;
    int SW;
    std::string OUT;

    int currentExecutionPoint;
    std::map<std::string, int> tags; //tag where to jump to in the code
    int codes[_8005_MEMORY_SIZE];

    int tmp;

    int codeWritePosition;
};

#endif
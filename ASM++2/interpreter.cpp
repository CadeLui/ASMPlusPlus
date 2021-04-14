#include "interpreter.h"

interpreter::interpreter()
{
	// A translation of each instruction to an integer to be used in a switch statement
	interpreter::InstructionTranslation["ADD"] = 11;
	interpreter::InstructionTranslation["SUB"] = 12;
	interpreter::InstructionTranslation["MUL"] = 13;
	interpreter::InstructionTranslation["DIV"] = 14;
	interpreter::InstructionTranslation["ADC"] = 21;
	interpreter::InstructionTranslation["SUC"] = 22;
	interpreter::InstructionTranslation["MUC"] = 23;
	interpreter::InstructionTranslation["DIC"] = 24;
	interpreter::InstructionTranslation["JGT"] = 31;
	interpreter::InstructionTranslation["JLT"] = 32;
	interpreter::InstructionTranslation["JET"] = 33;
	interpreter::InstructionTranslation["JNE"] = 34;
	interpreter::InstructionTranslation["JMP"] = 35;
	interpreter::InstructionTranslation["OUT"] = 41;
	interpreter::InstructionTranslation["OUC"] = 42;
	interpreter::InstructionTranslation["OUN"] = 43;
	interpreter::InstructionTranslation["INT"] = 51;
	interpreter::InstructionTranslation["INP"] = 52;
	interpreter::InstructionTranslation["POP"] = 61;
	interpreter::InstructionTranslation["PUT"] = 62;
	interpreter::InstructionTranslation["PUS"] = 63;
	interpreter::InstructionTranslation["PUI"] = 64;
	interpreter::InstructionTranslation["FLS"] = 65;
	interpreter::InstructionTranslation["NEW"] = 71;
	interpreter::InstructionTranslation["MOV"] = 72;
	interpreter::InstructionTranslation["CPY"] = 73;
	interpreter::InstructionTranslation["CMT"] = 99;
	interpreter::InstructionTranslation[""] = 99;
}

void interpreter::ADD(int n, int reg)
{
	RegisterVector[reg] += n;
}

void interpreter::SUB(int n, int reg)
{
	RegisterVector[reg] -= n;
}

void interpreter::MUL(int n, int reg)
{
	RegisterVector[reg] *= n;
}

void interpreter::DIV(int n, int reg)
{
	RegisterVector[reg] /= n;
}

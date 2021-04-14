#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

/*
	* Made by Cade Luinenburg, February 10th, 2020
	* Library for funny programming language
	* Called ASM++
	* Last updated September 25th, 2020
	* Last recorded opening September 25th, 2020
*/

std::vector<std::string> parameter; // Parameter passed to instructions
std::string debug; // Flag for debug output
std::string out; // String buffer
std::vector<int> ACC = { 0 }; // Accumulator vector
std::vector<std::string> stack; // Instruction stack

std::map<std::string, int> compile;

// Defines the values for compile
void defineMap()
{
	compile["ADD"] = 11;
	compile["SUB"] = 12;
	compile["MUL"] = 13;
	compile["DIV"] = 14;

	compile["ADC"] = 21;
	compile["SUC"] = 22;
	compile["MUC"] = 23;
	compile["DIC"] = 24;

	compile["JGT"] = 31;
	compile["JLT"] = 32;
	compile["JET"] = 33;
	compile["JNE"] = 34;
	compile["JMP"] = 35;

	compile["OUT"] = 41;
	compile["OUC"] = 42;
	compile["OUN"] = 43;

	compile["INT"] = 51;
	compile["INP"] = 52;

	compile["POP"] = 61;
	compile["PUT"] = 62;
	compile["PUS"] = 63;
	compile["PUI"] = 64;
	compile["FLS"] = 65;

	compile["NEW"] = 71;
	compile["MOV"] = 72;
	compile["CPY"] = 73;

	compile["CMT"] = 99;
	compile[""] = 99;
}

// If instruction takes special parameter or none, return false
// s: a given instruction
// return: true for regular instruction, false for special
bool bad(std::string s)
{
	if (s == "CMT") return false;
	if (s == "PUS") return false;
	if (s == "FLS") return false;
	if (s == "OUC") return false;
	if (s == "OUN") return false;
	return true;
}

// Most of the instructions

// Arithmetic

// Adds N to reg and stores it in reg
void ADD(int n, int reg) { ACC[reg] += n; }

// Subtracts N from reg and stores it in reg
void SUB(int n, int reg) { ACC[reg] -= n; }

// Multiplies reg by N and stores it in reg
void MUL(int n, int reg) { ACC[reg] *= n; } 

// Divides reg by N and stores it in reg
void DIV(int n, int reg) { ACC[reg] /= n; } 

// Register Arithmetic

// Adds reg2 to reg1 and stores it in reg1
// reg1: a register
// reg2: a register
void ADC(int reg1, int reg2) { ACC[reg1] += ACC[reg2]; } 

// Subtracts reg2 from reg1 and stores it in reg1
// reg1: a register
// reg2: a register
void SUC(int reg1, int reg2) { ACC[reg1] -= ACC[reg2]; } 

// Multiplies reg1 by reg2 and stores it in reg1
// reg1: a register
// reg2: a register
void MUC(int reg1, int reg2) { ACC[reg1] *= ACC[reg2]; } 

// Divides reg1 by reg2 and stores it in reg1
// reg1: a register
// reg2: a register
void DIC(int reg1, int reg2) { ACC[reg1] /= ACC[reg2]; } 

// Register Modifiers

// Copies an register to another
// reg1: register being copied to
// reg2: register being copied from
void CPY(int reg1, int reg2) { ACC[reg1] = ACC[reg2]; } 

// Moves value to another register
// n: value being moved
// reg: register being accessed
void MOV(int n, int reg) { ACC[reg] = n; } 

// Creates new register(s)
// n: however many registers to be created
void NEW(int n) { for (int i = 0; i < n; i++) ACC.push_back(0); } 

// User input

// Take in character and store to ACC as an INT
// reg: a register
void INP(int reg)
{
	char tmp; std::cin >> tmp;
	ACC[reg] = (int)tmp;
}

// Take in integer and store to ACC
// reg: a register
void INT(int reg)
{
	std::cin >> ACC[reg];
}

// Output

// Outputs a register
// reg: a register
void OUT(int reg) { std::cout << ACC[reg]; } 

// Outputs current string buffer
void OUC() { std::cout << out; } 

// Outputs new line
void OUN() { std::cout << "\n"; } 

// String buffer modifiers

// Removes last character in string buffer
void POP() { out.pop_back(); } 

// Adds character to end of string buffer
// reg: a register
void PUT(int reg) { out += (char)ACC[reg]; } 

// Adds string to string buffer
// s: an input string
void PUS(std::string s) { out += s; } 

// Adds an accumulator's value to string buffer
// reg: a register
void PUI(int reg) { out += ACC[reg]; } 

// Clears string buffer
void FLS() { out = ""; } 

// Various errors that may arise from bad code

// If input is not an integer, ignore instruction and send warning
// input: a string to be tested for being a number
int nonIntError(std::string input, int line)
{
	try { return stoi(input); } // Try to turn string into integer
	catch (const std::exception&) { std::cout << "NON INT  @" << line + 1 << std::endl; return 0; } // If unable, return 0
}

// If input is not a valid register, create enough registers.
// inputString: A string to be tested for being a valid register
// line: Current line
int invRegError(std::string inputString, int line)
{
	int input = nonIntError(inputString, line); // Input register, also tested for Non Integer Error
	if (input < 0) { std::cout << "INV REG @" << line + 1 << std::endl; return 0; } // If below minimum, return error
	if (input > ACC.size()) { NEW(input + 1 - ACC.size()); } // If above current maximum, create new registers up to requested
	return input; // If no error, return register
}

// Various jumps to allow looping

// Jump to N

// gotoLineString: The line to be jumped to
// line: The current line.
int JMP(std::string gotoLineString, int line)
{
	int gotoLine = nonIntError(gotoLineString, line);
	return gotoLine - 2;
}

// Jump to line when Reg is greater than N
// regString: The register being accessed
// nString: The number being tested
// gotoLineString: The line to be jumped to
// line: The current line.
int JGT(std::string regString, std::string nString, std::string gotoLineString, int line)
{
	int reg = invRegError(regString, line); // Register being tested
	int n = nonIntError(nString, line); // Value register is being tested against
	int gotoLine = nonIntError(gotoLineString, line); // Line the user wants to go to
	if (ACC[reg] > n) return (gotoLine - 2); // If condition is true, to go line
	return line; // Otherwise return next line.
}

// Jump to line when Reg is less than N
// regString: The register being accessed
// nString: The number being tested
// gotoLineString: The line to be jumped to
// line: The current line.
int JLT(std::string regString, std::string nString, std::string gotoLineString, int line)
{
	int reg = invRegError(regString, line);
	int n = nonIntError(nString, line);
	int gotoLine = nonIntError(gotoLineString, line);
	if (ACC[reg] < n) return (gotoLine - 2);
	return line;
}

// Jump to line when Reg is equal to N
// regString: The register being accessed
// nString: The number being tested
// gotoLineString: The line to be jumped to
// line: The current line.
int JET(std::string regString, std::string nString, std::string gotoLineString, int line)
{
	int reg = invRegError(regString, line);
	int n = nonIntError(nString, line);
	int gotoLine = nonIntError(gotoLineString, line);
	if (ACC[reg] == n) return (gotoLine - 2);
	return line;
}

// Jump to line when Reg is not equal to N
// regString: The register being accessed
// nString: The number being tested
// gotoLineString: The line to be jumped to
// line: The current line.
int JNE(std::string regString, std::string nString, std::string gotoLineString, int line)
{
	int reg = invRegError(regString, line);
	int n = nonIntError(nString, line);
	int gotoLine = nonIntError(gotoLineString, line);
	if (ACC[reg] != n) return (gotoLine - 2);
	return line;
}

// Takes a line of code and takes any parameters from it
// line: a line of code
void grabParameters(std::string line)
{
	std::string singleParameter; // Single parameter from list of parameters
	std::string parameters = line.substr(4); // List of parameters from line
	parameter.clear(); // Clear list of parameters of values
	for (int i = 0; i < parameters.length(); i++) // Iterate through parameters character by character
	{
		if (parameters[i] == '.')
		{ // If period is reached, add parameter to list; then, continue.
			parameter.push_back(singleParameter);
			singleParameter.clear(); continue;
		}
		singleParameter += parameters[i]; // If period is not reached, add current character to ass
	}
}

// Reads from the stack and interprets it.
void interpret()
{
	for (int i = 0; i < stack.size(); i++) 
	{
		// Stores the first three characters of a full instruction
		std::string instructionStr = stack[i].substr(0, 3); // Stores lone instruction
		if (stack[i].length() > 3 && bad(instructionStr)) grabParameters(stack[i]); // If instruction valid, grab parameters

		int instruction = compile[instructionStr];

		if (debug == "debug") // Output all accumulators for debugging.
		{
			std::cout << "\n" << i << ": ";
			for (int i2 = 0; i2 < ACC.size(); i2++) std::cout << ACC[i2] << " ";
			std::cout << stack[i] << std::endl;
		}

		switch (instruction)
		{
		case 11: ADD(nonIntError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 12: SUB(nonIntError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 13: MUL(nonIntError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 14: DIV(nonIntError(parameter[0], i), invRegError(parameter[1], i)); break;

		case 21: ADC(invRegError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 22: SUC(invRegError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 23: MUC(invRegError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 24: DIC(invRegError(parameter[0], i), invRegError(parameter[1], i)); break;

		case 31: i = JGT(parameter[0], parameter[1], parameter[2], i); break;
		case 32: i = JLT(parameter[0], parameter[1], parameter[2], i); break;
		case 33: i = JET(parameter[0], parameter[1], parameter[2], i); break;
		case 34: i = JNE(parameter[0], parameter[1], parameter[2], i); break;
		case 35: i = JMP(parameter[0], i); break;

		case 41: OUT(invRegError(parameter[0], i)); break;
		case 42: OUC(); break;
		case 43: OUN(); break;

		case 51: INT(invRegError(parameter[0], i)); break;
		case 52: INP(invRegError(parameter[0], i)); break;

		case 61: POP(); break;
		case 62: PUT(invRegError(parameter[0], i)); break;
		case 63: PUS(stack[i].substr(4)); break;
		case 64: PUI(invRegError(parameter[0], i)); break;
		case 65: FLS(); break;

		case 71: NEW(nonIntError(parameter[0], i)); break;
		case 72: MOV(nonIntError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 73: CPY(invRegError(parameter[0], i), invRegError(parameter[1], i)); break;
		case 99: break;
		default: std::cout << "INV INS " << i + 1 << std::endl;
		}
		// If instruction doesn't exist, report invalid instruction and continue.
	}
}

// Executes single line of code
// line: A complete line of code
// stackPos: the instruction's position in the stack
void execute(std::string line, int stackPos)
{
	// Stores the first three characters of a full instruction
	std::string instructionStr = line.substr(0, 3); // Stores lone instruction
	if (line.length() > 3 && bad(instructionStr)) grabParameters(line); // If instruction valid, grab parameters
	
	int instruction;
	std::stringstream instructionStream(instructionStr);
	instructionStream >> instruction;

	if (debug == "debug") // Output all accumulators for debugging.
	{
		std::cout << "\n" << stackPos << ": ";
		for (int i = 0; i < ACC.size(); i++) std::cout << ACC[i] << " ";
		std::cout << line << std::endl;
	}

	switch (instruction)
	{
	case 11: ADD(nonIntError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 12: SUB(nonIntError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 13: MUL(nonIntError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 14: DIV(nonIntError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;

	case 21: ADC(invRegError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 22: SUC(invRegError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 23: MUC(invRegError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 24: DIC(invRegError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;

	case 31: stackPos = JGT(parameter[0], parameter[1], parameter[2], stackPos); break;
	case 32: stackPos = JLT(parameter[0], parameter[1], parameter[2], stackPos); break;
	case 33: stackPos = JET(parameter[0], parameter[1], parameter[2], stackPos); break;
	case 34: stackPos = JNE(parameter[0], parameter[1], parameter[2], stackPos); break;
	case 35: stackPos = JMP(parameter[0], stackPos); break;

	case 41: OUT(invRegError(parameter[0], stackPos)); break;
	case 42: OUC(); break;
	case 43: OUN(); break;

	case 51: INT(invRegError(parameter[0], stackPos)); break;
	case 52: INP(invRegError(parameter[0], stackPos)); break;

	case 61: POP(); break;
	case 62: PUT(invRegError(parameter[0], stackPos)); break;
	case 63: PUS(line.substr(4)); break;
	case 64: PUI(invRegError(parameter[0], stackPos)); break;
	case 65: FLS(); break;

	case 71: NEW(nonIntError(parameter[0], stackPos)); break;
	case 72: MOV(nonIntError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 73: CPY(invRegError(parameter[0], stackPos), invRegError(parameter[1], stackPos)); break;
	case 99: break;
	default: std::cout << "INV INS " << stackPos + 1 << std::endl;
	}
	// If instruction doesn't exist, report invalid instruction and continue.
}
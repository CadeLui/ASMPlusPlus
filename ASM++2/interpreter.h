#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class interpreter
{
private:
	std::vector<int> RegisterVector = { 0 }; // Holds various registers
	std::vector<std::string> StackVector; // Holds the instruction stack
	std::string StringBuffer; // Holds the string being manipulated
	std::map<std::string, int> InstructionTranslation; // Instructions that map to integers
public:
	// Constructor method
	interpreter();
	void ADD(int n, int reg);
	void SUB(int n, int reg);
	void MUL(int n, int reg);
	void DIV(int n, int reg);

};


#include "parse.h"

/*
	* Made by Cade Luinenburg, November 23, 2019
	* Simple code language
	* Last updated March 30, 2021
*/

int main(int argc, char* argv[])
{
	std::string input; // Current line
	std::ifstream file(argv[2]); // File being interpreted
	debug = argv[1]; // Debug flag
	defineMap();

	// Compile the file and save
	if (debug == "compile")
	{
		// Adds lines from file to instruction stack
		while (getline(file, input)) stack.push_back(input);
	}
	// Read and interpret the file
	if (debug == "run")
	{
		// Adds lines from file to instruction stack
		while (getline(file, input)) stack.push_back(input);
		// Parses instructions in stack
		interpret();
	}
	if (debug == "repl")
	{
		while (true)
		{
			// Get input from user
			getline(std::cin, input);
			// If input instruction is RUN, parse code and empty stack.
			if (input == "RUN") { interpret(); stack.clear(); }
			// Otherwise, push input instruction to stack
			stack.push_back(input);
		}
	}

	// If in debug mode, send all accumulators when done parsing
	if (debug == "debug")
	{
		std::cout << " ";
		for (int i = 0; i < ACC.size(); i++) std::cout << ACC[i] << " ";
		std::cout << "END" << std::endl;
	}
	return 0;
}
/*\
 *
 * Moostard BrainFuck Interpreter
 * By Lymkwi/LeMagnesium
 * License : CC0
 *
\*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bfinterpretor.h"

#define VERSION 1.2

int main(int argc, char ** argv) {
	if (argc == 1) {
		// Infos here
		std::cout << "Moostard BrainFuck Interpreter" << std::endl;
		std::cout << "By Lymkwi | Version " << VERSION << std::endl;
		std::cout << "Compiled on the " << __DATE__ << " at " << __TIME__ << std::endl;
		std::cout << "Compiling standard : " << __cplusplus << std::endl;
		std::cout << "--- Specifications ---" << std::endl;
		std::cout << "\tMemory Ribbon Index has " << sizeof(size_t) << " bytes (" << std::pow(2, sizeof(size_t) * 8) << " cells), unsigned" << std::endl;
		std::cout << "\tData wraps around " << sizeof(uint8_t) * 8 << " bits, signed" << std::endl;
		std::cout << "---- End of Specs ----" << std::endl;
		return 0;
	}

	std::ifstream fptr = std::ifstream();
	fptr.open(argv[1]);
	if (!fptr) {
		std::cerr << "ERROR Couldn't open file " << argv[1] << std::endl;
		return 1;
	}

	std::string moo;
	fptr.seekg(0, fptr.end);
	size_t length = fptr.tellg();
	fptr.seekg(0, fptr.beg);

	char * buff = new char[length];
	fptr.read(buff, length);
	fptr.close();
	moo += buff;
	delete[] buff;

	BFInterpretor interpretor = BFInterpretor();
	interpretor.process(moo);

	// Interpretation
	interpretor.interpret(moo);
	return 0;
}


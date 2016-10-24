/*\
 *
 * Moostard BrainFuck Interpreter
 * By Lymkwi/LeMagnesium
 * License : WTFPL
 *
\*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <thread>
#include <chrono>

#define VERSION 1.0

int main(int argc, char * argv[]) {
	if (argc == 1) {
		// Infos here
		std::cout << "Moostard BrainFuck Interpreter" << std::endl;
		std::cout << "By Lymkwi | Version " << VERSION << std::endl;
		std::cout << "Compiled on the " << __DATE__ << " at " << __TIME__ << std::endl;
		std::cout << "Compiling standard : " << __cplusplus << std::endl;
		std::cout << "--- Specifications ---" << std::endl;
		std::cout << "\tRibbon Index coded on " << sizeof(size_t) << " bytes, unsigned" << std::endl;
		std::cout << "\tData wraps around " << sizeof(long long) << " bytes, signed" << std::endl;
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
	moo += buff;
	delete[] buff;

	long long brackets = 0;
	// Here we simply parse the string using i as index and nest ternary operators to modify 'brackets'
	for (size_t i = 0; i <= length; brackets += (moo[i] == '[' ? 1 : (moo[i] == ']' ? -1 : 0))) {
		i++;
		if (brackets < 0) {
			std::cerr << "ERROR : Closing bracket before its opening counterpart" << std::endl;
			return -1;
		}
	}

	if (brackets) {
		std::cerr << "ERROR : Expected closing bracket" << std::endl;
		return 1;
	}

	// Interpretation
	std::vector<std::string::iterator> loop_register;
	std::map<size_t, long long> memory; // start with that much
	size_t pointer = 0;
	for (std::string::iterator iter = moo.begin(); iter != moo.end(); iter++) {
		bool unprint = true;
		switch(*iter) {
			case '[': {
					if (memory[pointer]) {
						loop_register.push_back(iter);
					} else {
						// We have to ignore everything until we find the end
						iter++;
						for (size_t level = 1; level > 0; iter++) {
							switch (*iter) {
								case '[': {level++; break;}
								case ']': {level--; break;}
								default: break;
							}
						}
						iter--;
							
					}
					break;
				}
			case ']': {
				if (memory[pointer]) {
					iter = loop_register.back();
				} else {
					loop_register.pop_back();
				}
				break;
			}
			// Pointer move
			case '>': { pointer++; break; }
			case '<': { pointer--; break; }
			// I/O
			case '.': { std::cout << (char)(memory[pointer]); break; }
			case ',': {
					char k = ' ';
					std::cin.get(k);
					memory[pointer] = (std::cin.eof() | std::cin.fail() ? -1 : (int)(k)); 
					break;
				}
			// Arithmetic
			case '+': { memory[pointer]++; break; }
			case '-': { memory[pointer]--; break; }

			default: { break;}
		}
		//std::cout << *iter << ")=::[" << pointer << "]--{" << (int)(memory[pointer]) << '}' << std::endl;
	}

	return 0;
}

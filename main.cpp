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
#include <cassert>
#include <cctype>
#include <cstring>

#define VERSION 1.2

/*int old_main(int argc, char * argv[]) {

}*/

class BFInterpretor {
	public:
		BFInterpretor();
		~BFInterpretor();
		void process(std::string);
		void add_function();

		void _check_dead_syntax(std::string&);
		void _find_function_definitions(std::string&);
		void _check_function_calls(std::string&);
		void interpret(std::string&);

	private:
		std::map<std::string, std::string> function_register;
		std::map<size_t, uint8_t> memory;
		std::vector<std::string::iterator> loop_register;
		size_t memory_pointer, register_pointer;
};


int main(int argc, char ** argv) {
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
	fptr.close();
	moo += buff;
	delete[] buff;

	BFInterpretor interpretor = BFInterpretor();
	interpretor.process(moo);

	// Interpretation
	interpretor.interpret(moo);
	return 0;
}

void BFInterpretor::process(std::string moo) {
	this->_check_dead_syntax(moo);
	this->_find_function_definitions(moo);
	this->_check_function_calls(moo);
}

void BFInterpretor::_check_function_calls(std::string& moo) {
	// #2 : Detect calls
	for (size_t i = 0; i < moo.length(); i++) {
		if (moo[i] != '~')
			continue;

		// Determine name
		size_t namelength;
		i++;
		for (namelength = 0; namelength + i < moo.length(); namelength++) {
			if (moo[i+namelength] == ';')
			break;
		}
		std::string func_name = moo.substr(i, namelength);
		if (!this->function_register.count(func_name)) {
			std::cerr << "ASSERTION FAIL on call-check for " << func_name << std::endl;
			assert(0);
		}
	}
}

void BFInterpretor::_find_function_definitions(std::string& moo) {
	// #1 : Detect definitions
	for (size_t i = 0; i < moo.length(); i++) {
		if (moo[i] != '(')
			continue;

		// Start looking for the end parenthesis and assert the name
		size_t namelength = 1;
		for (; namelength + i < moo.length(); namelength++) {
			char current = moo[namelength+i];
			if (current == ')')
				break;
			assert(isdigit(current) || islower(current) || current == '_');
		}
		//std::cout << namelength << " is the namelength\n";
		std::string func_name = moo.substr(i+1, namelength-1);
		//std::cout << "Found function header '" << func_name << "'" << std::endl;

		i += namelength + 1;
		assert(moo[i] == ':' && moo[i+1] == '{');
		//std::cout << "Found beginning of code string" << std::endl;

		// Now, the code
		i += 2;
		size_t codelength = 0;
		for (; codelength + i < moo.length(); codelength++) {
			if (moo[i+codelength] == '}')
				break;
		}
		//std::cout << "Codelength is " << codelength << std::endl;

		// Now, store!
		this->function_register[func_name] = moo.substr(i, codelength);
	}
}


void BFInterpretor::_check_dead_syntax(std::string& moo) {
	/*
		Checking Dead Syntax

	Dead syntax is the colloquial name of syntax determined by [](){} and ~;.
	Those are purely static and therefore are verified during processing
	*/

	// Assertions
	int brackets, parenthesis, curly, calls;
	brackets = parenthesis = curly = calls = 0;
	for (size_t i = 0; i < moo.length(); i++) {
		switch (moo[i]) {
			case '[': brackets++; break;
			case ']': brackets--; break;
			case '(': parenthesis++; break;
			case ')': parenthesis--; break;
			case '{': curly++; break;
			case '}': curly--; break;
			case '~': calls++; break;
			case ';': calls--; break;
			default: break;
		}
	}
	assert(brackets == 0);
	assert(parenthesis == 0);
	assert(curly == 0);
	assert(calls == 0);
}

BFInterpretor::BFInterpretor() {
	this->function_register["sub_5"] = "-----";
	this->function_register["sub_10"] = "----------";
	this->function_register["add_5"] = "+++++";
	this->function_register["add_10"] = "++++++++++";
	this->function_register["imove"] = "[->+<]";
	this->function_register["dmove"] = "[-<+>]";
	this->function_register["clean"] = "[-]";

	std::string scan8;
	for (size_t i = 0; i < 8; i++)
		scan8.append(".>");
	for (size_t i = 0; i < 8; i++)
		scan8.append("<");
	this->function_register["scan8"] = scan8;
	this->function_register["scan16"] = scan8.substr(0,16) + scan8.substr(0,16) + scan8.substr(16,8) + scan8.substr(16,8);

	this->function_register["foreach_cpy"] = ">[>[->+<<<+>>]>[-<+>]<<-]>[-]<<";
	this->function_register["add"] = ">[-<+>]<"; // :R:X:
	this->function_register["sub"] = ">[-<->]<"; // :R:Y:
	this->function_register["mul"] = this->function_register["foreach_cpy"];

	this->function_register["pow"] = ">>>+<<[>>[->+<]<[->>>+>+<<<<]>>>>[-<<<<+>>>>]<<<~foreach_cpy;<<-]>>[-<<<+>>>]<[-]<<";
	this->function_register["eq"] = "[->-<]+>[<[-]>[-]][-]<";
	this->function_register["neq"] = "[->-<]>[[-]<+>][-]<}";
	this->function_register["lt"] = ">[->+<]<[->+<]>+>+>>+<<<[->-[>]<<]>>>[<<[-]<<+>>>]>-<<[-]<[-]<";
	this->function_register["gt"] = ">[->+<]>>>+<<<<[->+<]>>[-<-[<]>>]>[-<<[-]<]>[-<<<[-]<+>>]<<";
}

BFInterpretor::~BFInterpretor() {
	;
}

void BFInterpretor::interpret(std::string& moo) {
	int silencer = 0;
	for (std::string::iterator iter = moo.begin(); iter != moo.end(); iter++) {
		bool unprint = true;
		switch(*iter) {
			case '(': { silencer++; break; } // These
			case '{': { silencer++; break; } // Prevent
			case ')': { silencer--; break; } // Intepreting
			case '}': { silencer--; break; } // Functions
		}

		if (silencer > 0)
			continue;

		switch(*iter) {
			case '~': {
					// Ok. Function call
					iter++;
					// Get the name
					size_t namelength = 0;
					std::string func_name;
					while (*iter != ';') {
						func_name.append(1, *iter);
						iter++;
					}


					//this->process(this->function_register[func_name]);
					this->interpret(this->function_register[func_name]);
					break;
			}
			case '[': {
					if (this->memory[this->memory_pointer]) {
						this->loop_register.push_back(iter);
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
				// We hit the end, so we chose..
				// We can go back to the beginning of the loop
				if (this->memory[this->memory_pointer]) {
					iter = this->loop_register.back();
				// Or else, we leave the loop, and vacuum the register
				} else {
					this->loop_register.pop_back();
				}
				break;
			}
			// Pointer move
			case '>': { this->memory_pointer++; break; }
			case '<': { this->memory_pointer--; break; }
			// I/O
			case '.': { std::cout << (char)(this->memory[this->memory_pointer]); break; }
			case ',': {
					char k = ' ';
					std::cin.get(k);
					memory[this->memory_pointer] = (std::cin.eof() | std::cin.fail() ? this->memory[this->memory_pointer] : (int)(k));
					break;
				}
			// Arithmetic
			case '+': { this->memory[this->memory_pointer]++; break; }
			case '-': { this->memory[this->memory_pointer]--; break; }

			default: { break;}
		}
	}

}

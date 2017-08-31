#ifndef BF_INTERPRETOR_H
#define BF_INTERPRETOR_H "moo"

#include <string>
#include <map>
#include <vector>
#include <iostream>

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

#endif

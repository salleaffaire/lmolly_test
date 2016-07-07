#include <string>
#include <iostream>
#include "lmolly/clpp.hpp"

int 
main(int argc, char *argv[]) {

	// Instanciate a command line argument parser
	lmolly::clpp cl;
	
	// Enable HELP and set the help flag to 'h' 
	cl.set_help_flag('h');
	
	// Adding a valid flag with its description
	cl.add_flag('v', "Enable verbose mode");

	// Adding a valid special flag with its description
	cl.add_special_flag('a', "The description of --a");

	// Process the command line arguments
	cl.process(argc, argv);

	// If a key exists
	std::string mode;
	if ((mode = cl.get_string("mode")) != "") {
		std::cout << "Mode : " << mode << std::endl;
	}
	else {
		std::cout << "No mode selected" << std::endl;
	}

	// Debug 
	#if 0
	std::cout << "Flags" << std::endl;
	std::cout << "------------------------------------------------ " << std::endl;
	cl.PrintFlags();

	std::cout << std::endl << std::endl;

	std::cout << "Key Value Strings" << std::endl;
	std::cout << "------------------------------------------------ " << std::endl;
	cl.PrintKeyValueStrings();

	std::cout << std::endl << std::endl;

	std::cout << "Key Value Numbers" << std::endl;
	std::cout << "------------------------------------------------ " << std::endl;
	cl.PrintKeyValueNumbers();
	#endif

	return 0;
} 

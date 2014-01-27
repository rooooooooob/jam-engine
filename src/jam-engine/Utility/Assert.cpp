#include "jam-engine/Utility/Assert.hpp"

#include <iostream>

namespace je
{

void assertFailed(const char *exp,int line, const char *file)
{
	std::cerr << "Assertion <" << exp << "> failed on line " << line << " of " << file << std::endl;
	std::cin.get();
	exit(1);
}

void assertFailed(const char *exp, int line, const char *file, const char *message)
{
	std::cerr << "Assertion <" << exp << "> failed on line " << line << " of " << file << std::endl
	          << "Assertion message: " << message << std::endl;
	std::cin.get();
	exit(1);
}

void error(int line, const char *file, const char *message)
{
	std::cerr << "Hit error on line " << line << " of " << file << std::endl
	          << "Message: " << message << std::endl;
	std::cin.get();
	exit(1);
}

}

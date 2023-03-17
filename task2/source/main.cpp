#include <iostream>

#include "big_integer/big_integer.h"

int main(int argc, char** argv) {

	try {
		auto num1 = big_integer("-4");
		auto num2 = big_integer("-5");

		auto result = num1 + num2;

		std::cout << result << std::endl;

		result = std::move(num1);

		std::cout << result << std::endl;

		std::cout << num2 * (-5) << std::endl;

	}
	catch (...) {
		std::cout << "Uncorrect input" << std::endl;
	}
	
	return 0;
}
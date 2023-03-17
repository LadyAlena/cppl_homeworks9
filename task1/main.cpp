#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::vector<T> move_vectors(std::vector<T>& v_lhs, std::vector<T>& v_rhs) {

	v_lhs = std::move(v_rhs);

	return v_lhs;
}

int main(int argc, char** argv) {

	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;

	move_vectors(two, one);

	return 0;
}
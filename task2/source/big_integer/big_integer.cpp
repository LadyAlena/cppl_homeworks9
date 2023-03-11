#include "big_integer.h"

#include <iostream>

big_integer::big_integer(std::string str) {

	if (str[0] == '-') {
		str = str.substr(1);
		sign.negative = true;
	}
	else {
		if (str[0] == '+') str = str.substr(1);
		sign.positive = true;
	}

	std::string check_correct_ch{};

	for (const auto& ch : str) {

		check_correct_ch = ch;

		auto result_str2int = std::stoi(check_correct_ch);

		number.push_back(result_str2int);
	}

	delete_front_zero(number);
}

big_integer::big_integer(const big_integer& other) noexcept { *this = other; }

big_integer big_integer::operator+(big_integer& other) noexcept {

	if (sign != other.sign) {
		if (sign.positive) {
			other.sign.set_positive();
			return *this - other;
		}
		else {
			sign.set_positive();
			return other - *this;
		}
	}

	if (!number.size()) { return other; }

	if (!other.number.size()) { return *this; }

	big_integer result_add{};

	if (sign.positive) result_add.sign.set_positive();
	else result_add.sign.set_negative();

	int size_ = std::max(number.size(), other.number.size());
	int memory{};

	result_add.number.resize(size_);

	int difference = number.size() - other.number.size();

	if (difference > 0) other.number.insert(other.number.begin(), difference, { 0 });
	if (difference < 0) number.insert(number.begin(), std::abs(difference), { 0 });

	for (int i = (size_ - 1); i >= 0; --i) {
		result_add.number[i] = (memory + number[i] + other.number[i]) % 10;
		memory = (memory + number[i] + other.number[i]) / 10;
	}

	if (memory) { result_add.number.insert(result_add.number.begin(), memory); }

	return result_add;
}

big_integer big_integer::operator-(big_integer& other) noexcept {

	if (sign != other.sign) {
		if (sign.positive) { other.sign.set_positive(); }
		else { other.sign.set_negative(); }
		return *this + other;
	}

	if (sign.negative) {
		sign.set_positive();
		other.sign.set_positive();
		return other - *this;
	}

	if (!number.size()) {
		other.sign.set_inversion_sign();
		return other;
	}

	if (!other.number.size()) { return *this; }

	big_integer result_sub{};

	int size_ = std::max(number.size(), other.number.size());

	result_sub.number.resize(size_);

	big_integer a{};
	big_integer b{};

	if (max_by_abs(*this, other)) {
		a = *this;
		b = other;
		result_sub.sign.set_positive();
	}
	else {
		a = other;
		b = *this;
		result_sub.sign.set_negative();
	}

	b.number.insert(b.number.begin(), a.number.size() - b.number.size(), { 0 });

	for (int i = size_ - 1; i >= 0; --i) {
		if (a.number[i] >= b.number[i]) {
			result_sub.number[i] = a.number[i] - b.number[i];
		}
		else {
			result_sub.number[i] = (a.number[i] + 10) - b.number[i];
			a.number[i - 1]--;
		}
	}

	delete_front_zero(result_sub.number);

	return result_sub;
}

big_integer big_integer::operator*(const int num) noexcept {

	big_integer result_multi{};

	for (int i = 0; i < std::abs(num); ++i) {
		result_multi = result_multi + *this;
	}

	if (num < 0) result_multi.sign.set_inversion_sign();

	return result_multi;
}

big_integer& big_integer::operator=(const big_integer& other) noexcept {
	number = other.number;
	sign = other.sign;

	return *this;
}

big_integer& big_integer::operator=(big_integer&& other) noexcept {
	number = other.number;
	sign = other.sign;

	other.number.clear();
	sign = { false, false };

	return *this;
}

bool big_integer::operator==(const big_integer& other) const { return (number == other.number) && (sign == other.sign); }

bool big_integer::max_by_abs(const big_integer& lhs, const big_integer& rhs) const {

	if (lhs == rhs) return false;

	bool result = false;

	if (lhs.number.size() == rhs.number.size()) {

		int i = 0;

		while (lhs.number[i] == rhs.number[i] && i < lhs.number.size() - 1) { i++; }

		result = lhs.number[i] > rhs.number[i];
	}
	else {
		result = (lhs.number.size() > rhs.number.size()) ? true : false;
	}

	return result;
}

void big_integer::delete_front_zero(std::vector<int>& v) {
	auto i = 0;
	while (v.size() && !v[i]) v.erase(v.begin());
}

std::ostream& operator<<(std::ostream& out, const big_integer& big_int) noexcept {
	std::string str_big_int{};

	for (auto el : big_int.number) { str_big_int += std::to_string(el); }

	str_big_int = big_int.sign.positive ? str_big_int : "-" + str_big_int;

	out << str_big_int;

	return out;
}
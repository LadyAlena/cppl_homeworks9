#include "Sign.h"

bool Sign::operator==(const Sign& other) const { return (negative == other.negative) && (positive == other.positive); }

bool Sign::operator!=(const Sign& other) const { return !(*this == other); }

Sign& Sign::operator=(const Sign& other) noexcept {
	positive = other.positive;
	negative = other.negative;

	return *this;
}

Sign& Sign::operator=(Sign&& other) noexcept {
	
	positive = other.positive;
	negative = other.negative;

	other.set_default();

	return *this;
}

Sign& Sign::set_positive() {
	positive = true;
	negative = false;
	return *this;
}

Sign& Sign::set_negative() {
	positive = false;
	negative = true;
	return *this;
}

Sign& Sign::set_inversion_sign() {
	positive = !positive;
	negative = !negative;
	return *this;
}

Sign& Sign::set_default()
{
	positive = false;
	negative = false;

	return *this;
}

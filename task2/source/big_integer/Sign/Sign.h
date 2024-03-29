#pragma once
struct Sign {

	bool positive = false;
	bool negative = false;

	bool operator == (const Sign& other) const;
	bool operator != (const Sign& other) const;
	Sign& operator = (const Sign& other) noexcept;
	Sign& operator = (Sign&& other) noexcept;


	Sign& set_positive();
	Sign& set_negative();
	Sign& set_inversion_sign();
	Sign& set_default();
};
#pragma once
#include <string>
#include <vector>

#include "Sign/Sign.h"

class big_integer
{
public:
	big_integer() = default;
	big_integer(std::string str);
	big_integer(const big_integer& other) noexcept;
	big_integer(big_integer&& other) noexcept;

	big_integer operator + (big_integer& other) noexcept;
	big_integer operator - (big_integer& other) noexcept;
	big_integer operator * (const int num) noexcept;
	big_integer& operator = (const big_integer& other) noexcept;
	big_integer& operator = (big_integer&& other) noexcept;

	friend std::ostream& operator<<(std::ostream& out, const big_integer& big_int) noexcept;

private:
	std::vector<int> number;
	Sign sign{};

	bool operator == (const big_integer& other) const;

	bool max_by_abs(const big_integer& lhs, const big_integer& rhs) const;

	void delete_front_zero(std::vector<int>& v);
};
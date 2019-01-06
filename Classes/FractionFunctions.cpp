#include "Fraction.h"
#include "stdafx.h"
#include <cmath>


const Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
	return Fraction(lhs.num()*rhs.num(), lhs.den()*rhs.den()).simplify();
}

const Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
	return Fraction(lhs.num()*rhs.den() + rhs.num()*lhs.den(), lhs.den()*rhs.den()).simplify();
}

const Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
	return Fraction(lhs.num()*rhs.den() - rhs.num()*lhs.den(), lhs.den()*rhs.den()).simplify();
}

const Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
	return Fraction(lhs.num()*rhs.den(), lhs.den()*rhs.num()).simplify();
}

const Fraction&  Fraction::simplify()
{
	if (denomintor < 0)
	{
		denomintor = -denomintor;
		numerator = -numerator;
	}
	if (numerator%denomintor == 0)
	{
		numerator = numerator / denomintor;
		denomintor = 1;
	}
	else
	{
		for (int i = 2; i <= denomintor&&i <= std::abs(numerator); i++)
		{
			if (denomintor%i == 0 && numerator%i == 0)
			{
				denomintor = denomintor / i;
				numerator = numerator / i;
				i = 1;
			}
		}
	}
	return *this;
}


Fraction::Fraction(int n, int d) :numerator(n), denomintor(d)
{
	if (denomintor == 0)
	{
		std::cout << "denomintor can not be zero" << std::endl;
		exit(0);
	}
}

std::ostream & operator<<(std::ostream &os, const Fraction &f)
{
	if (f.denomintor == 1)
	{
		os << f.numerator;
	}
	else
	{
		os << f.numerator << '/' << f.denomintor;
	}
	return os;
}


bool operator<(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() < rhs.num()*lhs.den())
	{
		return 1;
	}
	else
		return 0;
}
bool operator>(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() > rhs.num()*lhs.den())
	{
		return 1;
	}
	else
		return 0;
}


bool operator<=(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() <= rhs.num()*lhs.den())
	{
		return 1;
	}
	else
		return 0;
}

bool operator>=(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() >= rhs.num()*lhs.den())
	{
		return 1;
	}
	else
		return 0;
}


bool operator==(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() == rhs.num()*lhs.den())
	{
		return 1;
	}
	else
		return 0;
}

bool operator!=(const Fraction &lhs, const Fraction &rhs)
{
	if (lhs.num()*rhs.den() == rhs.num()*lhs.den())
	{
		return 0;
	}
	else
		return 1;
}

Range Fraction::cal_range() const
{
	Range r;
	if (denomintor == 1)
	{
		CCLOG("intcalwrong");
		exit(0);
	}
	r.min = numerator / denomintor;
	r.max = r.min + 1;
	return r;
}
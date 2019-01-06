#pragma once
#include <iostream>
#include "cocos2d.h"


USING_NS_CC;

struct Range
{
	int min;
	int max;
};


class Fraction
{
private:
	int numerator;
	int denomintor;
public:
	Fraction(int n, int d = 1);
	friend std::ostream & operator<<(std::ostream &os, const Fraction &f);
	int num() const { return numerator; }
	int den() const { return denomintor; }
	const Fraction& simplify();
	Range cal_range() const;
};

const Fraction operator+(const Fraction &lhs, const Fraction &rhs);
const Fraction operator*(const Fraction &lhs, const Fraction &rhs);
const Fraction operator-(const Fraction &lhs, const Fraction &rhs);
const Fraction operator/(const Fraction &lhs, const Fraction &rhs);
bool operator<(const Fraction &lhs, const Fraction &rhs);
bool operator>(const Fraction &lhs, const Fraction &rhs);
bool operator>=(const Fraction &lhs, const Fraction &rhs);
bool operator<=(const Fraction &lhs, const Fraction &rhs);
bool operator==(const Fraction &lhs, const Fraction &rhs);
bool operator!=(const Fraction &lhs, const Fraction &rhs);
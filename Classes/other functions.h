#pragma once
#include <string>
#include <sstream>
#include "Fraction.h"

std::string makeTab(int n);
std::string makeTab(char ch);
std::string makeTab(std::string s);
std::string makeTab(Fraction f);
bool isValid(const std::string& str, int n);
bool isSign(const std::string&str);
bool lessThan(const std::string& str, int n, int max);
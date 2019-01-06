#include "other functions.h"
#include <sstream>



std::string makeTab(int n)
{
	std::stringstream s;
	s << n;
	std::string str = s.str();
	while (str.size() < 8)
	{
		str = " " + str;
	}
	str = " " + str;
	return str;
}

std::string makeTab(char ch)
{
	std::string str;
	str += ch;
	while (str.size() < 8)
	{
		str = " " + str;
	}
	str = " " + str;
	return str;
}

std::string makeTab(std::string s)
{
	std::string str;
	str += s;
	while (str.size() < 8)
	{
		str = " " + str;
	}
	str = " " + str;
	return str;
}

std::string makeTab(Fraction f)
{
	std::stringstream s;
	if (f.den() != 1)
	{
		s << f.num() << '/' << f.den();
	}
	else
	{
		s << f.num();
	}
	std::string str = s.str();
	while (str.size() < 8)
	{
		str = " " + str;
	}
	str = " " + str;
	return str;
}

bool isValid(const std::string& str, int n)
{
	int len;
	len = str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ')
		{
			continue;
		}

		if (str[i] == '-')
		{
			if (i + 1 < len)
			{
				if (str[i + 1] >= '0'&& str[i + 1] <= '9')
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (str[i] >= '0'&& str[i] <= '9')
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}

	int count = 0;
	bool bo = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != ' ')
		{
			if (bo == 0)
			{
				count++;
				bo = 1;
				continue;
			}
			if (str[i] == '-')
			{
				bo = 0;
			}
		}
		else
		{
			bo = 0;
		}
	}

	if (count == n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSign(const std::string& str)
{
	if (str.size() != 2)
	{
		return false;
	}
	if (str[0] == '<' || str[0] == '>')
	{
		if (str[1] == '=')
		{
			return true;
		}
	}
	return false;
}



bool lessThan(const std::string& str, int n, int max)
{
	if (isValid(str, n))
	{
		std::istringstream input(str);
		for (int i = 0; i < n; ++i)
		{
			int a;
			input >> a;
			if (a > max || a <= 0)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

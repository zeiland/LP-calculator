#include "stdafx.h"
#include "LP.h"

std::vector<Fraction> best_result;
std::vector<std::vector<Fraction>> best_results;
extern std::vector<int> int_lim;

void int_lp(std::shared_ptr<Lp> p)
{
	std::vector<Fraction> result = p.get()->result_cal();
	if (!best_result.empty())
	{
		if (result.back() > best_result.back())
		{
			return;
		}
	}
	int size = int_lim.size();
	bool b = 0;
	for (int j = 0; j < size; j++)
	{
		int i = int_lim[j];
		if (result[i].den() != 1)
		{
			b = 1;
			Range r = result[i].cal_range();
			std::shared_ptr<Lp> Lchild(new Lp(*(p.get())));
			if (Lchild.get()->add_condition_noprint(p.get()->parse(0, i, r.min)))
			{
				int_lp(Lchild);
			}
			std::shared_ptr<Lp> Rchild(new Lp(*(p.get())));
			if (Rchild.get()->add_condition_noprint(p.get()->parse(1, i, r.max)))
			{
				int_lp(Rchild);
			}
		}
	}
	if (b == 0)
	{
		if (!best_result.empty())
		{
			if (best_result.back() > result.back())
			{
				best_result = result;
				best_results.clear();
				best_results.push_back(result);
			}
			else
			{
				bool bo = 0;
				for (const auto &x : best_results)
				{
					if (x[0] == result[0])
					{
						bo = 1;
					}
				}
				if (bo == 0)
				{
					best_results.push_back(result);
				}
			}
		}
		else
		{
			best_result = result;
			best_results.push_back(result);
		}
	}
}

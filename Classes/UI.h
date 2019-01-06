#pragma once

#include "LP.h"

class UI
{
private:
	Lp *p;
	bool isLp;
public:
	UI();
	void Fst_in();
	void Scd_in();
	void Trd_in();
	void deleteLp()
	{
		if (isLp)
		{
			delete p;
			isLp = 0;
		}
	}
};

UI& UIgetInstance();
#include "UI.h"
#include "stdafx.h"
#include "cocos2d.h"

USING_NS_CC;

using namespace std;


UI::UI()
{
}


void UI::Fst_in()
{
	char ch;
	ifstream input(FileUtils::getInstance()->getWritablePath() + "mode1.txt");
	if (input.is_open())
	{
		CCLOG("mode1open");
		input >> ch;
		input.close();
		switch (ch)
		{
		case 'A':p = new Lp; isLp = 1; p->enter(); Scd_in();	 break;
		}
	}
	else
	{
		CCLOG("UIWRONG!");
		Director::getInstance()->end();
	}
	
}

void UI::Scd_in()
{
	char ch;
	ifstream input(FileUtils::getInstance()->getWritablePath() + "mode2.txt");
	if (input.is_open())
	{
		CCLOG("secondPageOpen");
		input >> ch;
		switch (ch)
		{
		case 'A': p->cal();   break;
		case 'B': p->dual();  break;
		case 'C':p->int_Lp(); break;
		}
		input.close();
	}
	else
	{
		CCLOG("UIWRONG!");
		Director::getInstance()->end();
	}
}


void UI::Trd_in()
{
	char ch;
	ifstream input(FileUtils::getInstance()->getWritablePath() + "mode3.txt");
	input >> ch;
	switch (ch)
	{
		case 'A': p->add_var();    break;
		case 'B': p->add_condition();   break;
		case 'C': p->sensi_analyze();    break;
     	//case 'D': system("cls"); delete p; FstPage(); Fst_in();
	}
}



UI& UIgetInstance()
{
	static UI a;
	return a;
}
#include "stdafx.h"
#include "LP.h"
#include <algorithm>
#include "cocos2d.h"
#include "other functions.h"
#include "ShowPageScene.h"

using namespace std;
USING_NS_CC;

Lp::Lp() :NumCondition(0), NumVar(0)
{}

void Lp::enter()
{
	ifstream input(FileUtils::getInstance()->getWritablePath() + "input.txt");
	if (input.is_open())
	{
		input >> NumVar;
		input >> NumCondition;
		std::vector<Fraction> MinVar;
		for (int i = 0; i < NumVar; i++)
		{
			int a;
			input >> a;
			target_func.push_back(a);
			MinVar.push_back(Fraction(0) - Fraction(a));
		}
		for (int i = 0; i < NumCondition + 1; i++)                  //添加辅助变量以及RHS。
		{
			MinVar.push_back(Fraction(0));
		}
		for (int i = 0; i < NumCondition; i++)
		{
			target_func.push_back(0);
		}
		mt.push_back(MinVar);

		for (int i = 0; i < NumCondition; i++)
		{
			std::vector<Fraction> var;
			for (int j = 0; j < NumVar; j++)
			{
				int a;
				input >> a;
				var.push_back(Fraction(a));
			}


			char sign1 = NULL;
			char sign2 = NULL;
			input >> sign1;
			input >> sign2;


			int rhs;
			input >> rhs;
			condition_r.push_back(rhs);
			//开始处理辅助变量
			for (int j = 0; j < NumCondition; j++)
			{
				if (j == i)
				{
					if (sign1 == '<')
					{
						var.push_back(Fraction(1));
						BasicVar.push_back(NumVar + j);
					}
					else
					{
						sign1 = '<';
						rhs = -rhs;
						for (int k = 0; k < var.size(); k++)
						{
							var[k] = Fraction(0) - var[k];
						}
						var.push_back(Fraction(1));
						BasicVar.push_back(NumVar + j);
					}
				}
				else
				{
					var.push_back(Fraction(0));
				}
			}
			var.push_back(rhs);
			mt.push_back(var);
		}
		NumVar += NumCondition;                 //将辅助变量个数填入变量总数
		FirstBasicVar = BasicVar;
	}
	else
	{
		CCLOG("LpWrong!");
		delete this;
		Director::getInstance()->end();
	}
	CCLOG("EnterComplete");
	ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt");
	output.close();
}




void Lp::print()
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "output.txt",std::ios::app);
	int SizeRow = mt[0].size();
	out << std::endl << "now Simplex tableau is:" << std::endl;
	for (int i = 0; i < NumCondition + 2; i++)
	{
		if (i == 0)
		{
			out << "  " << makeTab('z');
		}
		if (i == 1)
		{
			out << "z " << makeTab(1);
		}
		if (i > 1)
		{
			out << 'x' << BasicVar[i - 2] + 1 << makeTab(0);
		}
		for (int j = 0; j < SizeRow; j++)
		{
			if (i == 0)
			{
				if (j == SizeRow - 1)
				{
					out << makeTab("RHS");
				}
				else
				{
					std::stringstream s;
					s << j + 1;
					std::string str = s.str();
					str = 'x' + str;
					out << makeTab(str);
				}
			}
			else
			{
				out << makeTab(mt[i - 1][j]);
			}
		}
		out << std::endl;
	}
	out << std::endl;
	CCLOG("enterSuccess");
	out.close();
}

void Lp::cal()
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "output.txt", std::ios::app);
	bool judge = 0;
	for (int i = 1; i < NumCondition + 1; i++)
	{
		if (mt[i][NumVar] < 0)
		{
			judge = 1;
		}
	}
	if (judge == 1)
	{
		tfm();
	}

	int count = 0;
	while (1)
	{
		print();
		count++;
		if (count == 50)
		{
			out << "circle wrong" << std::endl;
			CCLOG("circlewrong");
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
		Fraction max = mt[0][0];
		int MaxJ = 0;
		for (int j = 1; j < NumVar; j++)
		{
			if (mt[0][j] > max)
			{
				max = mt[0][j];
				MaxJ = j;
			}
		}
		if (max <= 0)
		{
			out << "have found the optimal solution" << std::endl << endl;
			out.close();
			return;
		}

		Fraction MinI_RHS = 0;
		int MinI = 0;
		for (int i = 1; i < NumCondition + 1; i++)
		{
			if (mt[i][MaxJ] > 0)
			{
				Fraction result = mt[i][NumVar] / mt[i][MaxJ];
				if ((result < MinI_RHS && result != 0) || MinI_RHS == 0)
				{
					MinI_RHS = result;
					MinI = i;
				}
			}
		}
		if (MinI_RHS <= 0)
		{
			out << "the objective function is unbounded" << std::endl;
			print();
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
		out << 'x' << MaxJ + 1 << " " << "enter" << "  " << 'x' << BasicVar[MinI - 1] + 1 << " " << "leave" << std::endl;
		BasicVar[MinI - 1] = MaxJ;
		rotation(MinI, MaxJ);
	}
}

void Lp::rotation(int x, int y)
{
	int SizeRow = mt[0].size();
	int SizeCol = mt.size();


	for (int i = 0; i < SizeCol; i++)
	{
		if (i == x)
		{
			Fraction f = Fraction(1) / mt[i][y];
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = mt[i][j] * f;
			}
		}
		else
		{
			Fraction f = mt[i][y] / mt[x][y];
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = mt[i][j] - mt[x][j] * f;
			}
		}
	}
}

void Lp::tfm()
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "output.txt", std::ios::app);
	int SizeRow = mt[0].size();
	int SizeCol = mt.size();
	int NumSup = 0;
	std::vector<int> ju;
	for (int i = 1; i < SizeCol; i++)
	{
		if (mt[i][SizeRow - 1] < 0)
		{
			BasicVar[i - 1] += NumCondition;
			ju.push_back(i);
			NumSup++;
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = Fraction(0) - mt[i][j];
			}
		}
	}                                                   //将负数约束标记，转化为正数约束

	std::vector<Fraction> v_f = mt[0];
	for (int i = 0; i < SizeCol; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = 0;
			}
			mt[i].insert(mt[i].end() - 1, NumSup, Fraction(-1));
		}
		else
		{
			mt[i].insert(mt[i].end() - 1, NumSup, Fraction(0));
		}
	}
	SizeRow = mt[0].size();

	for (int i = 0, j = NumVar; i < NumSup; i++, j++)
	{
		mt[ju[i]][j] = 1;
	}
	out << endl << "the following is the matrix after the artificial variable is added" << std::endl;

	NumVar += NumSup;               //为调用cal做准备
	for (int i = 0; i < NumSup; i++)
	{
		for (int j = 0; j < SizeRow; j++)
		{
			mt[0][j] = mt[0][j] + mt[ju[i]][j];
		}
	}                                                    //将目标函数系数消去
	cal();                                               //将加入人工变量的矩阵进行运算

	for (int i=0;i<NumCondition;i++)
	{
		if (BasicVar[i] >= NumVar - NumSup)
		{
			out << "there is no feasible solution to the original problem when the artificial variables are not all away from the base" << std::endl;
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
	}

	mt[0] = v_f;
	for (int i = 1; i < SizeCol; i++)
	{
		mt[i].erase(mt[i].end() - 1 - NumSup, mt[i].end() - 1);
	}
	NumVar -= NumSup;
	SizeRow = mt[0].size();                              //将人工变量消去
	out << endl << "the following manual variables are removed" << std::endl;
	print();

	for (int i = 0; i < NumCondition; i++)
	{
		int k = BasicVar[i];
		if (mt[0][k] != 0)
		{
				
			Fraction f = mt[0][k] / mt[i+1][k];
			for (int x = 0; x < SizeRow; x++)
			{
				mt[0][x] = mt[0][x] - mt[i+1][x] * f;
			}
		}
	}                                                    //将目标函数系数消去
	FirstBasicVar = BasicVar;
	out << "after elimination of the coefficients of the base variable in the objective function" << endl;
	out.close();
	return;
}

void Lp::dual()                      //使用对偶单纯形法
{
	print();
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "output.txt", std::ios::app);
	out << "the following procedure yields a dual feasible solution" << endl << endl;

	int count = 0;
	while (1)                                                 //以上过程得到对偶可行的解
	{
		bool judge = 0;
		count++;
		for (int j = 0; j < NumVar; j++)
		{
			if (mt[0][j] > 0)
			{
				judge = 1;
				for (int i = 1; i < NumCondition + 1; i++)
				{
					if (mt[i][j] > 0)
					{
						out << 'x' << j + 1 << " " << "enter" << "  " << 'x' << BasicVar[i - 1] + 1 << " " << "leave" << std::endl;
						BasicVar[i - 1] = j;
						rotation(i, j);
						print();
					}

				}
			}
		}
		if (!judge)
		{
			break;
		}
                                             //打印出变化过程
		if (count == 50)
		{
			out << "count too much wrong" << std::endl;
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
	}
	
	out << "dual feasible solutions have been obtained" << std::endl;
	out << "the following entry into the base off process" << std::endl;

	count = 0;
	while (1)                                                      //开始进基离基
	{
		print();
		
		count++;
		if (count == 50)
		{
			out << "too much count wrong" << std::endl;
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
		Fraction MinI_RHS=mt[1][NumVar];
		int MinI = 1;
		for (int i = 2; i < NumCondition + 1; i++)
		{
			if (mt[i][NumVar] < MinI_RHS)
			{
				MinI_RHS = mt[i][NumVar];
				MinI = i;
			}
		}
		if (MinI_RHS >= 0)
		{
			out << "have found the optimal solution" << std::endl << endl;
			out.close();
			return;
		}

		Fraction MinJ_R = 0;
		int MinJ = 0;
		bool b = 0;
		for (int j = 0; j < NumVar; j++)
		{
			if (mt[MinI][j] < 0)
			{
				b = 1;
				Fraction result = mt[0][j] / mt[MinI][j];
				if (result < MinJ_R || MinJ_R == 0)
				{
					MinJ_R = result;
					MinJ = j;
				}
			}
		}                           //不存在检验数(对偶可行解)为0的情况
		if (b)
		{
			out << 'x' << MinJ + 1 << " enter" <<"  "<<'x' << BasicVar[MinI - 1] + 1 << " leave" << std::endl;
			BasicVar[MinI - 1] = MinJ;
			rotation(MinI, MinJ);
		}
		else
		{
			out << "Unable to proceed to enter or leave base, there is no feasible solution for the original problem" << std::endl;
			out.close();
			ShowPageScene::wrong_tag = 1;
			return;
		}
	}
}

void Lp::add_var()
{
	ifstream input(FileUtils::getInstance()->getWritablePath() + "add_var.txt");
	int c;
	input >> c;
	target_func.push_back(c);

	vector<Fraction> v_a;
	for (int i = 0; i < NumCondition; i++)
	{
		int a;
		input >> a;
		v_a.push_back(a);
	}
	input.close();

	vector<Fraction> v_y;
	Fraction z(0);
	for (int i = 1; i < NumCondition + 1; i++)
	{
		Fraction y(0);
		for (int j = 0; j < NumCondition; j++)
		{
			y = y + mt[i][FirstBasicVar[j]] * v_a[j];
		}
		
		mt[i].insert(mt[i].end() - 1, y);
		z = z + y* target_func[BasicVar[i - 1]];
	}

	mt[0].insert(mt[0].end() - 1, z - c);
	NumVar++;

	cal();
}

void Lp::add_condition()
{
    ifstream input(FileUtils::getInstance()->getWritablePath() + "add_condition.txt");
	std::vector<Fraction> var;
	for (int j = 0; j < NumVar-NumCondition; j++)
	{
		int a;
		input >> a;
		var.push_back(Fraction(a));
	}


	char sign1 = NULL;
	char sign2 = NULL;
	input >> sign1;
	input >> sign2;

	int rhs;
	input>> rhs;
	condition_r.push_back(rhs);

	//开始处理辅助变量
	for (int j = 0; j < NumCondition+1; j++)
	{
		if (j == NumCondition)
		{
			if (sign1 == '<')
			{
				var.push_back(Fraction(1));
			}
		    else
			{
				sign1 = '<';
				rhs = -rhs;
				for (int k = 0; k < var.size(); k++)
				{
					var[k] = Fraction(0) - var[k];
				}
				var.push_back(Fraction(1));
			}
		}
		else
		{
			var.push_back(Fraction(0));
		}
	}


	var.push_back(rhs);

	input.close();

	mt.push_back(var);
	NumCondition++;
	BasicVar.push_back(NumVar);
	FirstBasicVar.push_back(NumVar);
	NumVar++;
	for (int i = 0; i < NumCondition; i++)
	{
		mt[i].insert(mt[i].end() - 1, 0);
	}
	target_func.push_back(0);

	print();
	ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt", std::ios::app);
	output << "the following is a simplex table that eliminates the coefficients of the base variable" << endl;
	output.close();

	for (int i = 0; i < NumCondition-1; i++)
	{
		int k = BasicVar[i];
		if (mt[NumCondition][k] != 0)
		{
			Fraction f = mt[NumCondition][k] / mt[i + 1][k];
			for (int j = 0; j < NumVar + 1; j++)
			{
				mt[NumCondition][j] = mt[NumCondition][j] - mt[i + 1][j] * f;
			}
		}
	}                                                    //消去基变量系数

	
	dual();
}

void Lp::sensi_analyze()
{
	ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt", std::ios::app);
	output << endl << "The following is the sensitivity analysis of the non base variables in the objective function" << endl;
	for (int j = 0; j < NumVar; j++)
	{
		if (mt[0][j] != 0)
		{
			Fraction f = target_func[j] + mt[0][j];
			output << 'c' << j + 1 << ">=" << f << "  ";
		}
	}
	output << endl << "The following is the sensitivity analysis of the base variable in the objective function" << endl;

	for (int i = 1; i < NumCondition + 1; i++)
	{
		Fraction max(0);                              //最大值
		Fraction min(0);                              //最小值
		for (int j = 0; j < NumVar; j++)
		{
			if (j != BasicVar[i - 1])
			{
				if (mt[i][j] > 0)
				{
					Fraction f = mt[0][j] / mt[i][j];
					if (f > min || min == 0)
					{
						min = f;
					}
				}
				if (mt[i][j] < 0)
				{
					Fraction f = mt[0][j] / mt[i][j];
					if (f < max || max == 0)
					{
						max = f;
					}
				}
			}
		}

		if (min != 0 && max != 0)
		{
			min = min + target_func[BasicVar[i - 1]];
			max = max + target_func[BasicVar[i - 1]];
			output << min << "<=" << 'c' << BasicVar[i - 1] + 1 << "<=" << max << "  ";
		}
		else
		{
			if (min == 0)
			{
				max = max + target_func[BasicVar[i - 1]];
				output << 'c' << BasicVar[i - 1] + 1 << "<=" << max << "  ";
			}
			else
			{
				min = min + target_func[BasicVar[i - 1]];
				output << min << "<=" << 'c' << BasicVar[i - 1] + 1 << "  ";
			}
		}
	}
	
	output << endl << "The following is the sensitivity analysis of the right hand number" << endl;
	for (int j = 0; j < NumCondition ; j++)
	{
		Fraction max(0);                              //最大值
		Fraction min(0);                              //最小值
		
		int k = FirstBasicVar[j];
		for (int i = 1; i < NumCondition+1; i++)
		{
			if (mt[i][k] > 0)
			{
				Fraction f = Fraction(0) - (mt[i][NumVar] / mt[i][k]);
				if (f > min || min == 0)
				{
					min = f;
				}
			}
			if (mt[i][k] < 0)
			{
				Fraction f = Fraction(0) - (mt[i][NumVar] / mt[i][k]);
				if (f < max || max == 0)
				{
					max = f;
				}
			}
		}



		if (min != 0 && max != 0)
		{
			min = min + condition_r[j];
			max = max + condition_r[j];
			output << min << "<=" << 'b' << j+1 << "<=" << max << "  ";
		}
		else
		{
			if (min == 0)
			{
				max = max + condition_r[j];
				output << 'b' << j << "<=" << max << "  ";
			}
			else
			{
				min = min + condition_r[j];
				output << min << "<=" << 'b' << j+1 << "  ";
			}
		}
	}
	output << endl << endl;
	output.close();
}

extern std::vector<Fraction> best_result;
void int_lp(std::shared_ptr<Lp> p);
extern std::vector<std::vector<Fraction>> best_results;
vector<int> int_lim;

void Lp::int_Lp()
{
	std::ifstream input(FileUtils::getInstance()->getWritablePath() + "IntInput.txt");
	std::ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt");
	int num = 0;

	input >> num;
	if (num == NumVar - NumCondition)
	{
		for (int i = 0; i < num; i++)
		{
			int_lim.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			int lim;
			input >> lim;
			int_lim.push_back(lim - 1);
		}
		sort(int_lim.begin(), int_lim.end());
		int_lim.erase(unique(int_lim.begin(), int_lim.end()), int_lim.end());
	}
	for (const auto&x : int_lim)
	{			
		output << 'x' << x + 1 << " ";
	}
		output << "is integer" << endl;
	if (cal_noprint())
	{
		shared_ptr<Lp> p(new Lp(*this));
		int_lp(p);
		if (!best_result.empty())
		{
			output << endl << "the optimal integer solution is as follows" << endl << endl;
			for (const auto &x : best_results)
			{
				int size = x.size();
				for (int i = 0; i < size-1; i++)
				{
					output << 'x' << i + 1 << '=' << x[i] << endl;
				}
				output << 'z' << '=' << x[size - 1] << endl;
				output << endl;
			}
		}
		else
		{
			output << "the original problem has no feasible integer solution" << endl;
			ShowPageScene::wrong_tag = 1;
		}
	}
	else
	{
		output << "the original problem has no solution" << endl;
		ShowPageScene::wrong_tag = 1;
	}
	input.close();
	output.close();
}



bool Lp::cal_noprint()
{
	bool judge = 0;
	for (int i = 1; i < NumCondition + 1; i++)
	{
		if (mt[i][NumVar] < 0)
		{
			judge = 1;
		}
	}
	if (judge == 1)
	{
		if (!tfm_noprint())
		{
			return 0;
		}
	}

	int count = 0;
	while (1)
	{
		count++;
		if (count == 50)
		{
			std::ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt",ios::app);
			output << "count too much" << std::endl;
			output.close();
			delete this;
			exit(0);
		}
		Fraction max = mt[0][0];
		int MaxJ = 0;
		for (int j = 1; j < NumVar; j++)
		{
			if (mt[0][j] > max)
			{
				max = mt[0][j];
				MaxJ = j;
			}
		}
		if (max <= 0)
		{
			return 1;
		}

		Fraction MinI_RHS = 0;
		int MinI = 0;
		for (int i = 1; i < NumCondition + 1; i++)
		{
			if (mt[i][MaxJ] > 0)
			{
				Fraction result = mt[i][NumVar] / mt[i][MaxJ];
				if ((result < MinI_RHS && result != 0) || MinI_RHS == 0)
				{
					MinI_RHS = result;
					MinI = i;
				}
			}
		}
		if (MinI_RHS <= 0)
		{
			std::ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt",ios::app);
			output << "no bound" << std::endl;
			output.close();
			delete this;
			exit(0);
		}
		BasicVar[MinI - 1] = MaxJ;
		rotation(MinI, MaxJ);
	}
}

bool Lp::tfm_noprint()
{
	int SizeRow = mt[0].size();
	int SizeCol = mt.size();
	int NumSup = 0;
	std::vector<int> ju;
	for (int i = 1; i < SizeCol; i++)
	{
		if (mt[i][SizeRow - 1] < 0)
		{
			BasicVar[i - 1] += NumCondition;
			ju.push_back(i);
			NumSup++;
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = Fraction(0) - mt[i][j];
			}
		}
	}                                                   //将负数约束标记，转化为正数约束

	std::vector<Fraction> v_f = mt[0];
	for (int i = 0; i < SizeCol; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < SizeRow; j++)
			{
				mt[i][j] = 0;
			}
			mt[i].insert(mt[i].end() - 1, NumSup, Fraction(-1));
		}
		else
		{
			mt[i].insert(mt[i].end() - 1, NumSup, Fraction(0));
		}
	}
	SizeRow = mt[0].size();

	for (int i = 0, j = NumVar; i < NumSup; i++, j++)
	{
		mt[ju[i]][j] = 1;
	}

	NumVar += NumSup;               //为调用cal做准备
	for (int i = 0; i < NumSup; i++)
	{
		for (int j = 0; j < SizeRow; j++)
		{
			mt[0][j] = mt[0][j] + mt[ju[i]][j];
		}
	}                                                    //将目标函数系数消去
	cal_noprint();                                               //将加入人工变量的矩阵进行运算

	for (int i = 0; i<NumCondition; i++)
	{
		if (BasicVar[i] >= NumVar - NumSup)
		{
			return 0;
		}
	}

	mt[0] = v_f;
	for (int i = 1; i < SizeCol; i++)
	{
		mt[i].erase(mt[i].end() - 1 - NumSup, mt[i].end() - 1);
	}
	NumVar -= NumSup;
	SizeRow = mt[0].size();                              //将人工变量消去

	for (int i = 0; i < NumCondition; i++)
	{
		int k = BasicVar[i];
		if (mt[0][k] != 0)
		{

			Fraction f = mt[0][k] / mt[i + 1][k];
			for (int x = 0; x < SizeRow; x++)
			{
				mt[0][x] = mt[0][x] - mt[i + 1][x] * f;
			}
		}
	}                                                    //将目标函数系数消去
	FirstBasicVar = BasicVar;
	return 1;
}

bool Lp::add_condition_noprint(std::vector<Fraction> var)  //返回1成功计算，返回0无可行解
{
	mt.push_back(var);
	NumCondition++;
	BasicVar.push_back(NumVar);
	FirstBasicVar.push_back(NumVar);
	NumVar++;
	for (int i = 0; i < NumCondition; i++)
	{
		mt[i].insert(mt[i].end() - 1, 0);
	}
	target_func.push_back(0);
	for (int i = 0; i < NumCondition - 1; i++)
	{
		int k = BasicVar[i];
		if (mt[NumCondition][k] != 0)
		{
			Fraction f = mt[NumCondition][k] / mt[i + 1][k];
			for (int j = 0; j < NumVar + 1; j++)
			{
				mt[NumCondition][j] = mt[NumCondition][j] - mt[i + 1][j] * f;
			}
		}
	}

	if (dual_noprint())
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

bool Lp::dual_noprint()           //返回1成功计算，返回0无可行解
{


	//使用此函数时，对偶必然可行，因此不需要找到对偶可行基。
	int count = 0;
	while (1)                                                      //开始进基离基
	{
		count++;
		if (count == 50)
		{
			std::ofstream output(FileUtils::getInstance()->getWritablePath() + "output.txt",ios::app);
			output << "count too much" << std::endl;
			output.close();
			delete this;
			exit(0);
		}
		Fraction MinI_RHS = mt[1][NumVar];
		int MinI = 1;
		for (int i = 2; i < NumCondition + 1; i++)
		{
			if (mt[i][NumVar] < MinI_RHS)
			{
				MinI_RHS = mt[i][NumVar];
				MinI = i;
			}
		}
		if (MinI_RHS >= 0)
		{
			return 1;
		}

		Fraction MinJ_R = 0;
		int MinJ = 0;
		bool b = 0;
		for (int j = 0; j < NumVar; j++)
		{
			if (mt[MinI][j] < 0)
			{
				b = 1;
				Fraction result = mt[0][j] / mt[MinI][j];
				if (result < MinJ_R || MinJ_R == 0)
				{
					MinJ_R = result;
					MinJ = j;
				}
			}
		}                           //不存在检验数(对偶可行解)为0的情况
		if (b)
		{
			BasicVar[MinI - 1] = MinJ;
			rotation(MinI, MinJ);
		}
		else
		{
			return 0;
		}
	}
}


std::vector<Fraction> Lp::parse(bool b, int x, int value)
{
	vector<Fraction> condi;
	if (b == 0)
	{
		for (int j = 0; j < NumVar; j++)                         
  		{
			if (j == x)
			{
				condi.push_back(1);
			}
			else
			{
				condi.push_back(0);
			}
		}
		condi.push_back(1);
		condi.push_back(value);
	}
	else
	{
		for (int j = 0; j < NumVar; j++)
		{
			if (j == x)
			{
				condi.push_back(-1);
			}
			else
			{
				condi.push_back(0);
			}
		}
		condi.push_back(1);
		condi.push_back(-value);
	}
	return condi;
}




std::vector<Fraction> Lp::result_cal()
{
	vector<Fraction> result;
	for (int j = 0; j < NumVar - NumCondition; j++)
	{
		bool bo = 0;
		for (int i = 0; i < NumCondition; i++)
		{
			if (BasicVar[i] == j)
			{
				bo = 1;
				result.push_back(mt[i + 1][NumVar]);
			}
		}
			if (!bo)
			{
				result.push_back(0);
			}
		}
	result.push_back(mt[0].back());
	return result;
}
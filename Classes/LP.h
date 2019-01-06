#pragma once
#include <vector>
#include "Fraction.h"
#include <memory>

class Lp
{
private:
	int NumVar;
	int NumCondition;
	std::vector<std::vector<Fraction>> mt;
	std::vector<int> BasicVar;
	std::vector<int> FirstBasicVar;
	std::vector<int> condition_r;
	std::vector<int> target_func;
	void tfm();
	void rotation(int x, int y); 

	bool tfm_noprint();      //返回1成功计算，返回0说明无可行解                     //用于解决整数规划
 	bool cal_noprint();      //返回1成功计算，返回0无可行解
	bool dual_noprint();           //返回1成功计算，返回0无可行解

public:
	Lp();
	void print();
	void enter();
	void cal();                       //使用单纯形法
	void dual();                      //使用对偶单纯形法
	void add_var();                   //增加一个变量
	void add_condition();             //增加一个约束
	void sensi_analyze();             //对目标函数系数和右边常数进行灵敏度分析
	void int_Lp();                    //使用整数规划
	std::vector<Fraction> result_cal();   //计算当前的结果
	bool add_condition_noprint(std::vector<Fraction> var);  //返回1成功计算，返回0无可行解
	std::vector<Fraction> parse(bool b, int x, int value);
};
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

	bool tfm_noprint();      //����1�ɹ����㣬����0˵���޿��н�                     //���ڽ�������滮
 	bool cal_noprint();      //����1�ɹ����㣬����0�޿��н�
	bool dual_noprint();           //����1�ɹ����㣬����0�޿��н�

public:
	Lp();
	void print();
	void enter();
	void cal();                       //ʹ�õ����η�
	void dual();                      //ʹ�ö�ż�����η�
	void add_var();                   //����һ������
	void add_condition();             //����һ��Լ��
	void sensi_analyze();             //��Ŀ�꺯��ϵ�����ұ߳������������ȷ���
	void int_Lp();                    //ʹ�������滮
	std::vector<Fraction> result_cal();   //���㵱ǰ�Ľ��
	bool add_condition_noprint(std::vector<Fraction> var);  //����1�ɹ����㣬����0�޿��н�
	std::vector<Fraction> parse(bool b, int x, int value);
};
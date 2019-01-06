#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;



class AskConditionScene2 :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //ѯ�ʸ���������
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //�����༭
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text)
	{
		if (editBox->getTag() == 101)
		{
			Var = text;
		}
		if (editBox->getTag() == 102)
		{
			RightVar = text;
		}
		if (editBox->getTag() == 103)
		{
			sign = text;
		}
	}; //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //����return��

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AskConditionScene2);
	void menuCloseCallback(cocos2d::Ref* pSender);
	static bool tag_add;                  //������ӱ���
	static bool tag;                       //���ڶ�ȡһ��NumVar��NumCondition��
	static int NumVar;
	static int NumCondition;
	static int count;


private:
	std::string Var;
	std::string sign;
	std::string RightVar;
	void changeToNextScene(cocos2d::Ref* pSender);
};
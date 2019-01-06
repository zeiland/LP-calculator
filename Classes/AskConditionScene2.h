#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;



class AskConditionScene2 :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //询问各条件参数
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //开始编辑
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //结束编辑
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
	}; //编辑框文字改变
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //触发return后

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AskConditionScene2);
	void menuCloseCallback(cocos2d::Ref* pSender);
	static bool tag_add;                  //用于添加变量
	static bool tag;                       //用于读取一次NumVar和NumCondition。
	static int NumVar;
	static int NumCondition;
	static int count;


private:
	std::string Var;
	std::string sign;
	std::string RightVar;
	void changeToNextScene(cocos2d::Ref* pSender);
};
#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class AskConditionScene1 :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //询问变量和条件个数
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //开始编辑
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //结束编辑
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) 
	{
		if (editBox->getTag() == 101)
		{
			NumVar = text;
		}
		if (editBox->getTag() == 102)
		{
			NumCondition = text;
		}
	}; //编辑框文字改变
	virtual void editBoxReturn(EditBox* editBox) 
	{};                               //触发return后

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AskConditionScene1);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	std::string NumVar;
	std::string NumCondition;
	void changeToAskMinConditionScene(cocos2d::Ref* pSender);
};
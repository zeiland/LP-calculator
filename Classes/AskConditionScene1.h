#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class AskConditionScene1 :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //ѯ�ʱ�������������
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //�����༭
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
	}; //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox) 
	{};                               //����return��

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AskConditionScene1);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	std::string NumVar;
	std::string NumCondition;
	void changeToAskMinConditionScene(cocos2d::Ref* pSender);
};
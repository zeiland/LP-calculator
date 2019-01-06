#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class IntProgrammingInputScene :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //ѯ�ʱ�������������
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //�����༭
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text)
	{
		
		if (tag == 0)
		{
			int_num = text;
		}
		else
		{
			int_position = text;
		}

	}; //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //����return��

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntProgrammingInputScene);
	void menuCloseCallback(cocos2d::Ref* pSender);

	static bool  tag;
	static std::string int_num;
private:
	

	std::string int_position;
	int NumVar;
	void changeToNextScene(cocos2d::Ref* pSender);
	void begin_cal();
};
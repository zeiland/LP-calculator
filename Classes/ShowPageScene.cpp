#include "ShowPageScene.h"
#include <iostream>
#include <fstream>
#include "UI.h"
#include "AskConditionScene2.h"
#include "AddVarScene.h"
#include "MainScene.h"
#include "IntProgrammingInputScene.h"

USING_NS_CC;

bool ShowPageScene::tag(0);
bool ShowPageScene::wrong_tag(0);

Scene* ShowPageScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShowPageScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool ShowPageScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add "HelloWorld" splash screen"

	std::string text;
	std::ifstream textFile(FileUtils::getInstance()->getWritablePath() + "output.txt");
	if (textFile.is_open())
	{
		std::ostringstream temp;
		temp << textFile.rdbuf();
		text = temp.str();
		textFile.close();
	}
	else
	{
		CCLOG("ShowWrong!");
		Director::getInstance()->end();
	}
	LabelTTF *label = LabelTTF::create(text, "Consolas", 20);
	label->setPosition(0, visibleSize.height);
	addChild(label);

	auto listener1 = EventListenerTouchOneByOne::create();
	     listener1->setSwallowTouches(true);

	     //通过 lambda 表达式 直接实现触摸事件的回掉方法
	 listener1->onTouchBegan = [](Touch* touch, Event* event) 
	 {
		 auto target = static_cast<Sprite*>(event->getCurrentTarget());

	     Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		 Size s = target->getContentSize();
         Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
		    log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		    return true;
		}
	        return false;
	 };

	
		
	 listener1->onTouchMoved = [](Touch* touch, Event* event)
	 {
           auto target = static_cast<Sprite*>(event->getCurrentTarget());
		   target->setPosition(target->getPosition() + touch->getDelta());
	 };

	 listener1->onTouchEnded = [=](Touch* touch, Event* event) 
	 {
		   auto target = static_cast<Sprite*>(event->getCurrentTarget());
		   log("sprite onTouchesEnded.. ");
	 };
	
		
		     //将触摸事件绑定到精灵身上
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, label);



	auto button_add_var = MenuItemImage::create(
		"button7.png",
		"button7.png",
		CC_CALLBACK_1(ShowPageScene::add_var, this));

	button_add_var->setPosition(Vec2(visibleSize.width / 2 + origin.x+170, visibleSize.height / 2 + origin.y + 100));
	auto size_button_add_var = button_add_var->getContentSize();
	button_add_var->setScale((0.2f*visibleSize.width) / size_button_add_var.width, (0.15f*visibleSize.height) / size_button_add_var.height);

	auto button_add_condition = MenuItemImage::create(
		"button8.png",
		"button8.png",
		CC_CALLBACK_1(ShowPageScene::add_condition, this));

	button_add_condition->setPosition(Vec2(visibleSize.width / 2 + origin.x+170, visibleSize.height / 2 + origin.y+50));
	auto size_button_add_condition = button_add_condition->getContentSize();
	button_add_condition->setScale((0.2f*visibleSize.width) / size_button_add_condition.width, (0.15f*visibleSize.height) / size_button_add_condition.height);

	auto button_sen_analysis = MenuItemImage::create(
		"button9.png",
		"button9.png",
		CC_CALLBACK_1(ShowPageScene::sen_analysis, this));

	button_sen_analysis->setPosition(Vec2(visibleSize.width / 2 + origin.x + 170, visibleSize.height / 2 + origin.y));
	auto size_button_sen_analysis = button_sen_analysis->getContentSize();
	button_sen_analysis->setScale((0.2f*visibleSize.width) / size_button_sen_analysis.width, (0.15f*visibleSize.height) / size_button_sen_analysis.height);


	auto button_restart = MenuItemImage::create(
		"button10.png",
		"button10.png",
		CC_CALLBACK_1(ShowPageScene::restart, this));

	button_restart->setPosition(Vec2(visibleSize.width / 2 + origin.x + 170, visibleSize.height / 2 + origin.y - 50));
	auto size_button_restart = button_add_var->getContentSize();
	button_restart->setScale((0.2f*visibleSize.width) / size_button_restart.width, (0.15f*visibleSize.height) / size_button_restart.height);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ShowPageScene::menuCloseCallback, this));

	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));




	// create menu, it's an autorelease object
	if (tag == 0&&wrong_tag==0)
	{
		auto menu = Menu::create(button_add_var, button_add_condition, button_sen_analysis, button_restart, closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);
	}
	else
	{
		auto menu = Menu::create(button_restart, closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);
	}
	return true;
}







void ShowPageScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	UIgetInstance().deleteLp();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


void ShowPageScene::add_var(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode3.txt");
	if (out.is_open())
	{
		out << 'A' << std::endl;
		out.close();
		Director::getInstance()->replaceScene(AddVarScene::createScene());
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
}
void ShowPageScene::add_condition(cocos2d::Ref* pSender)
{
	AskConditionScene2::tag_add = 1;
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode3.txt");
	if (out.is_open())
	{
		out << 'B' << std::endl;
		out.close();
		Director::getInstance()->replaceScene(AskConditionScene2::createScene());
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
}
	
void ShowPageScene::sen_analysis(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode3.txt");
	if (out.is_open())
	{
		out << 'C' << std::endl;
		out.close();
		UIgetInstance().Trd_in();
		Director::getInstance()->replaceScene(ShowPageScene::createScene());
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
}



extern std::vector<Fraction> best_result;
extern std::vector<std::vector<Fraction>> best_results;
extern std::vector<int> int_lim;


void ShowPageScene::restart(cocos2d::Ref* pSender)
{
	UIgetInstance().deleteLp();
	best_result.clear(); best_results.clear(); int_lim.clear();
	tag = 0;
	wrong_tag = 0;
	AskConditionScene2::NumVar = 0;
	AskConditionScene2::NumCondition = 0;
	AskConditionScene2::tag = 0;
	AskConditionScene2::count = 0;
	IntProgrammingInputScene::tag = 0;
	IntProgrammingInputScene::int_num.clear();
	Director::getInstance()->replaceScene(MainScene::createScene());
}

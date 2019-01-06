#include "AskMinConditionScene.h"
#include <iostream>
#include <fstream>
#include "AskConditionScene2.h"
#include "other functions.h"

USING_NS_CC;

Scene* AskMinConditionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AskMinConditionScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool AskMinConditionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	std::ifstream in(FileUtils::getInstance()->getWritablePath() + "input.txt");
	if (in.is_open())
	{
		in >> NumVar;
		in.close();
		CCLOG("RIGHT");
	}
	else
	{
		CCLOG("WRONG!");
		Director::getInstance()->end();
	}




	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add "HelloWorld" splash screen"
	auto tip1 = Sprite::create("tip3.png");

	// position the sprite on the center of the screen
	tip1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
	auto size_tip1 = tip1->getContentSize();
	tip1->setScale((0.7f*visibleSize.width) / size_tip1.width, (0.4f*visibleSize.height) / size_tip1.height);
	this->addChild(tip1, 0);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(AskMinConditionScene::menuCloseCallback, this));


	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));

	// create menu, it's an autorelease object

	Size MinConditionSize = CCSizeMake(300, 60);
	EditBox* MinCondition = EditBox::create(MinConditionSize, Scale9Sprite::create("white_ground.png"));;
	MinCondition->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-40 ));
	this->addChild(MinCondition);

	MinCondition->setFontName("fonts/Paint Boy.ttf");
	MinCondition->setFontSize(30);
	MinCondition->setFontColor(Color3B(0, 0, 0));
	MinCondition->setMaxLength(30); //限制字符长度
	MinCondition->setDelegate(this);



	auto button_complete = MenuItemImage::create(
		"complete.png",
		"complete.png",
		CC_CALLBACK_1(AskMinConditionScene::changeToAskConditionScene2, this));

	button_complete->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 125));
	auto size_button_complete = button_complete->getContentSize();
	button_complete->setScale((0.27f*visibleSize.width) / size_button_complete.width, (0.15f*visibleSize.height) / size_button_complete.height);

	auto menu = Menu::create(button_complete, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void AskMinConditionScene::changeToAskConditionScene2(cocos2d::Ref* pSender)
{
	if (isValid(MinCondition, NumVar))
	{
		std::ofstream out(FileUtils::getInstance()->getWritablePath() + "input.txt", std::ios::app);
		if (out.is_open())
		{
			out << MinCondition << std::endl;
			out.close();
			Director::getInstance()->replaceScene(AskConditionScene2::createScene());
		}
		else
		{
			CCLOG("WRONG");
			Director::getInstance()->end();
		}
	}
	else
	{

		auto visibleSize = Director::getInstance()->getVisibleSize();

		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto WrongTip = Sprite::create("tip14.png");
		// position the sprite on the center of the screen
		WrongTip->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 90));
		auto size_tip1 = WrongTip->getContentSize();
		WrongTip->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.07f*visibleSize.height) / size_tip1.height);
		this->addChild(WrongTip, 0);
	}
}
void AskMinConditionScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
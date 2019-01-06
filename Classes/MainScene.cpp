#include "MainScene.h"
#include <iostream>
#include <fstream>
#include "AskConditionScene1.h"
#include "UI.h"
#include "ShowPageScene.h"
#include "IntProgrammingInputScene.h"

USING_NS_CC;


Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene -> addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
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
	auto title = Sprite::create("title.png");

	// position the sprite on the center of the screen
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	auto size_title = title->getContentSize();
	title->setScale((0.4f*visibleSize.width) / size_title.width, (0.3f*visibleSize.height) / size_title.height);
	this->addChild(title, 0);

	auto tip13 = Sprite::create("tip13.png");

	// position the sprite on the center of the screen
	tip13->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50));
	auto size_tip13 = tip13->getContentSize();
	tip13->setScale((0.4f*visibleSize.width) / size_title.width, (0.2f*visibleSize.height) / size_title.height);
	this->addChild(tip13, 0);

	auto tip15 = Sprite::create("tip15.png");

	// position the sprite on the center of the screen
	tip15->setPosition(Vec2(visibleSize.width / 2+ + origin.x+35, visibleSize.height / 2 + origin.y+25 ));
	auto size_tip15 = tip15->getContentSize();
	tip15->setScale((0.4f*visibleSize.width) / size_title.width, (0.2f*visibleSize.height) / size_title.height);
	this->addChild(tip15, 0);
	
	auto tip16 = Sprite::create("tip16.png");

	// position the sprite on the center of the screen
	tip16->setPosition(Vec2(visibleSize.width / 2 + +origin.x , origin.y+25 ));
	auto size_tip16 = tip16->getContentSize();
	tip16->setScale((0.4f*visibleSize.width) / size_title.width, (0.2f*visibleSize.height) / size_title.height);
	this->addChild(tip16, 0);


	auto button_LP = MenuItemImage::create(
		"button1.png",
		"button1.png",
		CC_CALLBACK_1(MainScene::changeToAskConditionScene1, this));

	button_LP->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y -75));
	auto size_button_LP = button_LP->getContentSize();
	button_LP->setScale((0.27f*visibleSize.width) / size_button_LP.width, (0.15f*visibleSize.height) / size_button_LP.height);


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));


	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2-13,
		origin.y + closeItem->getContentSize().height / 2+10));

	// create menu, it's an autorelease object
	auto menu = Menu::create(button_LP, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainScene::menuCloseCallback(Ref* pSender)
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
void MainScene::changeToAskConditionScene1(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode1.txt");
	if (out.is_open())
	{
		out << 'A' << std::endl;
		out.close();
	}
	else
	{
		CCLOG("WRONGmode1");
		Director::getInstance()->end();
	}
	Director::getInstance()->replaceScene(AskConditionScene1::createScene());
}




Scene* MainScene2::createScene()
{

	auto scene = Scene::create();
	auto layer = MainScene2::create();

	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene2::init()
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
	auto title = Sprite::create("title.png");

	// position the sprite on the center of the screen
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	auto size_title = title->getContentSize();
	title->setScale((0.4f*visibleSize.width) / size_title.width, (0.3f*visibleSize.height) / size_title.height);
	this->addChild(title, 0);


	auto button_simplex_method = MenuItemImage::create(
		"button3.png",
		"button3.png",
		CC_CALLBACK_1(MainScene2::do_simplex_method, this));

	button_simplex_method->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+25));
	auto size_button_simplex_method = button_simplex_method->getContentSize();
	button_simplex_method->setScale((0.27f*visibleSize.width) / size_button_simplex_method.width, (0.15f*visibleSize.height) / size_button_simplex_method.height);

	auto button_dual_simplex_method = MenuItemImage::create(
		"button4.png",
		"button4.png",
		CC_CALLBACK_1(MainScene2::do_dual_simplex_method, this));

	button_dual_simplex_method->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 25));
	auto size_button_dual_simplex_method = button_dual_simplex_method->getContentSize();
	button_dual_simplex_method->setScale((0.27f*visibleSize.width) / size_button_dual_simplex_method.width, (0.15f*visibleSize.height) / size_button_dual_simplex_method.height);


	auto button_int_programming = MenuItemImage::create(
		"button5.png",
		"button5.png",
		CC_CALLBACK_1(MainScene2::do_int_programming, this));

	button_int_programming->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));
	auto size_button_int_programming = button_int_programming->getContentSize();
	button_int_programming->setScale((0.27f*visibleSize.width) / size_button_int_programming.width, (0.15f*visibleSize.height) / size_button_int_programming.height);




	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene2::menuCloseCallback, this));

	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2-13,
		origin.y + closeItem->getContentSize().height / 2+10));

	// create menu, it's an autorelease object
	auto menu = Menu::create(button_simplex_method, button_dual_simplex_method, button_int_programming, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainScene2::menuCloseCallback(Ref* pSender)
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

void MainScene2::do_simplex_method(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode2.txt");
	if (out.is_open())
	{
		out << 'A' << std::endl;
		out.close();
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
	begin_cal();
}
void MainScene2::do_dual_simplex_method(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode2.txt");
	if (out.is_open())
	{
		out << 'B' << std::endl;
		out.close();
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
	begin_cal();
}
void MainScene2::do_int_programming(cocos2d::Ref* pSender)
{
	std::ofstream out(FileUtils::getInstance()->getWritablePath() + "mode2.txt");
	if (out.is_open())
	{
		out << 'C' << std::endl;
		out.close();
		std::ofstream out(FileUtils::getInstance()->getWritablePath() + "IntInput.txt");
		out.close();
		Director::getInstance()->replaceScene(IntProgrammingInputScene::createScene());
	}
	else
	{
		CCLOG("WRONG2");
		Director::getInstance()->end();
	}
}

void MainScene2::begin_cal()
{
	CCLOG("BeginCal");
	UIgetInstance().Fst_in();
	CCLOG("BeginCalEnd");
	Director::getInstance()->replaceScene(ShowPageScene::createScene());
}
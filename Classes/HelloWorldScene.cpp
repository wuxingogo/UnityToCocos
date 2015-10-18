#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AnalyticsUnityToCocos.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    auto winSize = Director::getInstance()->getWinSize();
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    AnalyticsUnityToCocos::parseXML("MainMenu.xml");
    
    Node * container = AnalyticsUnityToCocos::container;
    getAllChild(container);
    container->setScale(0.3f);
    container->setPosition(winSize / 2);
    this->addChild(container);

    return true;
}

void HelloWorld::getAllChild(Node * root){
    CCLOG("root name is %s",root->getName().c_str());
    if (root->getChildren().size() > 0) {
        for ( auto item : root->getChildren()) {
            getAllChild(item);
        }
    }
}

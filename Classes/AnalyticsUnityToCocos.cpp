//
//  AnalyticsUnityToCocos.cpp
//  UnityToCocos
//
//  Created by ly on 8/16/15.
//
//

#include "AnalyticsUnityToCocos.h"
#include<iostream>
using namespace std;

Node* AnalyticsUnityToCocos::container = NULL;
Node* AnalyticsUnityToCocos::currentNode = NULL;


void AnalyticsUnityToCocos::parseXML(const char *fileName){
    container = Node::create();
    container->setContentSize(Director::getInstance()->getWinSize());
    currentNode = container;
    
    std::string filePath =FileUtils::getInstance()->fullPathForFilename(fileName);
    XMLDocument *pDoc = new XMLDocument();
    XMLError errorId = pDoc->LoadFile(filePath.c_str());
    if (errorId != 0) {
        //xml格式错误
        
        return;
    }
    XMLElement *rootEle = pDoc->RootElement();
    getAllChild(rootEle,currentNode);
//    const char * tex = rootEle->Attribute("mainTexture");
//    CCLOG("%s", rootEle->FirstChildElement()->Attribute("name"));
//    if (tex) {
//        CCLOG("asdf");
//    }
//    XMLElement *dicEle = rootEle->FirstChildElement();
  
//    const XMLElement * dic = const_case<const XMLElement*>(dicEle);
//    CCLOG("root Ele is %s",   rootEle->Attribute("name"));
    
//    CCLOG("dic Ele is %s", dic.FindAttribute("aa")->Name());
}

void AnalyticsUnityToCocos::getAllChild(tinyxml2::XMLElement *root, Node * appendNode){
    Node * targetNode = NULL;
    currentNode = appendNode;
    
    if (root->Attribute("mainTexture") != NULL) {
        
        if (strcmp("", root->Attribute("mainTexture")) != 0  ) {
            char fileName[30];
            sprintf(fileName, "%s%s",root->Attribute("mainTexture"),".png");
            if (FileUtils::getInstance()->isFileExist(fileName)) {
                
                targetNode = Sprite::create(fileName);
            }
           
            
        }
        
        if ( NULL == targetNode) {
            targetNode = Node::create();
        }
    }
    else if (root->Attribute("text") != NULL) {
        CCLOG("Label will be create %s",root->Attribute("name"));
        targetNode = Label::create();
        Label * target = (Label*)targetNode;
        target->setSystemFontSize(atof(root->Attribute("textSize")));
        target->setColor(attr2Color(root->Attribute("textColor")));
        target->setString(root->Attribute("text"));
//        targetNode = label;
////        label->setString(root->Attribute("text"));
//        currentNode->addChild(label);
//        currentNode = label;
//        targetNode = Node::create();
//        currentNode->addChild(targetNode);
    }else{
        CCLOG("Node will be create %s",root->Attribute("name"));
        targetNode = Node::create();
    }
    appendNode->addChild(targetNode);
   
//    targetNode->setContentSize(root->)
   
//    CCLOG("Node setposition is %f, %f", targetNode->getPosition().x, targetNode->getPositionY());
    const char * name = root->Attribute("name");
    
    Vec2 parentSize = Vec2(currentNode->getContentSize().width, currentNode->getContentSize().height);
    Vec2 currentSize = attr2Size(root->Attribute("size"));
    Vec2 pivot = attr2Size(root->Attribute("pivot"));
    Vec2 localPosition = attr2Size(root->Attribute("localposition"));
    Vec2 point = pivotWithSize( pivot , parentSize, localPosition );
    targetNode->setPosition( point );
//    if (currentSize.equals(Vec2::ZERO)) {
//        targetNode->setContentSize(appendNode->getContentSize());
//    }else{
//        targetNode->setContentSize(Size(currentSize.x, currentSize.y));
//    }
    
    targetNode->setName(name);
    targetNode->setVisible(attr2Bool(root->Attribute("visible")));
    if (root->NextSiblingElement() != NULL) {
        getAllChild(root->NextSiblingElement(),appendNode);
    }
    if (root->FirstChildElement() != NULL) {
        getAllChild(root->FirstChildElement(), targetNode);
    }
    
}

void AnalyticsUnityToCocos::strToArray(const char * str, float *array)
{
    string content(str);
    string::iterator it;

    while( 1 )
    {
        int nPos = content.find_first_of( '(' );
        if ( nPos != string::npos )
        {
            content =    content.substr( 0 , nPos ) + content.substr( nPos + 1 , -1 );
        }
        nPos = content.find_first_of( ')' );
        if ( nPos != string::npos )
        {
            content =    content.substr( 0 , nPos ) + content.substr( nPos + 1 , -1 );
        }
        nPos = content.find_first_of( ' ' );
        if ( nPos != string::npos )
        {
            content =    content.substr( 0 , nPos ) + content.substr( nPos + 1 , -1 );
        }
        else
            break;
    }
    
    int index = (int)content.find(',');
    string nextStr = content.substr(0, index);
    int i = 0;
    while (content.length() > 0)
    {
        nextStr = content.substr(0, index);
        array[i] = atof(nextStr.c_str());
        i++;
        
        index = (int)content.find(',') + 1;
        if(index == 0) index = content.length();
        content = content.substr(index, content.length());
    }
    
}

Color3B AnalyticsUnityToCocos::attr2Color(const char *str){
    string content(str);
    content = content.substr(4, content.length() - 1);
    
    char strPosition[30];
    strcpy( strPosition, content.c_str() );
    float * localPosition = new float[3];
    memset(localPosition, 0, sizeof(float)*3);
    strToArray(strPosition, localPosition);
    Color3B c= Color3B(localPosition[0] *255, localPosition[1] *255, localPosition[2] *255);
    delete localPosition;
    return c;
}

Vec2 AnalyticsUnityToCocos::attr2Point(const char *str){
    
    
    char strPosition[30];
    strcpy( strPosition, str );
    float * localPosition = new float[3];
    memset(localPosition, 0, sizeof(float)*3);
    strToArray(strPosition, localPosition);
    Vec2 v= Vec2(localPosition[0], localPosition[1]);
    
    delete localPosition;
    return v;
//    targetNode->setPosition(localPosition[0],localPosition[1]);
//    CCLOG("set position is %f, %f",localPosition[0],localPosition[1]);
}

Vec2 AnalyticsUnityToCocos::attr2Size(const char *str){
    char strPosition[30];
    strcpy( strPosition, str );
    float * localPosition = new float[2];
    memset(localPosition, 0, sizeof(float)*2);
    strToArray(strPosition, localPosition);
  
    Vec2 v =Vec2(localPosition[0], localPosition[1]);
//    delete localPosition;
//    if (v.equals(Vec2::ZERO)) {
//        return Vec2(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
//    }
    return v;

}

Vec2 AnalyticsUnityToCocos::pivotWithSize(cocos2d::Vec2 pivot, cocos2d::Vec2 size, cocos2d::Vec2 localp){
    
    return Vec2(pivot.x * size.x + localp.x, pivot.y * size.y + localp.y);
//    return Vec2( pivot.x * localp.x, pivot.y * localp.y );
//    return Vec2( pivot + localp );
}

bool AnalyticsUnityToCocos::attr2Bool(const char *str){
    return atoi(str);
}
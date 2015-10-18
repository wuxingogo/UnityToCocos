//
//  AnalyticsUnityToCocos.h
//  UnityToCocos
//
//  Created by ly on 8/16/15.
//
//

#ifndef __UnityToCocos__AnalyticsUnityToCocos__
#define __UnityToCocos__AnalyticsUnityToCocos__

#include <stdio.h>
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace tinyxml2;


class AnalyticsUnityToCocos {
    
public:
    static void parseXML(const char * fileName);
    
    static void getAllChild(XMLElement * root, Node * appendNode);
    
    static Node * container;
    
    static Node * currentNode;
    
    static void strToArray(const char * str, float *array);
    static Vec2 attr2Point(const char * str);
    static Vec2 attr2Size(const char * str);
    
    static Vec2 pivotWithSize(Vec2 pivot, Vec2 size, Vec2 localp);
    static Color3B attr2Color(const char * str);
    static bool attr2Bool(const char * str);
    
    
    
private:

};

#endif /* defined(__UnityToCocos__AnalyticsUnityToCocos__) */

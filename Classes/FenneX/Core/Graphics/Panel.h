/****************************************************************************
Copyright (c) 2013-2014 Auticiel SAS

http://www.fennex.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************///

#ifndef __FenneX__Panel__
#define __FenneX__Panel__

#include "Logs.h"
#include "cocos2d.h"
USING_NS_CC;
#include "RawObject.h"
#include "FenneXMacros.h"

NS_FENNEX_BEGIN

//TODO : finish implementation when needed : scrapped open/close for now, which is not needed yet
class Panel : public RawObject
{
public:
    virtual CCNode* getNode();
    
    //WARNING : experimental method, used to replace the standard node by a ClippingNode
    void setNode(CCNode* node);
    void setClippingNode(); //Will replace itself by a ClippingNode with a DrawNode stencil using ContentSize
    
    Panel(const char* panelName, CCPoint location);
    Panel(CCNode* node, const char* panelName = NULL);
    ~Panel();
    
    void addChild(RawObject* child);
    bool containsObject(RawObject* child);
    void removeChild(RawObject* child);
    void reorderChild(RawObject* child, int zOrder);
    void clear();
    CCArray* getChildren();
    
    //TODO : reorder methods when needed by GraphicLayer (protected and friend GraphicLayer ?)
    
    virtual void update(float deltaTime);
    
    virtual bool collision(CCPoint point);
    virtual bool collision(CCRect rect);
    virtual bool containsRect(CCRect rect);
    
protected:
    //the actual rendering layer for graphic objects stored
    CCNode* delegate;
    
    //Array containing graphic objects
    CCArray* children;
};
NS_FENNEX_END

#endif /* defined(__FenneX__Panel__) */

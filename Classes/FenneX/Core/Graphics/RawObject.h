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

#ifndef __FenneX__RawObject__
#define __FenneX__RawObject__

#include "Logs.h"
#include "cocos2d.h"
USING_NS_CC;
#include "Pausable.h"
#include "SynthesizeString.h"
#include "FenneXMacros.h"

NS_FENNEX_BEGIN
class RawObject : public CCObject
{
    CC_SYNTHESIZE_STRING(name, Name);
    CC_SYNTHESIZE_STRING(eventName, EventName);
    CC_SYNTHESIZE(bool, isEventActivated, EventActivated);
    CC_SYNTHESIZE_STRING(help, Help);
    CC_SYNTHESIZE_READONLY(int, identifier, ID);
public:
    
    //property-like methods that will actually call getNode
    virtual const CCPoint& getPosition();
    virtual void setPosition(const CCPoint& newPosition);
    const CCSize& getSize();
    const int getZOrder();
    const float getScale();
    void setScale(const float newScale);
    const float getScaleX();
    void setScaleX(const float newScale);
    const float getScaleY();
    void setScaleY(const float newScale);
    
    CCDictionary* getEventInfos();//Warning : the returned CCDictionary is copied, changes will not affect RawObject
    //Will not copy Sender automatically. Do it manually if required
    void addEventInfos(CCDictionary* infos);
    void setEventInfo(CCObject* obj, std::string key);
    void removeEventInfo(std::string key);
    //TODO : add opacity, isMoving
    
    RawObject();
    virtual ~RawObject();
    
    //mandatory to do for sub-class
    virtual CCNode* getNode() = 0;
    //virtual void update(float deltaTime) = 0; //already in CCObject
    
    //collisions methods
    virtual bool collision(CCPoint point);
    virtual bool collision(CCRect rect);
    virtual bool containsRect(CCRect rect);
    
    virtual void update(float deltatime) {};
    
    //TODO ? description, eventInfos handling, move methods, distance methods
    
    //Shitty code to go around the copy requirement
    virtual CCObject* copyWithZone(CCZone* pZone)
    {
        this->retain();
        return this;
    }
    
protected:
    CCDictionary* eventInfos;
};
NS_FENNEX_END

#endif /* defined(__FenneX__RawObject__) */

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

#ifndef __FenneX__InertiaGenerator__
#define __FenneX__InertiaGenerator__

#include "Logs.h"
#include "cocos2d.h"
#include "Pausable.h"
#include "FenneXMacros.h"

USING_NS_CC;

NS_FENNEX_BEGIN
class InertiaGenerator : public CCObject, public Pausable
{
public:
    static InertiaGenerator* sharedInertia(void);
    
    void planSceneSwitch(Ref* obj);
    void scrolling(CCObject* obj);
    void scrollingEnded(CCObject* obj);
    void stopInertia(CCObject* obj);
    virtual void update(float delta);
    
    //If a tap is recognized, no inertia is generated
    void tapRecognized(Ref* obj);
    void ignoreTouch(CCTouch* touch);
    
    void addPossibleTarget(CCObject* object);
    void addPossibleTargets(CCArray* array);
    
protected:
    void init();
    ~InertiaGenerator();
    
    CCArray* possibleTargets;
    CCArray* inertiaTargets;
    CCArray* inertiaParameters;
    
    CCDictionary* lastOffsets;
    CCArray* ignoredTouches;
    
    float currentTime;
    float lastInertiaNotificationTime;
};
NS_FENNEX_END

#endif /* defined(__FenneX__InertiaGenerator__) */

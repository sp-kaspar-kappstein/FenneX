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

#include "LayoutHandler.h"
#include "EventResponder.h"

NS_FENNEX_BEGIN

// singleton stuff
static LayoutHandler *s_SharedHandler = NULL;

LayoutHandler* LayoutHandler::sharedHandler(void)
{
    if (!s_SharedHandler)
    {
        s_SharedHandler = new LayoutHandler();
        s_SharedHandler->init();
    }
    
    return s_SharedHandler;
}

void LayoutHandler::init()
{
    responder = new EventResponder();
}

LayoutHandler::~LayoutHandler()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(responder);
    responder->release();
}

EventResponder* LayoutHandler::getResponder()
{
    return responder;
}

void LayoutHandler::linkToScene(Scene* target, bool initDisplay)
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(responder);
    currentScene = target;
    responder->currentScene = target;
    layer = GraphicLayer::sharedLayer();
    responder->layer = GraphicLayer::sharedLayer();
    if(initDisplay)
    {
        this->createSceneGraphics(target);
    }
    this->catchEvents(target);
}
NS_FENNEX_END

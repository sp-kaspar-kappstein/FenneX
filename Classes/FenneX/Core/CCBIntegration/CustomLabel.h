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

#ifndef __FenneX__CustomLabel__
#define __FenneX__CustomLabel__

#include "cocos2d.h"
#include "../extensions/cocos-ext.h"
#include "CustomBaseNode.h"
#include "LabelTTF.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

NS_FENNEX_BEGIN
class CustomLabel : public Label, public CustomBaseNode
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CustomLabel, create);
    bool init();
    CC_SYNTHESIZE(LabelFitType, fitType, FitType);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, const cocos2d::Value& pCCBValue);
};

class CustomLabelLoader : public LabelTTFLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CustomLabelLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CustomLabel);
};
NS_FENNEX_END

#endif /* defined(__FenneX__CustomLabel__) */
Cocos2d-x V3.2 Modifications
====

* build/cocos2d_lib/xcodeproj/project.pbxproj => updated project using Xcode suggestion
* cocos/math/CCGeometry.h => Size now subclass Ref (to allow using it in structures)
* [REMOVED]cocos/math/Vec2.h => Vec2 now subclass Ref (to allow using it in structures) => **don't do that, since it causes problem with DrawNode**
* cocos/2d/actions/CCActionManager.h/.cpp => add Vector<Action\*> ActionManager::getAllActionsForTarget(const Node* target)
* cocos/2d/actions/CCActionInterval.h/.cpp => add FiniteTimeAction\* getCurrentAction() const; and FiniteTimeAction\* getNextAction() const;
* cocos/2d/actions/CCActionInstant.h/.cpp => add SEL_CallFuncO getSelectorTarget() const;
* cocos/renderer/CCTextureCache.h/.cpp => add std::string getKeyForTexture(Texture2D* tex) const;
* cocos/deprecated/__Array.cpp => add lazy init in addObject, addObjectsFromArray and insertObject to avoid crash
* cocos/deprecated/__Array.cpp => secure containsObject, remove*, count, capacity for no data
* cocos/deprecated/CCArray.h => secure CC_ARRAY_FOREACH to work with no data
* cocos/2d/misc-nodes/CCClippingNode.h/.cpp => subclass CCActionTweenDelegate to be able to change width/height, add setSquareStencil() to use a square the size of ContentSize
* cocos/base/CCValue.h/.cpp => add VEC2 type
* cocos/platform/android/java/Cocos2dxActivity.java => change GLSurfaceView EGLConfigChooser for real devices (for ClippingNode)
* cocos/base/CCDirector.h/.cpp => add support for build version via setDisplayStats
* cocos/editor-support/cocosbuilder/CCNodeLoader.cpp => fix a problem with CCScale9Sprite preferedSize
* cocos2d/extensions/GUI/CCeditBox/CCEditBox.cpp => fix scaling problems for fontSize and contentSize
* cocos2d/extensions/GUI/CCeditBox/* => Add support for keyboard return type "Next"
* cocos2d/extensions/GUI/CCeditBox/* => editBoxReturn delegate is now called only for return button on iOS
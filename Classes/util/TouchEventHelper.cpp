#include "TouchEventHelper.h"

TouchEventHelper::TouchEventHelper():
_touchListener(NULL)
{}

TouchEventHelper::~TouchEventHelper() {
	CC_SAFE_RELEASE_NULL(_touchListener);
}

TouchEventHelper* TouchEventHelper::create() {
    auto obj = new TouchEventHelper;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool TouchEventHelper::init() {
  this->setTouchListenner(EventListenerTouchOneByOne::create());
  return true;
}

void TouchEventHelper::applyTouchListenner(Node* node){
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener,node);
}

void TouchEventHelper::removeTouchListenner(){
    Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
}


/** パラメータサンプル
this->setTouchListenner(EventListenerTouchOneByOne::create());
this->getTouchListenner();
*/

#include "ScrollNode.h"

ScrollNode::ScrollNode():
_calc(NULL),_touch(NULL),_scrollType(ScrollType::VERTICAL),_scrollWidth(10),_scrollPos(0)
{}

ScrollNode::~ScrollNode() {
	CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_touch);
}

ScrollNode* ScrollNode::create() {
    auto obj = new ScrollNode;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool ScrollNode::init() {
    if(!Node::init()){
        return false;
    }
    scheduleUpdate();
    
  return true;
}

void ScrollNode::update(float dt) {
    if(_touched){
        scrollSpeed = scrollSpeed * 0.8 + (_touchPt - _beforeTouchPt)*0.2/dt;
        _beforeTouchPt.set(_touchPt);
    }else{
        switch (getScrollType()) {
            case ScrollType::VERTICAL:
                if(abs(scrollSpeed.y)<minSpeed){
                    int diff = (int)getPosition().y % getScrollWidth();
                    int pos =  (int)getPosition().y / getScrollWidth();
                    if(diff){
                        if(diff > minSpeed * dt ){
                            setPosition(getPosition()-Vec2(0,minSpeed * dt));
                        }else{
                            setPosition(Vec2(getPosition().x, pos * getScrollWidth()));
                            setScrollPos(pos);
                        }
                    }
                }else{
                    setPosition(getPosition()+Vec2(0,scrollSpeed.y * dt));
                    if (scrollSpeed.y>0){
                        scrollSpeed.y -= dumpSpeedRate * dt;
                    }else{
                        scrollSpeed.y += dumpSpeedRate * dt;
                    }
                }
                break;
            case ScrollType::HORIZONTAL:
                
                break;
        }
    }
}

void ScrollNode::setTouchEvent(){
    setTouch(TouchEventHelper::create());
    getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        _touched = true;
        _touchPt.set(touch->getLocation());
        return true;
    };
    getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        if(_touched){
            Vec2 dpt = touch->getLocation() - _touchPt;
            switch (this->getScrollType()) {
                case ScrollType::VERTICAL:
                    setPosition(getPosition()+Vec2(0,dpt.y));
                    break;
                case ScrollType::HORIZONTAL:
                    setPosition(getPosition()+Vec2(dpt.x,0));
                    break;
            }
            _touchPt.set(touch->getLocation());
        }
        return true;
    };
    getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        _touched = false;
        return true;
    };
    getTouch()->applyTouchListenner(this);
}

/** パラメータサンプル
setCalc(Calclater::create());
getCalc();
*/

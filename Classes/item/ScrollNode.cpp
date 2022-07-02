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
    
    if(scrollSpeed.equals(Vec2::ZERO)){
        return;
    }
    
    if(_touched){
        scrollSpeed = scrollSpeed * 0.8 + (_touchPt - _beforeTouchPt)*0.2/dt;
        _beforeTouchPt.set(_touchPt);
    }else{
        int diff = (int)getPosition().y % getScrollWidth();
        int pos =  (int)getPosition().y / getScrollWidth();
        switch (getScrollType()) {
            case ScrollType::VERTICAL:
                if(pos>getMaxScrollPos()){
                    setPosition(Vec2(0,getScrollWidth() * getMaxScrollPos()));
                    scrollSpeed = Vec2::ZERO;
                    setScrollPos(getMaxScrollPos());
                }
                if(pos<getMinScrollPos()){
                    setPosition(Vec2(0,getScrollWidth() * getMinScrollPos()));
                    scrollSpeed = Vec2::ZERO;
                    setScrollPos(getMinScrollPos());
                }
                if(abs(scrollSpeed.y)<minSpeed){
                    if(diff){
                        if(diff > minSpeed * dt ){
                            setPosition(getPosition()-Vec2(0,minSpeed * dt));
                        }else{
                            setPosition(Vec2(getPosition().x, pos * getScrollWidth()));
                            scrollSpeed = 0;
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
        _touchPt.set(touch->getLocation());
        return true;
    };
    getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        Vec2 dpt = touch->getLocation() - _touchPt;
        int pos =  (int)getPosition().y / getScrollWidth();
        switch (this->getScrollType()) {
            case ScrollType::VERTICAL:
                if(pos>getMaxScrollPos()){
                    setPosition(Vec2(0,getScrollWidth() * getMaxScrollPos()));
                    scrollSpeed = Vec2::ZERO;
                    setScrollPos(getMaxScrollPos());
                    break;
                }
                if(pos<getMinScrollPos()){
                    setPosition(Vec2(0,getScrollWidth() * getMinScrollPos()));
                    scrollSpeed = Vec2::ZERO;
                    setScrollPos(getMinScrollPos());
                    break;
                }
                setPosition(getPosition()+Vec2(0,dpt.y));
                break;
            case ScrollType::HORIZONTAL:
                setPosition(getPosition()+Vec2(dpt.x,0));
                break;
        }
        _touchPt.set(touch->getLocation());
        _touched = true;
        return true;
    };
    getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        _touched = false;
        _touchPt.set(Vec2::ZERO);
        return true;
    };
    getTouch()->applyTouchListenner(this);
}

/** パラメータサンプル
setCalc(Calclater::create());
getCalc();
*/

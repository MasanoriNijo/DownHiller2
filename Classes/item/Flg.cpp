#include "Flg.h"

Flg::Flg(){}

Flg::~Flg() {
}

Flg* Flg::create() {
    auto obj = new Flg;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Flg::init() {
    if(!Sprite2::initWithFile("goalflg.png")){
        return false;
    }
    setAnchorPoint(Vec2(0.22,0));
    auto size = getContentSize();
    setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(-size.width/2 + size.width * 0.15,-size.height/2), Vec2(-size.width/2 + size.width * 0.15,size.height/2)));
    getPhysicsBody()->setGravityEnable(true);
    getPhysicsBody()->setCategoryBitmask(CT_GOAL);
    getPhysicsBody()->setCollisionBitmask(CT_NONE);
    getPhysicsBody()->setContactTestBitmask(CT_WHEEL);
    getPhysicsBody()->setDynamic(false);
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setTag(TG_GOAL);
    setGlobalZOrder(OBJ_LAYER_LV3);
  return true;
}

Flg* Flg::create(FlgType ftype) {
    auto obj = new Flg;
    if (obj && obj->init(ftype)) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Flg::init(FlgType ftype) {
    Size size_;
    switch (ftype) {
        case START:
            if(!Sprite2::initWithFile("startflg.png")){
                return false;
                break;
            }
            setAnchorPoint(Vec2(0.22,0));
            size_ = getContentSize();
            setGlobalZOrder(OBJ_LAYER_LV1-1);
            return true;
            break;
            
        case GOAL:
            if(!Sprite2::initWithFile("goalflg.png")){
                return false;
                break;
            }
            setAnchorPoint(Vec2(0.22,0));
            size_ = getContentSize();
            setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(-size_.width/2 + size_.width * 0.15,-size_.height/2), Vec2(-size_.width/2 + size_.width * 0.15,size_.height/2)));
            getPhysicsBody()->setGravityEnable(true);
            getPhysicsBody()->setCategoryBitmask(CT_GOAL);
            getPhysicsBody()->setCollisionBitmask(CT_NONE);
            getPhysicsBody()->setContactTestBitmask(CT_WHEEL);
            getPhysicsBody()->setDynamic(false);
            getPhysicsBody()->setRotationEnable(false);
            getPhysicsBody()->setTag(TG_GOAL);
            setGlobalZOrder(OBJ_LAYER_LV1-1);
            return true;
            break;
    }
    
   return true;
}

void Flg::update(float dt) {
  // todo
}

/** パラメータサンプル
*/

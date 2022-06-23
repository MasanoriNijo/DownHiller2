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
  return true;
}


void Flg::update(float dt) {
  // todo
}

/** パラメータサンプル
*/

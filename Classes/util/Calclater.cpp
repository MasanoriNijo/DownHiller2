#include "Calclater.h"

Calclater::Calclater(){}

Calclater::~Calclater(){}

Calclater* Calclater::create() {
    auto obj = new Calclater;
    if (obj && obj->init()) {
        obj->autorelease();
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Calclater::init() {
    // todo
    return true;
}

void Calclater::onEnterTransitionDidFinish() {
    // todo
}

void Calclater::update(float dt) {
    // todo
}

/** パラメータサンプル
 */

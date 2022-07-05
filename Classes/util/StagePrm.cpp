#include "StagePrm.h"

StagePrm::StagePrm():
_stageNumber(NULL), _comment(NULL), _timeLimit(NULL)
{}

StagePrm::~StagePrm() {

}

StagePrm* StagePrm::create() {
    auto obj = new StagePrm;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool StagePrm::init() {
  // todo
  return true;
}

void StagePrm::onEnterTransitionDidFinish() {
  // todo
}

void StagePrm::update(float dt) {
  // todo
}

/** パラメータサンプル
this->setStageNumber(int::create());
this->getStageNumber();
this->setCommnent(std::string::create());
this->getCommnent();
this->setTymeLimit(float::create());
this->getTymeLimit();
*/

#ifndef __STAGEPRM_H__
#define __STAGEPRM_H__

#include "cocos2d.h"
USING_NS_CC;

class StagePrm: public Ref {
protected:
  StagePrm();
  virtual ~StagePrm();

public:
  static StagePrm* create();
  bool init();
  CC_SYNTHESIZE(int,_stageNumber,StageNumber);
  CC_SYNTHESIZE(std::string,_comment,Commnent);
  CC_SYNTHESIZE(float,_timeLimit,TymeLimit);
  void update(float dt);
  void onEnterTransitionDidFinish();
};

#endif


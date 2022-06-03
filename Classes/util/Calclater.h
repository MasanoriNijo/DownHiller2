#ifndef __CALCLATER_H__
#define __CALCLATER_H__

#include "cocos2d.h"
USING_NS_CC;

class Calclater: public Ref {
protected:
  Calclater();
  virtual ~Calclater();

public:
  static Calclater* create();
  bool init();
  void update(float dt);
  void onEnterTransitionDidFinish();
};

#endif


#ifndef __FLG_H__
#define __FLG_H__

#include "item/base/Sprite2.h"
#include "cocos2d.h"
USING_NS_CC;

class Flg: public Sprite2 {
protected:
  Flg();
  virtual ~Flg();

public:
  static Flg* create();
  bool init() override;
  void update(float dt) override;
};

#endif

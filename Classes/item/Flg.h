#ifndef __FLG_H__
#define __FLG_H__

#include "item/base/Sprite2.h"
#include "cocos2d.h"
USING_NS_CC;

enum FlgType{
    START,
    GOAL
};

class Flg: public Sprite2 {
protected:
  Flg();
  virtual ~Flg();

public:
    static Flg* create();
    bool init() override;
    
    static Flg* create(FlgType ftype);
    bool init(FlgType ftype);
    void update(float dt) override;
};

#endif

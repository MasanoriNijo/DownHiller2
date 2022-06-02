#include "cocos2d.h"
USING_NS_CC;

class ColorChanger:Ref {
protected:
  ColorChanger();
  virtual ~ColorChanger();
  bool init();

public:
  CREATE_FUNC(ColorChanger);
  static Scene* createScene();
  CC_SYNTHESIZE_RETAIN(LayerColor*,_lc,LC);
  void update(float dt);
  void onEnterTransitionDidFinish();
};


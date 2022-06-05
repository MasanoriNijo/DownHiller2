#ifndef __TRANSITIONSCENE_H__
#define __TRANSITIONSCENE_H__

#include "ad/ImovileAd.h"
#include "util/Const.h"
#include "util/ColorChanger.h"
#include "util/Calclater.h"
#include "audio/include/AudioEngine.h"

#include "cocos2d.h"
USING_NS_CC;

//画面遷移時のメモリーリーク対策
class TransitionScene: public Scene {
protected:
  TransitionScene();
  virtual ~TransitionScene();
  bool init() override;

public:
  CREATE_FUNC(TransitionScene);
  static Scene* createScene();
  void update(float dt) override;
  void onEnterTransitionDidFinish() override;

    // 画面遷移
    void transitonScene(Scene* scene);
};

#endif

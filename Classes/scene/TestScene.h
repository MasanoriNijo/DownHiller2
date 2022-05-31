#ifndef __neomeiro__TestScene__
#define __neomeiro__TestScene__

#include "cocos2d.h"
USING_NS_CC;
class TestScene: public Layer {
protected:
	TestScene();
	virtual ~TestScene();
	bool init() override;

public:
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;
	static cocos2d::Scene* createScene();
    CREATE_FUNC(TestScene);
	void SetPrm();
	int index = 0;
	void SetPrm(int index_);
	void GetPrm(int index_);

	void update(float dt) override;
	void SetTouchListenner();
	void onEnterTransitionDidFinish() override;
    CC_SYNTHESIZE_RETAIN(Sprite*,_productTitle,ProductTitle);
};

#endif // __HELLOWORLD_SCENE_H__

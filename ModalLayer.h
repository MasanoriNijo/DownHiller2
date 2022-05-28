#ifndef __scalecatch__ModalLayer__
#define __scalecatch__ModalLayer__
#include "cocos2d.h"
USING_NS_CC;
class ModalLayer: public cocos2d::Layer {
protected:

private:

	//ModalLayer();
	virtual ~ModalLayer();
public:
	virtual bool init() override;
//void menuCloseCallBack(CCObject* pSender);
//virtual bool ccTouchBegan(cocos2d::Touch* pTouch,cocos2d::Event* pEvent) override;
	CREATE_FUNC(ModalLayer)
	;

};

#endif // __HELLOWORLD_SCENE_H__

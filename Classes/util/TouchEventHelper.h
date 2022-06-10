#ifndef __TOUCHEVENTHELPER_H__
#define __TOUCHEVENTHELPER_H__

#include "cocos2d.h"
USING_NS_CC;

class TouchEventHelper: public Ref {
protected:
  TouchEventHelper();
  virtual ~TouchEventHelper();

public:
  static TouchEventHelper* create();
  bool init();
  CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*,_touchListener,TouchListenner);
    
    void applyTouchListenner(Node* node);
    
    void removeTouchListenner();
    
};

#endif

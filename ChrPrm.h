#ifndef __piyopiyo__ChrPrm__
#define __piyopiyo__ChrPrm__

#include "cocos2d.h"
USING_NS_CC;
class ChrPrm: public cocos2d::Ref {
protected:
	ChrPrm();
	virtual ~ChrPrm();

	bool init();

private:

//

public:
//	CREATE_FUNC(ChrPrm);
	static const int NONE = 0x00000000;
	static const int PLAYER = 1 << 0;
	static const int ENEMY = 1 << 1;
	static const int COURCE = 1 << 2;
	static const int ITEM = 1 << 3;
	static const int PLAYERBOUND = 1 << 4;
	static const int PLAYERBODY = 1 << 5;
	static const int ALL = 0xFFFFFFFF;
	static ChrPrm * create();

};
#endif // __HELLOWORLD_SCENE_H__

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "cocos2d.h"
USING_NS_CC;

class Button: public Sprite {
protected:
    Button();
    virtual ~Button();
public:
    bool init(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback);
    static Button* create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_menuItemImage,MenuItemImage);
};

#endif

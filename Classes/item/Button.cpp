#include "Button.h"

Button::Button():_menuItemImage(NULL){}

Button::~Button() {
    CC_SAFE_RELEASE_NULL(_menuItemImage);
}

Button* Button::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback) {
    auto obj = new Button;
    if (obj && obj->init(normalImage, selectedImage, callback)) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Button::init(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback) {
    this->setMenuItemImage(MenuItemImage::create(normalImage,selectedImage,callback));
    
    return true;
}



/** パラメータサンプル
 this->setMenuItemImage(MenuItemImage::create());
 this->getMenuItemImage();
 this->setMenu(Menu::create());
 this->getMenu();
 */

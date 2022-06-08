#ifndef __CONST_H__
#define __CONST_H__

#include "cocos2d.h"
USING_NS_CC;

// 各変数を記入する

// debug用ログを表示する
#define DEBUG_LOG 1

// display statusを表示する
#define DISPLAY_STATUS 1

// NJLOGを表示する。
#define ENABLE_NJLOG 1

// debugLineを表示する
#define ENABLE_DEBUG_LINE 1

#if !defined(ENABLE_NJLOG) || ENABLE_NJLOG == 0
#define NJLOG(...)
#else
#define NJLOG(st)  cocos2d::log("njlog:%s", st)
#endif

// デフォルトのバックグラウンドカラーをセット 色相H:0-360,彩度S:0-100,明度V:0-100
#define DEFAULT_COLOR_H 230
#define DEFAULT_COLOR_S 100
#define DEFAULT_COLOR_V 100

// spriteの上下
#define OBJ_LAYER_BUTTOM 0
#define OBJ_LAYER_LV1 1
#define OBJ_LAYER_LV2 2
#define OBJ_LAYER_LV3 3
#define OBJ_LAYER_TOP 4

// 物理関連の定数
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

// 物理ラインを表示する
#define DEBUG_PHYSICS_MASK 1

// 物理世界の処理スピード
#define PHYSICS_WOELD_SPEED 6

// 数字の文字化
#define ST_INT(suzi) ({std::string st = StringUtils::toString((int)suzi);st;})

// 数字の文字化std::_Floating_to_string("%.3f", doubleNum)
#define ST_FLOAT(suzi) ({std::string st = StringUtils::format("%.3f", (float)suzi);st;})
// Vec2の文字化
#define ST_VEC2(vec2) ({std::string stx = ST_INT(vec2.x);std::string sty = ST_INT(vec2.y); "x:"+stx+" y:"+sty;})
// Nodeの文字化
#define ST_NODE(node) ({std::string stnd = ST_VEC2(node->getPosition());std::string stdeg = ST_FLOAT(node->getRotation()); stnd + " deg:" + stdeg;})

#endif

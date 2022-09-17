#ifndef __CONST_H__
#define __CONST_H__

#include "cocos2d.h"
USING_NS_CC;

// 各変数を記入する

// debug用ログを表示する
#define DEBUG_LOG 0

// display statusを表示する
#define DISPLAY_STATUS 1

// NJLOGを表示する。
#define ENABLE_NJLOG 1

// debugLineを表示する
#define ENABLE_DEBUG_LINE 0

#if !defined(ENABLE_NJLOG) || ENABLE_NJLOG == 0
#define NJLOG(...)
#else
#define NJLOG(st)  cocos2d::log("njlog:%s", st)
#endif

// デフォルトのバックグラウンドカラーをセット 色相H:0-360,彩度S:0-100,明度V:0-100
#define DEFAULT_COLOR_H 186
#define DEFAULT_COLOR_S 76
#define DEFAULT_COLOR_V 85

// デフォルトのグラデーションで変化後のバックグラウンドカラーをセット 色相H:0-360,彩度S:0-100,明度V:0-100
#define DEFAULT_GRADIATE_COLOR_H 184
#define DEFAULT_GRADIATE_COLOR_S 35
#define DEFAULT_GRADIATE_COLOR_V 80

// コース線の色
#define COURCE_LINE_COLOR_H 127
#define COURCE_LINE_COLOR_S 95
#define COURCE_LINE_COLOR_V 45

// コースベースの色
#define COURCE_BASE_COLOR_H 44
#define COURCE_BASE_COLOR_S 78
#define COURCE_BASE_COLOR_V 83

// コースベースの色
#define COURCE_BASE_COLOR2_H 44
#define COURCE_BASE_COLOR2_S 78
#define COURCE_BASE_COLOR2_V 83

// タイトル文字のカラー
#define TITLE_COLOR_H 340
#define TITLE_COLOR_S 100
#define TITLE_COLOR_V 100

// タイトル文字の縁取りカラー
#define TITLE_FUTI_COLOR_H 342
#define TITLE_FUTI_COLOR_S 5
#define TITLE_FUTI_COLOR_V 100

// コメント文字のカラー
#define COMMENT_COLOR_H 218
#define COMMENT_COLOR_S 77
#define COMMENT_COLOR_V 49

// spriteの上下
#define OBJ_LAYER_BUTTOM 0
#define OBJ_LAYER_LV1 2
#define OBJ_LAYER_LV2 4
#define OBJ_LAYER_LV3 6
#define OBJ_LAYER_TOP 8

// 物理関連の定数
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

// 物理ラインを表示する
#define DEBUG_PHYSICS_MASK 0

// 物理世界の処理スピード
#define PHYSICS_WOELD_SPEED 5

// タグ名コンタクト時に判別
static const int TG_RIDER=0;
static const int TG_F_WHEEL=1;
static const int TG_R_WHEEL=2;
static const int TG_COURCE=3;
static const int TG_START=4;
static const int TG_GOAL=5;

// Buttonの設定値
static const int BTN_FONT_SIZE = 24;

// Physics Category
static const int CT_NONE = 0x00000000;
static const int CT_RIDER = 1 << 0;
static const int CT_WHEEL = 1 << 1;
static const int CT_COURCE = 1 << 2;
static const int CT_GOAL = 1 << 3;
static const int CT_START = 1 << 4;
static const int CT_ALL = 0xFFFFFFFF;

// GameMode
static const int GAME_MODE_STAGE=0;
static const int GAME_MODE_TRAINING=1;
static const int GAME_MODE_DEMO=2;

// Stage数
static const int STAGE_SIZE=20;
static const int TRAINING_SIZE=63;


// GameSound
// Openingロゴ表示の音
static const char * SOUND_OPENING = "ME016-100125-logo01-wav.wav";

// ボタンを押す音
static const char * SOUND_BUTTON = "button05.mp3";

// Game中のBGM
static const char * SOUND_GAME_BGM = "BGM097-100811-shiaikaishida-mp3.mp3";

// Game開始音READY
static const char * SOUND_GAME_READY = "select01.mp3";

// Game開始音START
static const char * SOUND_GAME_START = "select02.mp3";

// Gameクリヤ音
static const char * SOUND_GAME_CLEAR = "ME010-090610-fanfare01-wav.wav";

// GameMiss音
static const char * SOUND_GAME_MISS = "ME023-100611-loss03-wav.wav";

// Playerのジャンプ音
static const char * SOUND_PLAYER_JUMP = "ashidejump.mp3";

// PlayerのMiss音
static const char * SOUND_PLAYER_MISS = "hit_noml.wav";


// macro
// 数字の文字化
#define ST_INT(suzi) ({std::string st = StringUtils::toString((int)suzi);st;})
// 数字の文字化std::_Floating_to_string("%.3f", doubleNum)
#define ST_FLOAT(suzi) ({std::string st = StringUtils::format("%.3f", (float)suzi);st;})
// 数字の文字化std::_Floating_to_string("%.3f", doubleNum)
#define ST_FLOAT2(suzi) ({std::string st = StringUtils::format("%.1f", (float)suzi);st;})
// Vec2の文字化
#define ST_VEC2(vec2) ({std::string stx = ST_FLOAT(vec2.x);std::string sty = ST_FLOAT(vec2.y); "x:"+stx+" y:"+sty;})
// Sizeの文字化
#define ST_SIZE(Size) ({std::string stx = ST_FLOAT(Size.width);std::string sty = ST_FLOAT(Size.height); "x:"+stx+" y:"+sty;})
// Nodeの文字化
#define ST_NODE(node) ({std::string stnd = ST_VEC2(node->getPosition());std::string stdeg = ST_FLOAT(node->getRotation()); stnd + " deg:" + stdeg;})

// UserDefault::getInstance();
static const char * UDF_INT_CLEAR_STAGE = "clear_stage";
static const char * UDF_INT_SELECTED_STAGE = "selected_stage";
static const char * UDF_BOOL_DEBUG_STAGE = "debug_stage";
static const char * UDF_INT_GAME_MODE = "game_mode";

#endif


// 各変数を記入する

// debug用ログを表示する
#define DEBUG_LOG 1

// display statusを表示する
#define DISPLAY_STATUS 1

// NJLOGを表示する。
#define ENABLE_NJLOG 1

#if !defined(ENABLE_NJLOG) || ENABLE_NJLOG == 0
#define NJLOG(...)
#else
#define NJLOG(format, ...)     cocos2d::log(format, ##__VA_ARGS__)
#endif


// デフォルトのバックグラウンドカラーをセット 色相H:0-360,彩度S:0-100,明度V:0-100
#define DEFAULT_COLOR_H 165
#define DEFAULT_COLOR_S 45
#define DEFAULT_COLOR_V 88

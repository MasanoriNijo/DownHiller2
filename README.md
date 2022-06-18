cocos2dx v4対応

ビルド方法
// todo:そのうちまとめる。

参照：https://zenn.dev/asteroid/articles/4c96ccfa09f12c418909
参照：https://qiita.com/noprops/items/cc022f326e8bc4f7cfe5

プロジェクトを作成する。
$ cocos new `Project名` -d ./ -l cpp -p `名前空間`

$ cocos new DownHiller -d jp.gr.java_conf.kotokotobokan.downhiller -l cpp -p /Users/jonym/Documents/cocos2dx
$ cocos new -l cpp -p jp.gr.java_conf.kotokotobokan.mygame -d ./mygame

$ cocos new HogeHoge -l cpp -p jp.gr.java_conf.kotokotobokan.hogehoge

$ cocos new DownHiller2 -l cpp -p jp.gr.java_conf.kotokotobokan.downhiller2

cd CocosTest/
mkdir ios-build
cd ios-build
cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos

Xcodeのプロジェクト設定
IOS deployment target:ios15.2
target device families:ipad

ビルドエラーの解消
1,[Xcode] iconv が Undefined symbols と叱られた時は ?
プロジェクトのBuild Phases に libiconv.tbd を追加します。
ライブラリは Link binary With Libraries から追加します。
https://atuweb.net/201708_xcode-iconv-undefined-symbols/

2,プロジェクトの Other Linker Flags に -lz を設定する。
https://nakamura001.hatenablog.com/entry/20120131/1328022869


3,画像ファイルの保存
1)エクスプローラーで
Resources/imagesフォルダ内に直接入れる。
2)Xcodeの右タブでAdd files to "Downhillor2"で、１の画像ファイルを指定
Resources/imagesフォルダ内に直接入れる。
3)XcodeのBuildPhases→Copy filesで２の画像ファイルを指定。
　代わりに、代わりに、Copy Bundle Resourcesから、２の画像を削除。
Resources/imagesフォルダ内に直接入れる。


4,imobile
SDKを入れる。
https://sppartner.i-mobile.co.jp/webdoc/index.html#swift/sdk-setup.html

cocos2dx用設定
https://sppartner.i-mobile.co.jp/webdoc/index.html#cocos2dx/module-information.html

corelocationframeworkを追加する。

5,memoryリーク対策
変数の呼び出しは、必ずget,setで呼ばないと、autoreleseが正常に機能せずに、
適切に消去されずに残り続けている。ので、get,setで呼び出す。

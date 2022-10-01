/****************************************************************************
Copyright (c) 2015-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.os.Build;
import android.os.Bundle;
import android.view.Gravity;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.FrameLayout;

import org.cocos2dx.lib.Cocos2dxActivity;

import jp.co.imobile.sdkads.android.ImobileSdkAd;

public class AppActivity extends Cocos2dxActivity {

    static final String IMOBILE_BANNER_PID = "34243";
    static final String IMOBILE_BANNER_MID = "461430";
    static final String IMOBILE_BANNER_SID = "1515544";
    static FrameLayout imobileBunnerLayout = null;

    static final String IMOBILE_FULLSCREENAD_PID = "34243";
    static final String IMOBILE_FULLSCREENAD_MID = "461430";
    static final String IMOBILE_FULLSCREENAD_SID = "1515545";
    static FrameLayout imobileFullScreenLayout = null;

    private static AppActivity me = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        me = this;
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW
        setImobileBanner();
//        setImobileFullScreen();
    }

    public static void setImobileBanner(){

        me.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // imobileの広告を入れる。
                // スポット情報を設定します
                ImobileSdkAd.registerSpotInline(me, IMOBILE_BANNER_PID, IMOBILE_BANNER_MID, IMOBILE_BANNER_SID);
                // 広告の取得を開始します
                ImobileSdkAd.start(IMOBILE_BANNER_SID);

                // 広告を表示するViewを作成します
                imobileBunnerLayout = new FrameLayout(me);
                FrameLayout.LayoutParams imobileAdLayoutParam = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
                // 広告の表示位置を指定
                imobileAdLayoutParam.gravity = (Gravity.BOTTOM | Gravity.CENTER);
                // 広告を表示します
                ImobileSdkAd.showAd(me, IMOBILE_BANNER_SID, imobileBunnerLayout);
                imobileBunnerLayout.bringToFront();
                mFrameLayout.addView(imobileBunnerLayout, imobileAdLayoutParam);
            }
        });
    }

    public static void removeImobileBanner(){
        me.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (imobileBunnerLayout != null) {
                    mFrameLayout.removeView(imobileBunnerLayout);
                    imobileBunnerLayout = null;
                }
            }
            });
    }

    public static void setImobileFullScreen(){
        me.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // imobileの広告を入れる。
                // スポット情報を設定します
                ImobileSdkAd.registerSpotFullScreen(getContext(), IMOBILE_FULLSCREENAD_PID, IMOBILE_FULLSCREENAD_MID, IMOBILE_FULLSCREENAD_SID);
                // 広告の取得を開始します
                ImobileSdkAd.start(IMOBILE_FULLSCREENAD_SID);

                // 広告を表示するViewを作成します
                imobileFullScreenLayout = new FrameLayout(getContext());
                FrameLayout.LayoutParams imobileAdLayoutParam = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
                // 広告の表示位置を指定
                imobileAdLayoutParam.gravity = Gravity.CENTER;
                // 広告を表示します
                ImobileSdkAd.showAd(getContext(), IMOBILE_FULLSCREENAD_SID);
                imobileFullScreenLayout.bringToFront();
                mFrameLayout.addView(imobileFullScreenLayout, imobileAdLayoutParam);
            }
        });
    }

    public static void removeImobileFullScreen(){
        me.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (imobileFullScreenLayout != null) {
                    imobileFullScreenLayout.removeView(imobileBunnerLayout);
                    imobileFullScreenLayout = null;
                }
            }
        });
    }

    @Override
    protected void onDestroy() {
        //Activity廃棄時の後処理
        ImobileSdkAd.activityDestroy();
        super.onDestroy();
    }
}

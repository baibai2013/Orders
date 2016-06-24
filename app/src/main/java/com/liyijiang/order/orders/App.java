package com.liyijiang.order.orders;

import android.app.Application;

import com.iflytek.cloud.SpeechConstant;
import com.iflytek.cloud.SpeechUtility;

/**
 * Created by lili on 16/6/24.
 */
public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        SpeechUtility.createUtility(this, SpeechConstant.APPID +"=576beb93");
    }




}

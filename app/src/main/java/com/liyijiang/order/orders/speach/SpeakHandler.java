package com.liyijiang.order.orders.speach;

/**
 * Created by lili on 16/6/24.
 */
public class SpeakHandler extends Thread{

    private  SpeachData speachData;

    public SpeakHandler(SpeachData speachData) {
        this.speachData = speachData;
    }

    @Override
    public void run() {
        while (Speach.getInstance().isrun()){







        }
    }
}

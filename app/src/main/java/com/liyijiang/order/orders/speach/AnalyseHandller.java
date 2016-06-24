package com.liyijiang.order.orders.speach;

/**
 * Created by lili on 16/6/24.
 */
public class AnalyseHandller extends Thread{

    private SpeachData speachData;
    public AnalyseHandller(SpeachData speachData) {
        this.speachData = speachData;
    }

    @Override
    public void run() {
        super.run();
    }
}

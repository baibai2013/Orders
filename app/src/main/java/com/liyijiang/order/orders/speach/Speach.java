package com.liyijiang.order.orders.speach;

/**
 * Created by lili on 16/6/24.
 */
public class Speach {

    private static Speach _instance;

    private boolean isrun = false;

    LisenHandler lisenHandler;
    SpeakHandler speakHandler;
    AnalyseHandller analyseHandller;
    SpeachData speachData;

    public static Speach getInstance(){
        if(_instance == null){
            _instance = new Speach();
        }

        return _instance;
    }

    private Speach(){

        speachData = new SpeachData();
        lisenHandler = new LisenHandler(speachData);
        speakHandler = new SpeakHandler(speachData);
        analyseHandller = new AnalyseHandller(speachData);

    }

    public void start(){
        isrun = true;
        lisenHandler.start();
        speakHandler.start();
        analyseHandller.start();
    }

    public void stop(){
        isrun = false;
    }


    public boolean isrun() {
        return isrun;
    }
}

package com.liyijiang.order.orders.speach;

import java.util.Queue;
import java.util.concurrent.SynchronousQueue;

/**
 * Created by lili on 16/6/24.
 */
public class SpeachData {

    private Queue<SentenceModel> lisenSentence = new SynchronousQueue<SentenceModel>(true);
    private Queue<SentenceModel> speakSentence = new SynchronousQueue<SentenceModel>(true);

    public SpeachData() {

    }

    public void addLisenSentence(SentenceModel sentenceModel){
        lisenSentence.add(sentenceModel);
    }

    public SentenceModel popLisenSentence(){
        return lisenSentence.poll();
    }

    public void addSpeakSentence(SentenceModel sentenceModel){
        speakSentence.add(sentenceModel);
    }

    public SentenceModel popSpeakSentence(){
        return speakSentence.poll();
    }


}

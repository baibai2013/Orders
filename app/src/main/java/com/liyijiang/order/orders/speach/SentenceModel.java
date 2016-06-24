package com.liyijiang.order.orders.speach;

/**
 * Created by lili on 16/6/24.
 */
public class SentenceModel {

    private String savepath;
    private UserModel user;
    private int prority;

    public SentenceModel(String savepath){
        this.savepath = savepath;
    }


    public int getPrority() {
        return prority;
    }

    public void setPrority(int prority) {
        this.prority = prority;
    }

    public UserModel getUser() {
        return user;
    }

    public void setUser(UserModel user) {
        this.user = user;
    }

    public String getSavepath() {
        return savepath;
    }

    public void setSavepath(String savepath) {
        this.savepath = savepath;
    }
}

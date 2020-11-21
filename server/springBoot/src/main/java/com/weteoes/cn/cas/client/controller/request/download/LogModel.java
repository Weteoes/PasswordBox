package com.weteoes.cn.cas.client.controller.request.download;

public class LogModel {
    String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public boolean hasData () {
        if (type == null) { return false; }
        return true;
    }
}

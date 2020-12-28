package com.weteoes.cn.cas.client.controller.json;

public class Download_LogModel {
    String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public boolean hasData () {
        if (type == null || type.isEmpty()) { return false; }
        return true;
    }
}

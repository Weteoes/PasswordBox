package com.weteoes.cn.cas.client.controller.json;

public class Config_Sumbit {
    String config;

    public String getConfig() {
        return config;
    }

    public void setConfig(String config) {
        this.config = config;
    }

    public boolean hasData () {
        if (config == null || config.isEmpty()) { return false; }
        return true;
    }
}

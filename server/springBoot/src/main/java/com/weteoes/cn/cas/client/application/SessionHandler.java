package com.weteoes.cn.cas.client.application;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.servlet.http.HttpSession;

@Component
public class SessionHandler {
    @Autowired
    public HttpSession httpSession_;

    public static HttpSession httpSession;

    @PostConstruct
    public void init(){
        httpSession = httpSession_;
    }
}

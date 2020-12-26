package com.weteoes.cn.cas.client.application;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.servlet.http.HttpServletRequest;

@Component
public class HttpServletRequestHandler {
    @Autowired
    public HttpServletRequest request_;

    public static HttpServletRequest request;

    @PostConstruct
    public void init() {
        request = request_;
    }
}

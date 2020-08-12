package com.weteoes.cn.cas.client.application;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.servlet.http.HttpServletRequest;

@Component
public class VariableClass {

    // 通过这个调用
    public static VariableClass that;

    @Autowired
    public HttpServletRequest request;

    @Autowired
    public JdbcTemplate jdbcTemplate;

    @Value("${server.servlet.session.cookie.name}")
    public String sessionName;

    @PostConstruct
    public void init(){
        that = this;
    }
}

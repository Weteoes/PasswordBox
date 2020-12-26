package com.weteoes.cn.cas.client.jdbc.application;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;


@Component
public class CommonVariableJDBC {
    @Autowired
    public JdbcTemplate jdbcTemplate_;

    public static JdbcTemplate jdbcTemplate;

    @PostConstruct
    public void init(){
        jdbcTemplate = jdbcTemplate_;
    }
}

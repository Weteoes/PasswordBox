package com.weteoes.cn.cas.client.application;

import com.weteoes.cn.cas.client.cas.configuration.EnableCasClient;
import com.weteoes.cn.cas.client.jdbc.controller.JdbcConfig;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.jdbc.core.JdbcTemplate;

@EnableCasClient
@SpringBootApplication
@ComponentScan({
        "com.weteoes.cn.cas.client.controller",
        "com.weteoes.cn.cas.client.cas.configuration",
        "com.weteoes.cn.cas.client.jdbc.controller"
})
public class ClientApplication {

    public static void main(String[] args) {
        SpringApplication.run(ClientApplication.class, args);
    }

}

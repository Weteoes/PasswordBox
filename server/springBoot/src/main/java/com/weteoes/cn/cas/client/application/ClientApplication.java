package com.weteoes.cn.cas.client.application;

import com.weteoes.cn.cas.client.cas.configuration.EnableCasClient;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.session.data.redis.config.annotation.web.http.EnableRedisHttpSession;

@EnableCasClient
@EnableRedisHttpSession(maxInactiveIntervalInSeconds=1800)
@SpringBootApplication
@ComponentScan({
        "com.weteoes.cn.cas.client.application",
        "com.weteoes.cn.cas.client.controller",
        "com.weteoes.cn.cas.client.cas.configuration",
        "com.weteoes.cn.cas.client.jdbc.controller"
})
public class ClientApplication {
    public static void main(String[] args) {
        SpringApplication.run(ClientApplication.class, args);
    }
}

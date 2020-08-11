package com.weteoes.cn.cas.client.controller;

import com.weteoes.cn.cas.client.jdbc.controller.JdbcConfig;
import com.weteoes.cn.cas.client.jdbc.controller.SessionOperating;
import org.jasig.cas.client.authentication.AttributePrincipal;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import com.google.gson.JsonObject;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Map;

@Controller
@RequestMapping("sso")
public class SSOController {
    @Autowired
    private JdbcTemplate jdbcTemplate;

    @Autowired
    private HttpServletRequest request;

    @Value("${cas-logout-url}")
    private String CAS_LOGOUT_URL;

    @ResponseBody
    @RequestMapping("login")
    String login() {
        JsonObject result = getUserInfo(request);
        int code = -1;
        if (result.size() != 0) {
            code = 0;
        }
        result.addProperty("code", code);
        return result.toString();
    }

    @RequestMapping("logout")
    String logout(@RequestParam String url, HttpSession session) {
        session.invalidate();
        return "redirect:" + CAS_LOGOUT_URL + url;
    }

    @RequestMapping("redirect")
    String redirect(@RequestParam String url) {
        AttributePrincipal principal = (AttributePrincipal)request.getUserPrincipal();
        if (principal == null) {
            return "sso/redirect";
        }
        // 登录成功，保存到数据库，永久保存
        JdbcConfig.initJDBC(jdbcTemplate);
        String uid = getUserInfo(request).get("uid").getAsString();
        if (!uid.isEmpty()) {
            SessionOperating.insert(request.getSession().getId(), uid);
        }
        return "redirect:" + url;
    }

    public static JsonObject getUserInfo(HttpServletRequest request) {
        JsonObject result = new JsonObject();
        AttributePrincipal principal = (AttributePrincipal)request.getUserPrincipal();
        if (principal != null) {
            Map attributes = principal.getAttributes();
            result.addProperty("id", (String)attributes.get("id"));
            result.addProperty("uid", (String)attributes.get("uid"));
            result.addProperty("user", (String)attributes.get("user"));
            return result;
        }
        return result;
    }

}

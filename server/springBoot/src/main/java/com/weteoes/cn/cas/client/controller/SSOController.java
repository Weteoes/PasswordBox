package com.weteoes.cn.cas.client.controller;

import com.weteoes.cn.cas.client.application.BasicClass;
import com.weteoes.cn.cas.client.application.HttpServletRequestHandler;
import com.weteoes.cn.cas.client.application.VariableClass;
import com.weteoes.cn.cas.client.jdbc.controller.SessionOperatingJDBC;
import org.jasig.cas.client.authentication.AttributePrincipal;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import com.google.gson.JsonObject;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpSession;
import java.util.Map;

@Controller
@RequestMapping("sso")
public class SSOController {

    @Value("${cas-logout-url}")
    private String CAS_LOGOUT_URL;

    @ResponseBody
    @RequestMapping("login")
    String login() {
        JsonObject result = getUserInfo();
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
        AttributePrincipal principal = (AttributePrincipal) HttpServletRequestHandler.request.getUserPrincipal();
        if (principal == null) {
            return "sso/redirect";
        }
        // 登录成功，保存到数据库，永久保存
        String uid = getUserInfo().get("uid").getAsString();
        if (!uid.isEmpty()) {
            String w = BasicClass.getCookie(VariableClass.that.sessionName);
            // 如果有session就保存一个
            if (!w.isEmpty()) {
                SessionOperatingJDBC.insert(w, uid);
            }
        }
        return "redirect:" + url;
    }

    public static JsonObject getUserInfo() {
        JsonObject result = new JsonObject();
        AttributePrincipal principal = (AttributePrincipal) HttpServletRequestHandler.request.getUserPrincipal();
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

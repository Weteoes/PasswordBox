package com.weteoes.cn.cas.client.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import java.net.HttpCookie;

@Controller
@RequestMapping("cs")
public class CsController {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    @Autowired
    private HttpServletRequest request;

    @RequestMapping("a")
    String a() {
        return "cs/a";
    }

    @ResponseBody
    @RequestMapping("b")
    String b() {
        String result = "";
        Cookie[] cookies = request.getCookies();
        if(cookies != null){
            for(Cookie cookie : cookies){
                result += cookie.getName() + ":" + cookie.getValue() + "<br/>";
            }
        }
        return result;
    }
//
//    @RequestMapping("byid")
//    public List<Login> byid (@RequestParam int id) {
//        return loginService.byid(id);
//    }
//
//    @RequestMapping("byid1")
//    // 无参数无法进入，除非defaultValue或者required = false
//    public String byid1 (@RequestParam(value = "id", defaultValue = "231") String id) {
//        return id;
//    }
//
//    @RequestMapping("byid2")
//    //这种在无参数也能进入
//    public String byid2 (String id) {
//        return id;
//    }
//
//    @RequestMapping("id/{id1}")
//    public String id_id (@PathVariable(value = "id1")Integer id) {
//        return "id_id" + id;
//    }
}

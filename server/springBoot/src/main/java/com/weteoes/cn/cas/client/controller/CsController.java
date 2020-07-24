package com.weteoes.cn.cas.client.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("cs")
public class CsController {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    @RequestMapping("a")
    String a() {
        return "cs/a";
    }

//    @RequestMapping("b")
//    String b(HttpSession session) {
//        return session.toString();
//    }
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

package com.weteoes.cn.cas.client.controller;

import com.weteoes.cn.cas.client.application.VariableClass;
import com.weteoes.cn.cas.client.jdbc.controller.SessionOperating;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpSession;

@Controller
@RequestMapping("cs")
public class CsController {

    @RequestMapping("a")
    String a() {
        return "cs/a";
    }

    @ResponseBody
    @RequestMapping("b")
    String b() {
        String result = "";
        result += "cookies:<br/>";
        Cookie[] cookies = VariableClass.that.request.getCookies();
        if (cookies != null) {
            for (Cookie i : cookies) {
                result += String.format("-%s:%s<br/>", i.getName(), i.getValue());
            }
        }
        HttpSession session = VariableClass.that.request.getSession();
        String id = session.getId();
        result += id + "<br/>";
        result += "session:<br/>";
        int maxInactiveInterval = session.getMaxInactiveInterval();
        result += "-maxInactiveInterval:" + maxInactiveInterval + "<br/>";
        long lastAccessedTime = session.getLastAccessedTime();
        result += "-lastAccessedTime:" + lastAccessedTime + "<br/>";
        long creationTime = session.getCreationTime();
        result += "-creationTime:" + creationTime + "<br/>";
        //SessionOperating.delete(session.getId());
        return result;
    }

//    @ResponseBody
//    @RequestMapping("b")
//    String b(HttpSession session) {
//        String result = "cookie:<br/>";
//        Cookie[] cookies = request.getCookies();
//        if(cookies != null){
//            for(Cookie cookie : cookies){
//                result += cookie.getName() + ":" + cookie.getValue() + "<br/>";
//            }
//        }
//
//        result += "session:<br/>";
//        int interval = session.getMaxInactiveInterval();
//        result += "interval:" + interval + "<br/>";
//
//        session.setAttribute("a","1");
//        session.setAttribute("a1","1");
//        Enumeration<String> sessionKeys = session.getAttributeNames();
//        while(sessionKeys.hasMoreElements()){
//            String key = sessionKeys.nextElement();
//            String value = (String)session.getAttribute(key);
//            result += String.format("  %s:%s<br/>", key, value);
//        }
//        return result;
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

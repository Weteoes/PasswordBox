package com.weteoes.cn.cas.client.application;

import javax.servlet.http.Cookie;

public class BasicClass {
    public static String getCookie(String name) {
        Cookie[] cookies = VariableClass.that.request.getCookies();
        if (cookies != null) {
            for (Cookie i : cookies) {
                String onlyName = i.getName();
                if (onlyName.equals(name)) return i.getValue();
            }
        }
        return "";
    }
}

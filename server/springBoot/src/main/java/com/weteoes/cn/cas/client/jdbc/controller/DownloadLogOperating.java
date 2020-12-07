package com.weteoes.cn.cas.client.jdbc.controller;

import com.weteoes.cn.cas.client.application.VariableClass;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DownloadLogOperating {
    public static boolean add (String type) {
        try {
            String sql = "insert into downloadlog(type, date) values(?, now())";
            int result = VariableClass.that.jdbcTemplate.update(sql, type);
            if (result > 0) return true;
            return false;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }


    public static List<Map<String, Object>> get () {
        List<Map<String, Object>> list = new ArrayList();
        try {
            String sql = "select type, count(*) as count, max(date) as date from downloadlog group by type";
            list = VariableClass.that.jdbcTemplate.queryForList(sql);
            return list;
        } catch (Exception e) {
            e.printStackTrace();
            return list;
        }
    }
}

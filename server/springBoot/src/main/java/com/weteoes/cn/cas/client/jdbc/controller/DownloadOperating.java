package com.weteoes.cn.cas.client.jdbc.controller;

import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.application.VariableClass;
import org.springframework.web.bind.annotation.RequestParam;

import java.sql.PreparedStatement;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DownloadOperating {
    public static List<Map<String, Object>> select (JsonObject args) {
        List<Map<String, Object>> list = new ArrayList();
        try {
            String sql = "select * from download " + JdbcConfig.getSQLString(args);
            list = VariableClass.that.jdbcTemplate.queryForList(sql);
            return list;
        } catch (Exception e) {
            e.printStackTrace();
            return list;
        }
    }
}

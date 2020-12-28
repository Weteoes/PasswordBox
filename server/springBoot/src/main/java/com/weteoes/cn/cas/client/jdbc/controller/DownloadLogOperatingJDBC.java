package com.weteoes.cn.cas.client.jdbc.controller;

import com.weteoes.cn.cas.client.jdbc.application.CommonJDBC;

import java.sql.PreparedStatement;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DownloadLogOperatingJDBC {
    public static boolean add (String type) {
        try {
            boolean hasType = false; // 数据库是否拥有相同的type
            List<Map<String, Object>> get = DownloadLogOperatingJDBC.get();
            for (Map<String, Object> a : get) {
                if (a.get("type").toString().equals(type)) {
                    // 数据库拥有相同的type
                    hasType = true;
                }
            }
            if (hasType) {
                // 数据库拥有相同的type
                CommonJDBC.getJdbcTemplate().update(connection -> {
                    String sql = "update downloadlog set count = count + 1, date = now() where type = ? ";
                    PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
                    ps.setString(1, type);
                    return ps;
                });
                return true;
            } else {
                // 数据库没有相同的type
                String sql = "insert into downloadlog(type, count, date) values(?, 1,  now())";
                int result = CommonJDBC.getJdbcTemplate().update(sql, type);
                if (result > 0) return true;
            }
            return false;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }


    public static List<Map<String, Object>> get () {
        List<Map<String, Object>> list = new ArrayList();
        try {
            String sql = "select * from downloadlog";
            list = CommonJDBC.getJdbcTemplate().queryForList(sql);
            return list;
        } catch (Exception e) {
            e.printStackTrace();
            return list;
        }
    }
}

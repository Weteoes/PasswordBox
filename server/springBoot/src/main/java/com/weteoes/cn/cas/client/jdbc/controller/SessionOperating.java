package com.weteoes.cn.cas.client.jdbc.controller;

import com.weteoes.cn.cas.client.jdbc.tables.Session;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class SessionOperating {

    public static String getUid (String w) {
        List<Map<String, Object>> list = new ArrayList();
        try {
            String sql = String.format("select * from session where session = '%s'", w);
            list = JdbcConfig.jdbcTemplate.queryForList(sql);
            if (list.size() > 0) {
                String uid = list.get(0).get("uid").toString();
                return uid;
            }
            return "";
        } catch (Exception e) {
            e.printStackTrace();
            return "";
        }
    }

    public static Session insert (String w, String uid) {
        try {
            Session a = new Session();
            a.setSession(w);
            a.setUid(uid);
            JdbcConfig.jdbcTemplate.update(connection -> {
                String sql = "insert into session(session, uid, createTime) values(?, ?, ?)";
                PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
                ps.setString(1, a.getSession());
                ps.setString(2, a.getUid());
                ps.setTimestamp(3, new Timestamp(System.currentTimeMillis()));
                return ps;
            });
            return a;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static boolean delete (String w) {
        String sql = "delete from session where session=?";
        int a = JdbcConfig.jdbcTemplate.update(sql, w);
        if (a > 0) return true;
        return false;
    }
}

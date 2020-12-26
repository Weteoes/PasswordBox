package com.weteoes.cn.cas.client.jdbc.controller;

import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.jdbc.application.CommonJDBC;
import com.weteoes.cn.cas.client.jdbc.tables.Config;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ConfigOperatingJDBC {

    public static List<Map<String, Object>> select (JsonObject args) {
        List<Map<String, Object>> list = new ArrayList();
        try {
            String sql = "select * from config " + CommonJDBC.getSQLString(args);
            list = CommonJDBC.getJdbcTemplate().queryForList(sql);
            return list;
        } catch (Exception e) {
            e.printStackTrace();
            return list;
        }
    }

    public static Config update (String uid, String config) {
        try {
            Config a = new Config();
            a.setUid(uid);
            a.setConfig(config);
            CommonJDBC.getJdbcTemplate().update(connection -> {
                String sql = "UPDATE config SET config=? WHERE uid = ?";
                PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
                ps.setString(1, config);
                ps.setString(2, uid);
                return ps;
            });
            return a;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Config insert (String uid, String config) {
        try {
            Config a = new Config();
            a.setUid(uid);
            a.setConfig(config);
            CommonJDBC.getJdbcTemplate().update(connection -> {
                String sql = "insert into config(uid, config) values(?, ?)";
                PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
                ps.setString(1, a.getUid());
                ps.setString(2, a.getConfig());
                return ps;
            });
            return a;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}

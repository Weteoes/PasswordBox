package com.weteoes.cn.cas.client.jdbc.controller;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.Map;

public class JdbcConfig {
    @Autowired
    public static JdbcTemplate jdbcTemplate;

    // 参数（where a = '1' and b ='2'）
    public static String getSQLString(JsonObject args) {
        String result = " ";
        int nowArgsSize = 0; // 当前加入字符串中有几个参数
        for (Map.Entry<String, JsonElement> entry : args.entrySet()) {
            String key = entry.getKey();
            JsonElement value = entry.getValue();
            String valueS = value.getAsString();

            if (key != "" && valueS != "") {
                if (nowArgsSize == 0) { result += "where "; }
                else { result += "and "; }
                result += String.format("%s = \"%s\" ", key, valueS);
                nowArgsSize++;
            }
        }
        return result;
    }
}
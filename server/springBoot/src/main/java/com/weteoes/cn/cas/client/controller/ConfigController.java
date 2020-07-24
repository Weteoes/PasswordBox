package com.weteoes.cn.cas.client.controller;

import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.jdbc.controller.JdbcConfig;
import com.weteoes.cn.cas.client.jdbc.tables.Config;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;
import com.weteoes.cn.cas.client.jdbc.controller.ConfigOperating;
import com.weteoes.cn.cas.client.controller.SSOController;

import javax.servlet.http.HttpServletRequest;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("config")
public class ConfigController {

    @Autowired
    private JdbcTemplate jdbcTemplate;
    @Autowired
    private HttpServletRequest request;

    private void initJDBC() {
        if (jdbcTemplate != null) JdbcConfig.jdbcTemplate = jdbcTemplate;
    }

    @ResponseBody
    @RequestMapping("sumbit")
    String sumbit (MultipartFile file) {
        initJDBC();
        JsonObject result = new JsonObject();
        int code = -1;
        String msg = "unknown error";
        if (file == null || file.isEmpty()) {
            code = -1;
            msg = "未选择需上传的文件";
        } else {
            // 有数据的时候
            JsonObject userInfo = SSOController.getUserInfo(request);
            if (userInfo.size() == 0) {
                code = -1;
                msg = "未登录";
            } else {
                try {
                    JsonObject selectJson = new JsonObject();
                    String uid = userInfo.get("uid").getAsString();
                    selectJson.addProperty("uid", uid);
                    // 获取文件内容
                    byte[] fileBytes = file.getBytes();
                    String fileString = new String(fileBytes);
                    // 判断是否有数据
                    if (ConfigOperating.select(selectJson).size() == 0) {
                        // 数据库没数据
                        Config a = ConfigOperating.insert(uid, fileString);
                        if (a == null) {
                            // 插入失败
                            code = -1;
                            msg = "数据库插入失败";
                        } else {
                            // 插入成功
                            code = 0;
                            msg = "success";
                        }
                    } else {
                        //　数据库有数据
                        ConfigOperating.update(uid, fileString);
                        code = 0;
                        msg = "success";
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    code = -1;
                    msg = "error";
                }
            }
        }
        result.addProperty("code", code);
        result.addProperty("msg", msg);
        return result.toString();
    }

    @ResponseBody
    @RequestMapping("get")
    String get () {
        initJDBC();
        JsonObject result = new JsonObject();
        int code = -1;
        String msg = "unknown error";
        // 有数据的时候
        JsonObject userInfo = SSOController.getUserInfo(request);
        if (userInfo.size() == 0) {
            code = -1;
            msg = "未登录";
        } else {
            JsonObject selectJson = new JsonObject();
            String uid = userInfo.get("uid").getAsString();
            selectJson.addProperty("uid", uid);
            List<Map<String, Object>> list = ConfigOperating.select(selectJson);
            // 判断是否有数据
            if (list.size() == 0) {
                // 数据库没数据
                code = -1;
                msg = "config error";
            } else {
                // 数据库有数据
                Map<String, Object> only = list.get(0);
                String onlyConfig = only.get("config").toString();
                result.addProperty("config", onlyConfig);
                code = 0;
                msg = "success";
            }
        }
        result.addProperty("code", code);
        result.addProperty("msg", msg);
        return result.toString();
    }
}

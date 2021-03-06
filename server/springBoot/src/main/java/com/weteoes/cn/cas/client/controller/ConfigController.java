package com.weteoes.cn.cas.client.controller;

import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.application.BasicClass;
import com.weteoes.cn.cas.client.application.VariableClass;
import com.weteoes.cn.cas.client.controller.json.Config_Sumbit;
import com.weteoes.cn.cas.client.jdbc.controller.SessionOperatingJDBC;
import com.weteoes.cn.cas.client.jdbc.tables.Config;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;
import com.weteoes.cn.cas.client.jdbc.controller.ConfigOperatingJDBC;

import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("config")
public class ConfigController {

    @ResponseBody
    @RequestMapping("sumbit")
    String sumbit (MultipartFile file) {
        JsonObject result = new JsonObject();
        int code = -1;
        String msg = "unknown error";
        if (file == null || file.isEmpty()) {
            code = -1;
            msg = "未选择需上传的文件";
        } else {
            String uid = getLoginUid();
            if (uid.isEmpty()) {
                code = 100;
                msg = "未登录";
            } else {
                try {
                    JsonObject selectJson = new JsonObject();
                    selectJson.addProperty("uid", uid);
                    // 获取文件内容
                    byte[] fileBytes = file.getBytes();
                    String fileString = new String(fileBytes);
                    // 判断是否有数据
                    if (ConfigOperatingJDBC.select(selectJson).size() == 0) {
                        // 数据库没数据
                        Config a = ConfigOperatingJDBC.insert(uid, fileString);
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
                        ConfigOperatingJDBC.update(uid, fileString);
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
    @RequestMapping("set")
    String set (@RequestBody Config_Sumbit config_Sumbit) {
        JsonObject result = new JsonObject();
        int code = -1;
        String msg = "unknown error";
        if (!config_Sumbit.hasData()) {
            code = 1;
            msg = "数据不正确";
        } else {
            String uid = getLoginUid();
            if (uid.isEmpty()) {
                code = 100;
                msg = "未登录";
            } else {
                try {
                    JsonObject selectJson = new JsonObject();
                    selectJson.addProperty("uid", uid);
                    // 获取文件内容
                    String fileString = config_Sumbit.getConfig();
                    // 判断是否有数据
                    if (ConfigOperatingJDBC.select(selectJson).size() == 0) {
                        // 数据库没数据
                        Config a = ConfigOperatingJDBC.insert(uid, fileString);
                        if (a == null) {
                            // 插入失败
                            code = 3;
                            msg = "数据库插入失败";
                        } else {
                            // 插入成功
                            code = 0;
                            msg = "success";
                        }
                    } else {
                        //　数据库有数据
                        ConfigOperatingJDBC.update(uid, fileString);
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
        JsonObject result = new JsonObject();
        int code = -1;
        String msg = "unknown error";
        String uid = getLoginUid();
        if (uid.isEmpty()) {
            code = 100;
            msg = "未登录";
        } else {
            JsonObject selectJson = new JsonObject();
            selectJson.addProperty("uid", uid);
            List<Map<String, Object>> list = ConfigOperatingJDBC.select(selectJson);
            // 判断是否有数据
            if (list.size() == 0) {
                // 数据库没数据
                code = 10;
                msg = "config empty";
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

    @ResponseBody
    @RequestMapping("login")
    String login() {
        JsonObject result = new JsonObject();
        int code = -1;
        String uid = getLoginUid();
        if (!uid.isEmpty()) {
            code = 0;
        }
        result.addProperty("code", code);
        return result.toString();
    }

    // 获取登录用户UID
    private String getLoginUid() {
        // 方式一
        JsonObject jsonObject = SSOController.getUserInfo();
        if (jsonObject.size() > 0) {
            return jsonObject.get("uid").getAsString();
        }

        // 方式二
        String w = BasicClass.getCookie(VariableClass.that.sessionName);
        if (!w.isEmpty()) {
            String uid = SessionOperatingJDBC.getUid(w);
            if (!uid.isEmpty()) { return uid; }
        }
        return "";
    }
}

package com.weteoes.cn.cas.client.controller;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.jdbc.controller.DownloadOperating;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("download")
@CrossOrigin
public class DownloadConteoller {
    @ResponseBody
    @RequestMapping("get")
    String get() {
        JsonObject result = new JsonObject();
        int code = -1;
        try {
            JsonObject jsonObject = new JsonObject();
            List<Map<String, Object>> resultList = DownloadOperating.select(jsonObject);
            if (resultList.size() > 0) {
                JsonArray downloadList = new JsonArray();
                for (Map<String, Object> only: resultList) {
                    JsonObject downloadOnly = new JsonObject();
                    downloadOnly.addProperty("key", only.get("key").toString());
                    downloadOnly.addProperty("url", only.get("url").toString());
                    downloadList.add(downloadOnly);
                }
                code = 0;
                result.add("data", downloadList);
            }
        } catch (Exception e) {
            code = -2;
            e.printStackTrace();
        }
        result.addProperty("code", code);
        return result.toString();
    }
}

package com.weteoes.cn.cas.client.controller;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.weteoes.cn.cas.client.controller.request.download.LogModel;
import com.weteoes.cn.cas.client.jdbc.controller.*;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("download")
@CrossOrigin
public class DownloadConteoller {
    @ResponseBody
    @RequestMapping(value = "get", method = RequestMethod.POST)
    String get() {
        JsonObject result = new JsonObject();
        int code = -1;
        try {
            JsonObject jsonObject = new JsonObject();
            List<Map<String, Object>> resultList = DownloadOperatingJDBC.select(jsonObject);
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

    @ResponseBody
    @RequestMapping(value = "log", method = RequestMethod.POST)
    String log(@RequestBody LogModel logModel) {
        JsonObject result = new JsonObject();
        int code = -1;
        try {
            if (logModel.hasData()) {
                boolean jdbcResult = DownloadLogOperatingJDBC.add(logModel.getType());
                if (jdbcResult) {
                    code = 0;
                }
            } else {
                code = -3;
            }
        } catch (Exception e) {
            code = -2;
            e.printStackTrace();
        }
        result.addProperty("code", code);
        return result.toString();
    }

    @ResponseBody
    @RequestMapping(value = "count")
    String admin() {
        JsonObject result = new JsonObject();
        int code = -1;
        try {
            JsonObject jsonObject = new JsonObject();
            List<Map<String, Object>> resultList = DownloadLogOperatingJDBC.get();
            if (resultList.size() > 0) {
                JsonArray downloadList = new JsonArray();
                for (Map<String, Object> only: resultList) {
                    JsonObject downloadOnly = new JsonObject();
                    downloadOnly.addProperty("type", only.get("type").toString());
                    downloadOnly.addProperty("count", only.get("count").toString());
                    downloadOnly.addProperty("date", only.get("date").toString());
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

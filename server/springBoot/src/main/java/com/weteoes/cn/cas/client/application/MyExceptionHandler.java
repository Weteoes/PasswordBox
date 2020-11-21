package com.weteoes.cn.cas.client.application;

import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@ControllerAdvice
public class MyExceptionHandler {

    public static final String ERROR_VIEW = "error/404";

    @ExceptionHandler(value = Exception.class)//指定拦截的异常
    public Object errorHandler(HttpServletRequest request, HttpServletResponse response, Exception e) throws Exception{
        e.printStackTrace();//打印异常信息
        ModelAndView mv = new ModelAndView();
        mv.addObject("exception",e);
        mv.addObject("url",request.getRequestURL());//发生异常的路径
        mv.setViewName(ERROR_VIEW);//指定发生异常之后跳转页面
        return mv;
    }
}
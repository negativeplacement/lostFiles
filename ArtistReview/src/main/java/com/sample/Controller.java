package com.sample;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.fasterxml.jackson.databind.ObjectMapper;

import dbUtils.DbConn;
import dbUtils.Json;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;
import model.webUser.StringData;
import view.WebUserView;

@RestController
public class Controller {

    @RequestMapping("/hello")
    public String helloController() {
        return "<h1>Hello World</h1>";
    }

    @RequestMapping(value="/jsonClass", produces="application/json")
    public String jsonClassController () {
        StringData sd = new StringData();
        sd.userEmail = "sallyk@temple.edu";
        sd.userPassword = "pass1234";
        ObjectMapper mapper = new ObjectMapper();
        try {
            return mapper.writer().writeValueAsString(sd);
        } catch (Exception e) {
            return "Cannot convert object to JSON";
        }
    }

    @RequestMapping(value = "/webUser/logIn", params = {"isEmail", "isPassword"}, produces = "application/json")
    public String logIn (HttpServletRequest request, @RequestParam("isEmail") String isEmail, @RequestParam("isPassword") String isPassword){
        HttpSession session = request.getSession();
        StringData sd = new StringData();
        DbConn dbc = new DbConn();
        //sd.errorMsg = (dbc == null) ? dbc.getErr() : "";
        StringData checkUser = WebUserView.isUser(dbc, isEmail, isPassword);
        try{
            if(checkUser.errorMsg != "Web User Not Found."){
                sd = checkUser;
                session.setAttribute("loggedOnUser", sd);
            } else{
                sd.errorMsg += "Credentials Not Found";
                session.invalidate();
            }
        }catch(Exception e){
            System.out.println("webUser/logIn controller error: " + e.getMessage());
            sd.errorMsg += ". " + e.getMessage();
        }
        dbc.close(); 
        return Json.toJson(sd);
    }

    @RequestMapping(value = "/webUser/getProfile", produces = "application/json")
    public String getProfile(HttpServletRequest request){
        HttpSession session = request.getSession();
        StringData sd = new StringData();
        try{
            if(session.getAttribute("loggedOnUser") != null){
                sd = (StringData)session.getAttribute("loggedOnUser");
            }else{
                sd.errorMsg = "No Current User Logged In";
            }
        } catch(Exception e){
            System.out.println("webUser/getProfile controller error: " + e.getMessage());
            sd.errorMsg += ". " + e.getMessage();
        }
        return Json.toJson(sd);
    }

    @RequestMapping(value = "/webUser/logOff", produces = "application/json")
    public String logOff (HttpServletRequest request){
        HttpSession session = request.getSession();
        StringData sd = new StringData();
        try{
            session.invalidate();
            sd.errorMsg = "Session has been invalidated";
        } catch(Exception e){
            System.out.println("webUser/logOff controller error: " + e.getMessage());
            sd.errorMsg += ". " + e.getMessage();
        }
        return Json.toJson(sd);
    }

}
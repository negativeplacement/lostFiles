package com.sample;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import com.fasterxml.jackson.databind.ObjectMapper;
import model.artistReview.*;
import dbUtils.*;
import view.artistReviewView;

@RestController
public class artistReviewController {
    @RequestMapping(value = "/artistReview/getAll", produces = "application/json")
    public String allUsers() {
        StringDataList list = new StringDataList();
        DbConn dbc = new DbConn();
        list = artistReviewView.getAllUsers(dbc);
        dbc.close(); 
        return Json.toJson(list); 
    }

    @RequestMapping(value = "/artistReview/getRoles", produces = "application/json")
    public String allRoles() {
        StringDataList list = new StringDataList(); // dbError empty, list empty
        DbConn dbc = new DbConn();
        list = artistReviewView.getAllRoles(dbc);
        dbc.close();
        return Json.toJson(list);
    }

    @RequestMapping(value = "/artistReview/insert", params = { "jsonData" }, produces = "application/json")
    public String insert(@RequestParam("jsonData") String jsonInsertData){
        StringData errorMsgs = new StringData();
        if ((jsonInsertData == null) || jsonInsertData.length() == 0) {
            errorMsgs.errorMsg = "Cannot insert. No user data was provided in JSON format";
        } else {
            System.out.println("user data for insert (JSON): " + jsonInsertData);
            try {
                ObjectMapper mapper = new ObjectMapper();
                StringData insertData = mapper.readValue(jsonInsertData, StringData.class);
                System.out.println("user data for insert (java obj): " + insertData.toString());

                DbConn dbc = new DbConn();
                errorMsgs.errorMsg = dbc.getErr();
                if (errorMsgs.errorMsg.length() == 0) { // db connection OK
                    errorMsgs = DbMods.insert(insertData, dbc);
                }
                dbc.close();
            } catch (Exception e) {
                String msg = "Could not convert jsonData to model.webUser.StringData obj: "+
                jsonInsertData+ " - or other error in controller for 'user/insert': " + e.getMessage();
                System.out.println(msg);
                errorMsgs.errorMsg += ". " + msg;
            }
        }
        return Json.toJson(errorMsgs);
    }

    @RequestMapping(value = "/artistReview/getById", params = {"userId"}, produces = "application/json")
    public String getById(@RequestParam("userId") String userId) {
        StringData sd = new StringData();
        if (userId == null) {
            sd.errorMsg = "Error: URL must be artistReview/getById/xx where xx is the artist_review_id of the desired artist_review record.";
        } else {
            DbConn dbc = new DbConn();
            sd.errorMsg = dbc.getErr();
            if (sd.errorMsg.length() == 0) {
                System.out.println("*** Ready to call DbMods.getById");
                sd = DbMods.getById(dbc, userId);
            }
            dbc.close();
        }
        return Json.toJson(sd);
    }
    
    @RequestMapping(value = "/artistReview/update", params = { "jsonData" }, produces = "application/json")
    public String update(@RequestParam("jsonData") String jsonInsertData) {
        StringData errorData = new StringData();
        if ((jsonInsertData == null) || jsonInsertData.length() == 0) {
            errorData.errorMsg = "Cannot update. No user data was provided in JSON format";
        } else {
            System.out.println("user data for update (JSON): " + jsonInsertData);
            try {
                ObjectMapper mapper = new ObjectMapper();
                StringData updateData = mapper.readValue(jsonInsertData, StringData.class);
                System.out.println("user data for update (java obj): " + updateData.toString());
                DbConn dbc = new DbConn();
                errorData = DbMods.update(updateData, dbc);
                dbc.close();
            } catch (Exception e) {
                String msg = "Unexpected error in controller for 'artistReview/insert'... " + e.getMessage();
                System.out.println(msg);
                errorData.errorMsg = msg;
            }
        }
        return Json.toJson(errorData);
    }

    @RequestMapping(value = "/artistReview/delete", params = {"deleteUserId" }, produces = "application/json")
    public String deleteUser(@RequestParam("deleteUserId") String deleteUserId){
        StringData sd = new StringData();
        if(deleteUserId == null){
            sd.errorMsg = "Error: URL must be artistReview/getById?userId=xx, where " +
            "xx is the artist_review_id of the artist_review record to be deleted.";
        } else{
            DbConn dbc = new DbConn();
            sd = DbMods.delete(dbc, deleteUserId);
            dbc.close();
        }
        return Json.toJson(sd);
    }
}
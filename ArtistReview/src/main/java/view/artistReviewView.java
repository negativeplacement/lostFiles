package view;
import model.artistReview.*;
import dbUtils.*;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class artistReviewView {
    public static StringDataList getAllUsers(DbConn dbc) {
        StringDataList sdl = new StringDataList(); 
        sdl.dbError = dbc.getErr(); 
        if (sdl.dbError.length() > 0) {
            return sdl; 
        }
        
        StringData sd = new StringData();
        try {
            String sql = 
            "SELECT artist_review_id, artist_name, artist_image_url, record_id, catalog_no, record_review, web_user.user_email, web_user.web_user_id " +
            "FROM artist_review, web_user "+
            "WHERE artist_review.web_user_id = web_user.web_user_id "+
            "ORDER BY artist_review_id";
            
            PreparedStatement stmt = dbc.getConn().prepareStatement(sql);
            ResultSet results = stmt.executeQuery();

            while (results.next()) {
                sd = new StringData();
                sd.artistReviewId = Format.fmtInteger(results.getObject("artist_review_id"));
                sd.artistName = Format.fmtString(results.getObject("artist_name"));
                sd.artistImage = Format.fmtString(results.getObject("artist_image_url"));
                sd.recordId = Format.fmtInteger(results.getObject("record_id"));
                sd.catalogNo = Format.fmtInteger(results.getObject("catalog_no"));
                sd.recordReview = Format.fmtString(results.getObject("record_review"));
                sd.webUserEmail = Format.fmtString(results.getObject("user_email"));
                sd.webUserId = Format.fmtInteger(results.getObject("web_user_id"));
                sdl.add(sd);
            }
            results.close();
            stmt.close();
        } catch (Exception e) {
            sd.errorMsg = "Exception thrown in artistReviewView.getAllUsers(): " + e.getMessage();
            sdl.add(sd);
        }
        return sdl;
    }

    public static StringDataList getAllRoles(DbConn dbc){

        // sdl will have two properties, a DbError (initially set to "") and an empty array. 
        StringDataList sdl = new StringDataList();

        sdl.dbError = dbc.getErr(); // returns "" if connection is good, else db error msg.
        if (sdl.dbError.length() > 0) {
            return sdl; // cannot proceed, db error (and that's been recorded in return object).
        }
        try{
            String sql = "SELECT DISTINCT web_user.web_user_id, user_email  "
                    + "FROM web_user, artist_review ORDER BY web_user_id";  // you always want to order by something, not just random order.
            PreparedStatement stmt = dbc.getConn().prepareStatement(sql);
            ResultSet results = stmt.executeQuery();
            while(results.next()){
                RoleStringData role = new RoleStringData();
                role.webUserId = Format.fmtInteger(results.getObject("web_user_id"));
                role.userEmail = Format.fmtString(results.getObject("user_email"));
                sdl.add(role);
            }
            results.close();
            stmt.close();
        } catch (Exception e) {
            StringData sd = new StringData();
            sd.errorMsg = "Exception thrown in artistReviewView.allRoles(): " + e.getMessage();
            sdl.add(sd);
        }
        return sdl;
    }
}

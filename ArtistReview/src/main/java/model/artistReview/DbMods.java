package model.artistReview;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import dbUtils.*;

public class DbMods {
    /*
     * Returns a "StringData" object that is full of field level validation
     * error messages (or "" for any field that passes validation).
     */
    private static StringData validate(StringData inputData) {

        StringData errorMsgs = new StringData();
        // Validation
        errorMsgs.artistReviewId = Validate.integerMsg(inputData.artistReviewId, false);
        errorMsgs.artistName = Validate.stringMsg(inputData.artistName, 45, true);

        errorMsgs.artistImage = Validate.stringMsg(inputData.artistImage, 300, false);

        errorMsgs.recordId = Validate.integerMsg(inputData.recordId, false);
        errorMsgs.catalogNo = Validate.integerMsg(inputData.catalogNo, false);
        errorMsgs.webUserId = Validate.integerMsg(inputData.webUserId, true);

        return errorMsgs;
    } // validate

    public static StringData insert(StringData inputData, DbConn dbc) {

        StringData errorMsgs = new StringData();
        errorMsgs = validate(inputData);
        if (errorMsgs.characterCount() > 0) { // at least one field has an error, don't go any further.
            errorMsgs.errorMsg = "Please try again";
            return errorMsgs;

        } else { // all fields passed validation

            // Start preparing SQL statement
            String sql = "INSERT INTO artist_review (artist_review_id, artist_name, artist_image_url, record_id, catalog_no, web_user_id) " +
                    "values (?,?,?,?,?,?)";

            // PrepStatement is Sally's wrapper class for java.sql.PreparedStatement
            // Only difference is that Sally's class takes care of encoding null
            // when necessary. And it also System.out.prints exception error messages.
            PrepStatement pStatement = new PrepStatement(dbc, sql);

            // Encode string values into the prepared statement (wrapper class).
            pStatement.setInt(1, Validate.convertInteger(inputData.artistReviewId));
            pStatement.setString(2, inputData.artistName);
            pStatement.setString(3, inputData.artistImage);
            pStatement.setInt(4, Validate.convertInteger(inputData.recordId));
            pStatement.setInt(5, Validate.convertInteger(inputData.catalogNo));
            pStatement.setInt(6, Validate.convertInteger(inputData.webUserId));

            // here the SQL statement is actually executed
            int numRows = pStatement.executeUpdate();

            // This will return empty string if all went well, else all error messages.
            errorMsgs.errorMsg = pStatement.getErrorMsg();
            if (errorMsgs.errorMsg.length() == 0) {
                if (numRows == 1) {
                    errorMsgs.errorMsg = ""; // This means SUCCESS. Let the user interface decide how to tell this to
                                             // the user.
                } else {
                    // probably never get here unless you forgot your WHERE clause and did a bulk
                    // sql update.
                    errorMsgs.errorMsg = numRows + " records were inserted when exactly 1 was expected.";
                }
            } else if (errorMsgs.errorMsg.contains("foreign key")) {
                errorMsgs.errorMsg = "Invalid Web User Id - " + errorMsgs.errorMsg;
            } else if (errorMsgs.errorMsg.contains("Duplicate entry")) {
                errorMsgs.errorMsg = "That artistName is already taken - " + errorMsgs.errorMsg;
            }

        } // customerId is not null and not empty string.
        return errorMsgs;
    } // insert

    public static StringData update(StringData updateData, DbConn dbc) {
        StringData errorMsgs = new StringData();
        errorMsgs = validate(updateData);
        // For update, we also need to check that webUserId has been supplied by the user...
        errorMsgs.webUserId = Validate.integerMsg(updateData.webUserId, true);
        if (errorMsgs.characterCount() > 0) { // at least one field has an error, don't go any further.
            errorMsgs.errorMsg = "Please try again";
            return errorMsgs;

        } else { // all fields passed validation

            /* Useful to know the exact field names in the database... 
             * "SELECT artist_review_id, artist_name, artist_image_url, record_id, web_user.web_user_id " +
             * "FROM artist_review, web_user "+
             * "WHERE artist_review.web_user_id = web_user.web_user_id "+
             * "ORDER BY artist_review_id";
             */

            String sql = "UPDATE artist_review SET artist_name = ?, artist_image_url = ?, record_id = ?, catalog_no = ?, "+
                    "web_user_id = ? WHERE artist_review_id = ?";

            // PrepStatement is Sally's wrapper class for java.sql.PreparedStatement
            // Only difference is that Sally's class takes care of encoding null
            // when necessary. And it also System.out.prints exception error messages.
            PrepStatement pStatement = new PrepStatement(dbc, sql);

            // Encode string values into the prepared statement (wrapper class).
            pStatement.setString(1, updateData.artistName); // string type is simple
            pStatement.setString(2, updateData.artistImage);
            pStatement.setInt(3, Validate.convertInteger(updateData.recordId));
            pStatement.setInt(4, Validate.convertInteger(updateData.catalogNo));
            pStatement.setInt(5, Validate.convertInteger(updateData.webUserId));
            pStatement.setInt(6, Validate.convertInteger(updateData.artistReviewId));
            

            // here the SQL statement is actually executed
            int numRows = pStatement.executeUpdate();

            // This will return empty string if all went well, else all error messages.
            errorMsgs.errorMsg = pStatement.getErrorMsg();
            if (errorMsgs.errorMsg.length() == 0) {
                if (numRows == 1) {
                    errorMsgs.errorMsg = ""; // This means SUCCESS. Let the user interface decide how to tell this to
                                             // the user.
                } else {
                    // probably never get here unless you forgot your WHERE clause and did a bulk
                    // sql update OR the web User id (supplied by the client side) does not exist.
                    errorMsgs.errorMsg = numRows + " records were inserted when exactly 1 was expected.";
                }
            } else if (errorMsgs.errorMsg.contains("foreign key")) {
                errorMsgs.errorMsg = "Invalid User Web User Id - " + errorMsgs.errorMsg;
            } else if (errorMsgs.errorMsg.contains("Duplicate entry")) {
                errorMsgs.errorMsg = "That artist name is already taken - " + errorMsgs.errorMsg;
            }

        } // customerId is not null and not empty string.
        return errorMsgs;
    } // update

    public static StringData getById(DbConn dbc, String id) {
        StringData sd = new StringData();
        // This case already tested in the controller, but ("belt and suspenders")
        // we are double checking here as well.
        if (id == null) {
            sd.errorMsg = "Cannot getById (user): id is null";
            return sd;
        }

        Integer intId;
        try {
            intId = Integer.valueOf(id);
        } catch (Exception e) {
            sd.errorMsg = "Cannot getById (user): URL parameter 'id' can't be converted to an Integer.";
            return sd;
        }
        try {
            String sql = "SELECT artist_review_id, artist_name, artist_image_url, record_id, catalog_no, artist_review.web_user_id " +
            "FROM artist_review, web_user "+
            "WHERE artist_review.web_user_id = web_user.web_user_id AND artist_review_id = ?";
            PreparedStatement stmt = dbc.getConn().prepareStatement(sql);

            // Encode the id (that the user typed in) into the select statement, into the
            // the first (and only) ?
            stmt.setInt(1, intId);

            ResultSet results = stmt.executeQuery();
            if (results.next()) { // id is unique, one or zero records expected in result set

                // plainInteger returns integer converted to string with no commas.
                sd.artistReviewId = Format.fmtInteger(results.getObject("artist_review_id"));
                sd.artistName = Format.fmtString(results.getObject("artist_name"));
                sd.artistImage = Format.fmtString(results.getObject("artist_image_url"));
                sd.recordId = Format.fmtInteger(results.getObject("record_id"));
                sd.catalogNo = Format.fmtInteger(results.getObject("catalog_no"));
                sd.webUserId = Format.fmtInteger(results.getObject("web_user_id"));

            } else {
                sd.errorMsg = "Artist Review Not Found.";
            }
            results.close();
            stmt.close();
        } catch (Exception e) {
            sd.errorMsg = "Exception thrown in model.artistReview.DbMods.getById(): " + e.getMessage();
        }
        return sd;
    } // getById

    public static StringData delete(DbConn dbc, String userId){
        StringData sd = new StringData();
        if (userId == null){
            sd.errorMsg = "modelartistReview.DbMods.delete: " +
            "cannot delete artist_review record because 'artist_review_id' is null";
            return sd;
        }
        sd.errorMsg = dbc.getErr();
        if(sd.errorMsg.length() > 0) { // cannot proceed, db error
            return sd;
        }
        try{
            String sql = "DELETE FROM artist_review WHERE artist_review_id = ?";
            // Compile the SQL (checking for syntax errors against the connected DB).
            PreparedStatement pStatement = dbc.getConn().prepareStatement(sql);
            // Encode user data into the prepared statement.
            pStatement.setString(1, userId);
            int numRowsDeleted = pStatement.executeUpdate();
            if(numRowsDeleted == 0){
                sd.errorMsg = "Record not deleted - there was no record with artist_review_id " + userId;
            }else if (numRowsDeleted > 1){
                sd.errorMsg = "Programmer Error: > 1 record deleted. Did you forget the WHERE clause?";
            }
        }catch (Exception e){
            sd.errorMsg = "Exception thrown in model.artistReview.DbMods.delete(): " + e.getMessage();
        }
        return sd;
    }

}

package model.artistReview;
public class RoleStringData {
    public String webUserId = ""; // Primary Key
    public String userEmail = "";

    public String errorMsg = "";

    public RoleStringData() {
    }

    public String toString() {
        return "userRoleId: " + this.webUserId
                + ", userRoleType: " + this.userEmail;
    }
}
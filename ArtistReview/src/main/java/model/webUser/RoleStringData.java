package model.webUser;
public class RoleStringData {
    public String userRoleId = ""; // Primary Key
    public String userRoleType = "";

    public String errorMsg = "";

    public RoleStringData() {
    }

    public String toString() {
        return "userRoleId: " + this.userRoleId
                + ", userRoleType: " + this.userRoleType;
    }
}

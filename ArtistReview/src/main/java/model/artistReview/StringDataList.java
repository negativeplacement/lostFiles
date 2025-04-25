package model.artistReview;
import java.util.ArrayList; 

public class StringDataList {

    public String dbError = "";
    public ArrayList <StringData> artistReviewList = new ArrayList <StringData>();
    public ArrayList <RoleStringData> roleList = new ArrayList <RoleStringData>();
    // Default constructor leaves StringDataList objects nicely set with properties 
    // indicating no database error and 0 elements in the list.
    public StringDataList() {
    }

    // Adds one StringData element to the array list of StringData elements
    public void add(StringData stringData) {
        this.artistReviewList.add(stringData);
    }

    public void add(RoleStringData stringData) {
        this.roleList.add(stringData);
    }
}

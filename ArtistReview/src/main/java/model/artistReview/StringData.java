package model.artistReview;

public class StringData {
    public String artistReviewId = "";     // auto-increment primary key
    public String artistName = "";     // varChar 45, must be unique
    public String artistImage = "";
    public String recordId = "";
    public String catalogNo = "";
    public String recordReview = "";
    public String webUserEmail = "";
    public String webUserId = "";  //foreign key (integer), required by DB 
    public String errorMsg = "";
    
    public StringData(){
    }
    
    public int characterCount() {
        String s = this.artistReviewId + this.artistName + this.artistImage + this.recordId + this.catalogNo + this.recordReview + this.webUserEmail + this.webUserId;
        return s.length();
    }

    public String toString() {
        return "Artist Review Id: " + this.artistReviewId + ", Artist Name: " + this.artistName + "Artist Image: "+ this.artistImage +
        "Record ID: " + this.recordId + ", Catalog No: " + this.catalogNo + ", Web User Email: " + this.webUserEmail + ", Record Review: " + this.recordReview + ", Web User ID: " + this.webUserId;
    }
}
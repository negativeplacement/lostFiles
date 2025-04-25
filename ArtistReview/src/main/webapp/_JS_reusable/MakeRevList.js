"use strict";
function MakeRevList({revList=[{}], title=""}){
    function MakeRev({ artistName = "blank", artistImage = "./imgRef/Default.jpg", catalogNo = null, userRating = null}) {
        var isReview = document.createElement("div");
        isReview.classList.add("rev"); 
        var isUserRating = userRating;
        var isCatalogNo = catalogNo;
        
        isReview.setCatalogNo = function (getCatalogNo) {
            var findCatalog = Number(getCatalogNo);
            if(isNaN(findCatalog)){
                console.log(getCatalogNo + " is not a valid input");
            }
            isCatalogNo = findCatalog;
            display();
        };
        
        isReview.setRating = function(getRating){
            var verifyRating = Number(getRating);
            if(isNaN(verifyRating)){
                console.log(getRating + " is not a valid input");
            } else if(verifyRating < 0 || verifyRating > 10){
                console.log(getRating + " is not a valid input");
                return;
            }
            isUserRating = verifyRating;
            display();
        };
        
        isReview.innerHTML = 
        `<div class='reviewInfo'></div>
        <button class='catalogButton'>Set Catalog No: </button>
        <input class='catalogInput'/> <br/>
        <button class='ratingButton'>Set Rating (1-10): </button>
        <input class='ratingInput'/>`;
        
        var reviewInfo = isReview.getElementsByClassName("reviewInfo")[0];
        var catalogButton = isReview.getElementsByClassName("catalogButton")[0];
        var catalogInput = isReview.getElementsByClassName("catalogInput")[0];
        var ratingButton = isReview.getElementsByClassName("ratingButton")[0];
        var ratingInput = isReview.getElementsByClassName("ratingInput")[0];
        
        var display = function(){
            reviewInfo.innerHTML = 
            `<img src='${artistImage}'/>
            <p> Artist: ${artistName} <br/> Catalog No: ${isCatalogNo} <br/> Rating: ${isUserRating} </p>`;
        };
        display();
        
        catalogButton.onclick = function(){
            isReview.setCatalogNo(catalogInput.value);
        };
        
        ratingButton.onclick = function(){
            isReview.setRating(ratingInput.value);
        };
        
        return isReview;
    }

    var isReviewList = document.createElement("div");
    isReviewList.classList.add("revList");
    isReviewList.innerHTML = `<h2>${title}</h2>`;
    if(revList.length == undefined && typeof(revList) == "object"){
        isReviewList.appendChild(MakeRev(revList));
    } else{
        for(var revObj of revList){
            isReviewList.appendChild(MakeRev(revObj));
        }
    }
    return isReviewList;
}
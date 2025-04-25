function MakeRevList_CGF() {
    var ele = document.createElement("div");
    var firstRevList = [{artistName:"MF DOOM", artistImage:"./imgRef/MF_DOOM.jpg", catalogNo:2, userRating:9.5}, {}];
    var newReview1 = MakeRevList({revList: firstRevList, title: "Test 1"});
    ele.appendChild(newReview1);
    var secondRevList = [{}];
    var newReview2 = MakeRevList({revList: secondRevList, title: "Test 2"});
    ele.appendChild(newReview2);
    var thirdRevList = {};
    var newReview3 = MakeRevList({revList: thirdRevList, title: "Test 3"});
    ele.appendChild(newReview3);
    return ele;
}
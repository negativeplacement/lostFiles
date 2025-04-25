function MakeRevListR_CGF(){
    var firstRevList = [{artistName:"MF DOOM", artistImage:"./imgRef/MF_DOOM.jpg", catalogNo:2,  userRating:9.5}, {}];
    var secondRevList = [{}];
    var thirdRevList = {};
    return (
        <div>
            <MakeRevListR revList={firstRevList} title="Test1"/>
            <MakeRevListR revList={secondRevList} title="Test2"/>
            <MakeRevListR revList={thirdRevList} title="Test3"/>
        </div>
    )
}
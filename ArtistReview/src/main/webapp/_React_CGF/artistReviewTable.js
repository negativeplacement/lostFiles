"use strict";

const artistReviewTable=(url)=>{

    console.log("artistReviewTable running");
    //const [items, setItems] = React.useState([]);
    const [error, setError] = React.useState(null);
    const [isLoading, setIsLoading] = React.useState(true);
    const [dbList, setDbList] = React.useState([]);
    const [deleteUser, setDeleteUser] = React.useState(false);
    const [getUserId, setGetUserId] = React.useState();
    const [filterInput, setFilterInput] = React.useState("");
    const [filteredList, setFilteredList] = React.useState([]);
    var getIndex;

    React.useEffect(()=>{
        ajax_alt( url, 
            function (dbList) {   // success function gets obj from ajax_alt
                if (dbList.dbError.length > 0) {
                    setError(dbList.dbError);
                } else {
                    console.log("in artistReviewTable, here is web review list (on the next line):");
                    console.log(dbList.artistReviewList);
                    //setItems(dbList.artistReviewList);
                    setDbList(dbList.artistReviewList);
                    setFilteredList(dbList.artistReviewList);
                }
                setIsLoading(false); // set isLoading last to prevent premature rendering. 
            },

            // failure function (also anonymous)
            function (msg) {       // failure function gets error message from ajax_alt
                setError(msg);
                setIsLoading(false); // set isLoading last to prevent premature rendering.
            }
        );
    },[]);

    React.useEffect(()=>{
        if(deleteUser){
            ajax_alt( "artistReview/delete?deleteUserId="+getUserId, 
            function() {   // success function gets obj from ajax_alt
                console.log("Record " + getUserId + " successfully deleted. ");
                setDeleteUser(false);
                setGetUserId();
            },
            // failure function (also anonymous)
            function (msg) {       // failure function gets error message from ajax_alt
                setError(msg);
                setIsLoading(false); // set isLoading last to prevent premature rendering.
            }
        );}
    },[deleteUser]);

    const doFilter=(filterInputVal)=>{
        let newList = filterObjList (dbList, filterInputVal);
        console.log("function doFilter. filterInputVal is: " + filterInputVal +". See filtered list on next line:");
        console.log(newList);
        setFilteredList(newList);
    };

    const clearFilter=()=>{
        setFilterInput("");
        doFilter("");
    }

    function sortByProp(propName, sortType){
        // sort the user list based on property name and type
        jsSort(dbList, propName, sortType);
        console.log("Sorted list is below");
        console.log(dbList);

        // For state variables that are objects or arrays, you have to do 
        // something like this or else React does not think that the state 
        // variable (dbList) has changed. Therefore, React will not re-render 
        // the component.
        let listCopy = JSON.parse(JSON.stringify(dbList)); 
        setDbList(listCopy);
    }

    if (isLoading) {
        console.log("Is Loading...");
        return <div> Loading... </div>
    }

    if (error) {
        console.log("Error...");
        return <div>Error: {error} </div>;
    }

    function getInsert(){
        window.location.hash = "#/reviewInsert"
    }

    function deleteUserDb(userObj, indx) {
        console.log("To delete user " + userObj.artistReviewId + "?");
        if (confirm("Do you really want to delete " + userObj.artistReviewId + "? ")){
            setDbList(deleteListEle(dbList, indx));
            alert("You have to call the delete web api here and only "+
            "delete the element from the UI if the delete web api was "+
            "succesfull (ajax success function AND there's no error message) "+
            "passed back from the ajax call");
        }
    }

    function callback(){
        setDeleteUser(true);
        setDbList(deleteListEle(dbList, getIndex));
        modalFw.alert("Record successfully deleted. ");
    }

    function deleteUserDbModal(userObj, indx){
        console.log("To delete user " + userObj.artistReviewId + "?");
        setGetUserId(userObj.artistReviewId);
        getIndex = indx;
        modalFw.confirm("Do you really want to delete artistReviewId:" + userObj.artistReviewId + "? ", callback);
    }

    function deleteListEle(theList, indx){
        let newList = [];
        for(var i = 0; i < theList.length; i++){
            if(i !== indx){
                newList.push(theList[i]);
            }
        }
        console.log("here is list after deleting element " + indx);
        console.log(newList);
        return newList;
    }

    console.log("items for ArtistReviewTable on next line");
    //console.log(items);
    return (
        <div className="clickSort">
            <h3>
                Artist Review List &nbsp;
                <input value={filterInput} onChange={(e) => setFilterInput(e.target.value)} /> &nbsp;
                <button onClick={() => doFilter(filterInput)}>Search</button> &nbsp;
                <button onClick={clearFilter}>Clear</button>&nbsp;
                <img src="./icons/insert.png" onClick={getInsert}/>
            </h3>
            <table>
                <thead>
                    <tr>
                        <th></th>
                        <th onClick={() => sortByProp("artistName", "text")} className="textAlignLeft">Artist Name</th>
                        <th className="textAlignCenter">Artist Image</th>
                        <th onClick={() => sortByProp("recordId", "number")} className="textAlignLeft">Record ID</th>
                        <th onClick={() => sortByProp("catalogNo", "number")} className="textAlignLeft">Catalog No</th>
                        <th onClick={() => sortByProp("webUserEmail", "text")} className="textAlignLeft">Web User Email</th>
                        <th onClick={() => sortByProp("webUserId", "number")} className="textAlignRight">Web User ID</th>
                    </tr>
                </thead>
                <tbody>
                    {
                        dbList.map((item, index) =>
                            <tr key={item.artistReviewId} >
                                <td>
                                <td><a href={'#/reviewUpdate/:'+item.artistReviewId}><img src="icons/update.png" className="clickLink"/></a></td><br/>
                                <td className="textAlignCenter" onClick={() => deleteUserDbModal(item, index)}><img src="icons/delete.png" /></td>
                                </td>
                                <td className="textAlignLeft">{item.artistName}({item.artistReviewId})</td>
                                <td className="simple"><img src={item.artistImage} /></td>
                                <td className="textAlignLeft">{item.recordId}</td>
                                <td className="textAlignLeft">{item.catalogNo}</td>
                                <td className="textAlignLeft">{item.webUserEmail}</td>
                                <td className="textAlignRight">{item.webUserId}</td>
                            </tr>
                        )
                    }
                </tbody>
            </table>
        </div>
    );

};
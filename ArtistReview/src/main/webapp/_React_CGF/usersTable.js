"use strict";
const usersTable = (url) => {

    console.log("usersTable running");
    //const [items, setItems] = React.useState([]);
    const [error, setError] = React.useState(null);
    const [isLoading, setIsLoading] = React.useState(true);
    const [dbList, setDbList] = React.useState([]);
    const [filterInput, setFilterInput] = React.useState("");
    const [filteredList, setFilteredList] = React.useState([]);
    const [deleteUser, setDeleteUser] = React.useState(false);
    const [getUserId, setGetUserId] = React.useState();
    var getIndex;

    React.useEffect(() => {
        ajax_alt(
            url,
            // success function (anonymous)
            function (dbList) {   // success function gets obj from ajax_alt
                if (dbList.dbError.length > 0) {
                    setError(dbList.dbError);
                } else {
                    console.log("in usersTable, here is web user list (on the next line):");
                    console.log(dbList.webUserList);
                    //setItems(dbList.webUserList);
                    setDbList(dbList.webUserList);
                    setFilteredList(dbList.webUserList);
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
            ajax_alt( "webUser/delete?deleteUserId="+getUserId, 
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
        let newList = filterObjList(dbList, filterInputVal);
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

    if(isLoading){
        console.log("Is Loading...");
        return <div> Loading... </div>
    }

    if (error) {
        console.log("Error...");
        return <div>Error: {error} </div>;
    }
    
    function getInsert(){
        window.location.hash = "#/userInsert"
    }

    function deleteUserDb(userObj, indx) {
        console.log("To delete user " + userObj.userEmail + "?");
        if (confirm("Do you really want to delete " + userObj.userEmail + "? ")){
            setFilteredList(deleteListEle(filteredList, indx));
            alert("You have to call the delete web api here and only "+
            "delete the element from the UI if the delete web api was "+
            "succesfull (ajax success function AND there's no error message) "+
            "passed back from the ajax call");
        }
    }

    function callback(){
        console.log("Ok Clicked");
        setDeleteUser(true);
        setFilteredList(deleteListEle(filteredList, getIndex));
        modalFw.alert("Record successfully deleted. ");
    }

    function deleteUserDbModal(userObj, indx){
        console.log("To delete user " + userObj.webUserId + "?");
        setGetUserId(userObj.webUserId);
        getIndex = indx;
        modalFw.confirm("Do you really want to webUserId:" + userObj.webUserId + "? ", callback);
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

    console.log("items for UserTable on next line");
    //console.log(items);
    return (
        <div className="clickSort">
            <h3>
                Web User List&nbsp;
                <input value={filterInput} onChange={(e) => setFilterInput(e.target.value)} /> &nbsp;
                <button onClick={() => doFilter(filterInput)}>Search</button> &nbsp;
                <button onClick={clearFilter}>Clear</button>&nbsp;
                <img src="./icons/insert.png" onClick={getInsert}/>
            </h3>
            <table>
                <thead>
                    <tr>
                        <th></th>
                        <th onClick={() => sortByProp("userEmail","text")}>Email</th>
                        <th className="textAlignCenter">Image</th>
                        <th onClick={() => sortByProp("birthday","date")} className="textAlignCenter">Birthday</th>
                        <th onClick={() => sortByProp("membershipFee","number")} className="textAlignRight">Membership Fee</th>
                        <th onClick={() => sortByProp("userRoleId","number")}>Role</th>
                        <th>Error</th>
                    </tr>
                </thead>
                <tbody>
                    {
                        filteredList.map((item, index) =>
                            <tr key={item.webUserId}>
                                <td>
                                <td><a href={'#/userUpdate/:'+item.webUserId}><img src="icons/update.png" className="clickLink"/></a></td><br/>
                                <td className="textAlignCenter" onClick={() => deleteUserDbModal(item, index)}><img src="icons/delete.png" /></td>
                                </td>
                                <td>{item.userEmail}({item.webUserId})</td>
                                <td className="shadowImage textAlignCenter"><img src={item.userImage} /></td>
                                <td className="textAlignCenter">{item.birthday}</td>
                                <td className="textAlignRight">{item.membershipFee}</td>
                                <td className="nowrap">{item.userRoleId} {item.userRoleType}</td>
                                <td>{item.errorMsg}</td>
                            </tr>
                        )
                    }
                </tbody>
            </table>
        </div>
    );

}; // function usersTable 
"use strict"; // not sure if this is needed in react...

const ReviewInsert = (props) => {

    // See if this is an Insert or an Updat by checking the path that invoked this component.
    // If the path has a : in it, then its update, else its insert.
    // If update, extract (from the path) the id of the webUser record that is to be updated. 
    // console.log("props for userInsertOrUpdate on next line");
    // console.log(props);

    var action = "insert"; // exact spelling has to match web API @RequestMapping
    var id = "";
    var url = props.location.pathname;
    console.log("url that invoked UserInsert is " + url);
    if (url.search(":") > -1) {
        const url_list = url.split(":");
        id = url_list[url_list.length - 1];
        console.log("to update id " + id);
        action = "update";
    } else {
        console.log("to insert");
    }

    // Set initial values of state variables and receive (from React) a setter function for each one.
    // In React, you create State Variables for anything that (if changed) needs to re-render the UI. 

    // Object (State Variable) that holds all the user entered data. Each object 
    // is linked with a textbox for user input. 
    const [userData, setUserData] = React.useState(
        {
            "artistReviewId": "",
            "artistName": "",
            "artistImage": "",
            "recordId": "",
            "catalogNo": "",
            "webUserId": "",
            "errorMsg": ""
        }
    );

    // State variable to hold the Role List (gotten from getRolesAPI.jsp) 
    // Role List populates the <select tag> for the UI.
    const [roleList, setRoleList] = React.useState([]);

    // Object (State Variable) that holds all the error messages - field level 
    // and form/record level (errorMsg).
    const [errorObj, setErrorObj] = React.useState(
        {
            "artistReviewId": "",
            "artistName": "",
            "artistImage": "",
            "recordId": "",
            "catalogNo": "",
            "webUserId": "",
            "errorMsg": ""
        }
    );

    // This state variable helps control when insertUserAPI should be run
    // (whenever the user clicks submit but NOT initially).
    const [submitCount, setSubmitCount] = React.useState(0);

    // By having this boolean state variable, we avoid rendering the component 
    // before we are ready to do so. 
    const [isLoading, setIsLoading] = React.useState(true);

    const encodeUserInput = () => {
        var userInputObj = {
            "artistReviewId": userData.artistReviewId,
            "artistName": userData.artistName,
            "artistImage": userData.artistImage,
            "recordId": userData.recordId,
            "catalogNo": userData.catalogNo,
            "webUserId": userData.webUserId
        };
        console.log("userInputObj on next line");
        console.log(userInputObj);
        // turn the user input object into JSON then run that through 
        // a URI encoder (needed for security on server side, prevents 
        // server from hacks). 
        //return encodeURIComponent(JSON.stringify(userInputObj));
        return encodeURI(JSON.stringify(userInputObj));
    };

    // If you just change the value of a State object's property, then React does not 
    // know that the object has been changed (and thus does re-render the UI). 
    // To get around this, I wrote function setProp that clones the object, changes 
    // the desired property, then returns the clone. THEN React knows that the object 
    // has been changed (and re-renders the UI). 
    const setProp = (obj, propName, propValue) => {
        var o = Object.assign({}, obj); // makes a copy of the object
        o[propName] = propValue; // changes the property of the copy
        // console.log("setProp orig object is");
        // console.log(obj);
        // console.log("after changing " + propName + " to " + propValue + " the new obj is");
        // console.log(o);
        return o; // returns the object copy with the property's value changed.
    };

    // useEffect second parameter is an array of "watch elements" that 
    // (if they change) should trigger the function specified 
    // as the first useEffect parameter.

    // This code should execute just once at initial page render because 
    // the array of watch elements (second parameter to useEffect) is empty.
    React.useEffect(

        () => {

            console.log("AJAX call for role list");
            ajax_alt("artistReview/getRoles",

                function (obj) { // obj holds role list from AJAX call
                    console.log("artistReview/getRoles Ajax success");
                    if (obj.dbError.length > 0) {  // db error trying to read role list
                        setErrorObj(setProp(errorObj, "webUserId", obj.dbError));
                    } else {
                        setRoleList(obj.roleList);
                        // role fields (from role/getAll): userRoleId, userRoleType. 
                        // sort alphabetically by role type (not by id)
                        obj.roleList.sort(function (a, b) {
                            if (a.userEmail > b.userEmail) {
                                return 1
                            } else {
                                return -1;
                            }
                            return 0;
                        });
                        console.log('sorted role list on next line');
                        console.log(obj.roleList);
                        //setRoleList(obj.roleList);

                        // UserData.userRoleId gets set whenever the user clicks on the role pick list, 
                        // but we need to set that field (to the id of the top role showing in the pick list) 
                        // so that if the user doesn't click the role pick list and then clicks save, things 
                        // will work. 
                        //setUserData(setProp(userData, "webUserId", obj.roleList[0].webUserId)); // FIX
                        console.log("set initial role id for web_user to be "+obj.roleList[0].webUserId);

                        if (action === "update") { //this is update, not insert, get webUser by the id
                            console.log("Now getting webUser record " + id + " for the update");
                            ajax_alt("/artistReview/getById?userId=" + id,
                                function (obj) {
                                    if (obj.errorMsg.length > 0) { // obj.errorMsg holds error, e.g., db error
                                        console.log("DB error trying to get the webUser record for udpate");
                                        setErrorObj(setProp(errorObj, "errorMsg", obj.errorMsg));
                                        //setProp = (obj, propName, propValue)

                                    } else { // obj holds the webUser record of the given id
                                        console.log("got the web user record for update (on next line)");
                                        console.log(obj);
                                        setUserData(obj); // prepopulate user data since this is update.
                                    }
                                },
                                function (ajaxErrorMsg) { // AJAX Error Msg from trying to read the webUser to be updated.
                                    setErrorObj(setProp(errorObj, "errorMsg", ajaxErrorMsg));
                                }
                            );
                        }

                    }
                },
                function (ajaxErrorMsg) { // AJAX Error Msg from trying to read the role list.
                    // setRoleError(msg);
                    setErrorObj(setProp(errorObj, "errorMsg", ajaxErrorMsg));
                }
            );
            setIsLoading(false);
        }, []);


    // This code should execute every time the submit BUTTON is clicked, 
    // but NOT on initial rendering (it checks submitCount). 
    React.useEffect(() => {

        console.log("Here is the user data that will be sent to the insert/update API");
        console.log(userData);

        console.log("SubmitCount has changed, value is " + submitCount);
        if (submitCount > 0) { // dont make the AJAX call on initial render

            // action was set to insert or update above (must match web API @RequestMapping). 
            ajax_alt("artistReview/" + action + "?jsonData=" + encodeUserInput(),

                function (obj) { // obj holds field level error messages
                    console.log("These are the error messages (next line)");
                    console.log(obj);

                    if (obj.errorMsg.length === 0) {
                        // errorMsg = "" means no error, record was inserted (or updated). 
                        obj.errorMsg = "Record Saved !";
                    }

                    setErrorObj(obj); // show the field level error messages (will all be "" if record was inserted)

                },
                function (ajaxErrorMsg) { // AJAX error msg trying to call the insert or update API
                    setErrorObj(setProp(errorObj, "errorMsg", ajaxErrorMsg));
                }
            );
        }
    }, [submitCount]);

    const validate = () => {
        // In this function, we just change the value of state variable submitCount 
        // so that the React.useEffect (that's watching for changes in submitCount)
        // will run, making the AJAX call.  
        console.log("Validate, should kick off AJAX call");
        setSubmitCount(submitCount + 1);
    };

    if (isLoading) {
        return <div> ... Loading ... </div>;
    }

    return (
        <table className="insertArea">
            <tbody>
                <tr>
                    <td>Review Id</td>
                    <td>
                        <input value={userData.artistReviewId} disabled />
                    </td>
                    <td className="error">
                        {errorObj.artistReviewId}
                    </td>
                </tr>
                <tr>
                    <td>Name</td>
                    <td>
                        <input value={userData.artistName} onChange=
                            {e => setUserData(setProp(userData, "artistName", e.target.value))}
                        />
                    </td>
                    <td className="error">
                        {errorObj.artistName}
                    </td>
                </tr>
                <tr>
                    <td>Image</td>
                    <td>
                        <input value={userData.artistImage} onChange=
                            {e => setUserData(setProp(userData, "artistImage", e.target.value))}
                        />
                    </td>
                    <td className="error">
                        {errorObj.artistImage}
                    </td>
                </tr>
                <tr>
                    <td>Record Id</td>
                    <td>
                        <input value={userData.recordId} onChange=
                            {e => setUserData(setProp(userData, "recordId", e.target.value))}
                        />
                    </td>
                    <td className="error">
                        {errorObj.recordId}
                    </td>
                </tr>
                <tr>
                    <td>Catalog No</td>
                    <td>
                        <input value={userData.catalogNo} onChange=
                            {e => setUserData(setProp(userData, "catalogNo", e.target.value))}
                        />
                    </td>
                    <td className="error">
                        {errorObj.catalogNo}
                    </td>
                </tr>
                <tr>
                    <td>Role</td>
                    <td>
                    <select onChange=
                            {e => setUserData(setProp(userData, "webUserId", e.target.value))}
                            value={userData.webUserId}
                        >
                            {
                                roleList.map(role =>
                                    <option key={role.webUserId} value={role.webUserId} >
                                        {role.userEmail}
                                    </option>
                                )
                            }
                        </select>
                    </td>
                    <td className="error">
                        {errorObj.webUserId}
                    </td>
                </tr>
                <tr>
                    <td>
                        <br />
                        <button type="button" onClick={validate}>Save</button>
                    </td>
                    <td className="error" colSpan="2">
                        <br />
                        {errorObj.errorMsg}
                    </td>
                </tr>
            </tbody>
        </table>

    ); // ends the return statement

}; // end of function/component


/* 
 
 Example of web_user StringData output from insertUserAPI.jsp
 
 "webUserId": "1",
 "userEmail": "sallyk",
 "userPassword": "p",
 "userImage": "http://cis-linux2.temple.edu/~sallyk/pics_/sk_2017.jpg",
 "birthday": "",
 "membershipFee": "$123.45",
 "userRoleId": "2",
 "userRoleType": "Edit",
 "errorMsg": ""
 
 */
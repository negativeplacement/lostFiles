"use strict";
function Login(){
    const [isLoading, setIsLoading] = React.useState(false);
    const [userEmail, setUserEmail] = React.useState("");
    const [userPassword, setUserPassword] = React.useState("");
    const [msg, setMsg] = React.useState("");
    
    function isValid(){
        setIsLoading(true);
        var url = "../webUser/logIn?isEmail=" + encodeURI(userEmail) + "&isPassword=" + encodeURI(userPassword);
        ajax_alt(
            url,
            function(obj){
                if(obj.errorMsg.length > 0){
                    setMsg(<strong>{obj.errorMsg}</strong>);
                } else {
                    setMsg(
                        <div>
                            <h2>Welcome Web User {obj.webUserId} </h2>

                            Birthday: {obj.birthday} <br />
                            MembershipFee: {obj.membershipFee} <br />
                            User Role: {obj.userRoleId} {obj.userRoleType} <br />
                            <p> <img src={obj.userImage} /> </p>
                        </div>
                    );
                }
                setIsLoading(false);
            },
            function (errorMsg) {
                console.log("AJAX error. Here's the message: " + errorMsg);
                setMsg("ajax failure: " + errorMsg);
                setIsLoading(false);
            }
        );

    }
    if(isLoading){
        return(
            <div>
                <h1>... Loading ....</h1>
            </div>
        );
    }
    return(
        <div className="login">
            <div className="getInfo">
            <label>Email Address:</label> <input class='isEmail' value={userEmail} onChange={(e) => setUserEmail(e.target.value)} />
            <label>Password:</label><input class='isPassword' type='password' value={userPassword} onChange={(e) => setUserPassword(e.target.value)} />
            <button onClick={isValid}> Submit</button>
            </div>
            <div className="getResult">{msg}</div>
        </div>
    );
}
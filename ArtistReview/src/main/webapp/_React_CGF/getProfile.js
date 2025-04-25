"use strict";
const getProfile=(url)=>{
    const [isLoading, setIsLoading] = React.useState(true);
    const [msg, setMsg] = React.useState("");
    React.useEffect(()=>{
    ajax_alt(url,
        function(obj){
            if(obj.errorMsg.length > 0) {
                setMsg(<strong>{obj.errorMsg}</strong>);
            }else{
                setMsg(
                <div>
                    <h2>Welcome Web User {obj.webUserId} </h2>
                    
                    Birthday: {obj.birthday} <br />
                    MembershipFee: {obj.membershipFee} <br />
                    User Role: {obj.userRoleId} {obj.userRoleType} <br />
                    <p> <img src={obj.userImage} /> </p>
                </div>);
            }
            setIsLoading(false);
        },
        function(errorMsg){
            console.log("AJAX error. Here's the message: " + errorMsg);
            setMsg("ajax failure: " + errorMsg);
            setIsLoading(false);
        }
    );},[]);
    if(isLoading){
        console.log("Loading...");
        return <div> Loading... </div>
    }

    return(
        <div className="getProfile"> <div className="getResult">{msg}</div></div>
    );
}
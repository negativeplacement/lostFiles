"use strict";
const Logoff=(url)=>{
    const [isLoading, setIsLoading] = React.useState(true);
    const [msg, setMsg] = React.useState("");
    React.useEffect(()=>{
    ajax_alt(
        url,
        function (obj) {
            if (obj.errorMsg.length > 0) {
                setMsg(<strong>{obj.errorMsg}</strong>);
            } else {
                setMsg("User is now logged off");
            }
            setIsLoading(false);
        },
        function (errorMsg) {
            console.log("AJAX error. Here's the message: " + errorMsg);
            setMsg("ajax failure: " + errorMsg);
            setIsLoading(false);
        }
    );},[]);
    if(isLoading){
        return <div> Loading... </div>
    }
    
    return(
        <div className="Logoff"><div className="getResult">{msg}</div></div>
    );
}
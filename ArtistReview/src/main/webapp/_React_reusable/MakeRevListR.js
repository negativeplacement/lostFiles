"use strict";
function MakeRevListR({revList=[{}], title=""}){
    function MakeRevR({artistName = "blank", artistImage = "./imgRef/Default.jpg", catalogNo = 0, userRating = 0 }){
        const [isCatalog, setCatalog] = React.useState(catalogNo);
        const [isRating, setRating] = React.useState(userRating);
        const [catalogInput, setCatalogInput] = React.useState("");
        const [ratingInput, setRatingInput] = React.useState("");
        
        function isNewCatalog(){
            var findCatalog = Number(catalogInput);
            if(isNaN(findCatalog)){
                console.log(catalogInput + " is not a valid input");
                return;
            }
            setCatalog(catalogInput);
        }
        
        function isNewRating(){
            var verifyRating = Number(ratingInput);
            console.log(verifyRating);
            if(isNaN(verifyRating)){
                console.log(ratingInput + " is not a valid input");
            } else if(verifyRating < 0 || verifyRating > 10){
                console.log(ratingInput + " is not a valid input");
                return;
            }
            setRating(ratingInput);
        };
        
        return(
            <div className="rev">
                <img src={artistImage}/>
                <p> Artist: {artistName} </p>
                <p> Catalog No: {isCatalog} </p>
                <p> Rating: {isRating} </p>
                <button onClick={isNewCatalog}>Set Catalog No: </button>
                <input value={catalogInput} onChange={e => setCatalogInput(e.target.value)}/> <br/>
                <button onClick={isNewRating}>Set Rating (1-10): </button>
                <input value={ratingInput} onChange={e => setRatingInput(e.target.value)}/>
            </div>
        );
    }
    
    return(
        <div className="revList">
            <h2>{title}</h2>{
            (revList.length == undefined && typeof(revList) == "object") ?
            <MakeRevR /> : revList.map(rev =>
            <MakeRevR key={rev.id} artistName={rev.artistName} artistImage={rev.artistImage} catalogNo={rev.catalogNo} userRating={rev.userRating}/>)
            }
        </div>
    );
}
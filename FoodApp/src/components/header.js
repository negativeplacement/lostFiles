import "bootstrap/dist/css/bootstrap.min.css";
import React, {useState, useEffect} from 'react';
import {Navbar} from "reactstrap";
import {getAuth, onAuthStateChanged, signOut} from "firebase/auth";
import '../css/header.css';

export default () => {
  const [isLogIn, isLoggedIn] = useState(false);
  const [userCredential, isUserCredential] = useState("");
  const [userDisplayName, isUserDisplayName] = useState("");
  const auth = getAuth();
  useEffect(()=>{
    document.title = 'Home';
    onAuthStateChanged(auth, (isUser)=>{
      if(isUser){
        isLoggedIn(true);
        isUserDisplayName(isUser.displayName);
      } else{
        isLoggedIn(false);
      }
    });
    if(isLogIn){
      console.log("Signed In");
      const isUserFullName = userDisplayName.split(' ');
      const displayUserName = (isUserFullName.length < 2)?isUserFullName[0]:
       (isUserFullName.length == 2)?isUserFullName[0]+" "+ isUserFullName[1]:isUserFullName[0]+" "+isUserFullName[1].charAt(0).concat('. ')+isUserFullName[isUserFullName.length - 1];
      isUserCredential(displayUserName);
      window.onclick = function(event){
        if(!event.target.matches('.userDropDown')){
          var dropdowns = document.getElementsByClassName("getDropDown");
          var i;
          for(i = 0; i < dropdowns.length; i++){
            var openDropdown = dropdowns[i];
            if(openDropdown.classList.contains('show')){
              openDropdown.classList.remove('show');
            }
          }
        }
      }
    }
  }, [isLogIn]);
  const Logout=()=>{
    signOut(auth).then(()=>{
      document.location.href = "/";
      console.log("Signed out successfully")
    }).catch((error)=>{
      const errorCode = error.code;
      const errorMessage = error.message;
      console.log(errorCode, errorMessage);
    });
  }
  function getToggle(){
    document.getElementById("isDropDown").classList.toggle("show");
  }

  return(
    <div>
    <nav className="navbar fixed-top navbar-expand-lg bg-light">
      <div className="container-fluid justify-content-start" style={{ overflowWrap: "anywhere" }}>
      <a className="navbar-brand cookbookPro" href="/">CookBook Pro</a>
        <div className="navbar-nav">
          <a className="nav-link" href="/meal-plans">Meal Plans</a>
          <a className="nav-link" href="/search">Search</a>
          <a className="nav-link" href="/recipes">Recipes</a>
          <a className="nav-link" href="/shopping-list">Shopping List</a>
          {isLogIn ? (
            <div className="isUser">
              <button className="userDropDown" type="button" id="getUser" onClick={getToggle}>{userCredential}</button>
              <div className="getDropDown" id="isDropDown">
                <a href="/">Home</a>
                <a href="/">Profile</a>
                <a href="/" onClick={Logout}>Sign Out</a>
              </div>
            </div>
            ):
            <a className="isLogin" href="/Login"><input className="getLogin" type="button" id="isValid" value={"Log In"}/></a>}
        </div>
      </div>
    </nav>
    </div>
  );
};

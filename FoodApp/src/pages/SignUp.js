import React, {useState, useEffect} from 'react';
import {getAuth, createUserWithEmailAndPassword, updateProfile} from 'firebase/auth';
import {getFirestore} from "firebase/firestore";
import {collection, doc, getDoc, setDoc} from "firebase/firestore";
import {firebaseApp} from '../firebase/firebaseConfig.js';
import '../index.js'
import "../css/LoginSignUp.css";
import './home.js'

var SignUp=()=>{
  const[userName, isUserName] = useState("");
  const[userEmail, isUserEmail] = useState("");
  const[userPassword, isUserPassword] = useState("");
  const auth = getAuth();
  const firebaseDB = getFirestore(firebaseApp);
  useEffect(()=>{
    document.title = 'CookBook-Pro: SignUp';
    document.body.classList.add('loginPage');
    document.body.style.backgroundColor="#CFDEF3"
  }, []);
  const inputCredentials=async(e)=>{
    e.preventDefault();
    await createUserWithEmailAndPassword(auth, userEmail, userPassword)
    .then (async (userCredential)=>{
      const user = userCredential.user;
      const isUID = user.uid;
      const docSnap = await getDoc(doc(firebaseDB, "Users", isUID));
      if(!docSnap.exists()){
        await setDoc(doc(firebaseDB, "Users", isUID), {recipeID:[""]});
      }
    })
    .catch((error)=>{
      const errorCode = error.code;
      const errorMessage = error.message;
      console.log(errorCode, errorMessage);
    });
    await updateProfile(auth.currentUser, {displayName: document.getElementById("isName").value})
    .then(()=>{
      console.log(auth.currentUser);
      document.location.href = "/";
    })
    .catch((error)=>{
      const errorCode = error.code;
      const errorMessage = error.message;
      console.log(errorCode, errorMessage);
    });
  }

  return(
    <div className = "SignUp">
      <h1 className="Title">Sign Up</h1><br/>
      <form>
        <label className="FullName">Name<br></br></label>
        <input value={userName} onChange={e => isUserName(e.target.value)} className = "getFullName" type="text" id="isName" name="isName"/><br />
        <label className="Email">Email<br></br></label>
        <input value={userEmail} onChange={e => isUserEmail(e.target.value)} className = "getEmail" type="text" id="isEmail" name="isEmail"/><br/>
        <label className="Password">Password<br></br></label>
        <input value={userPassword} onChange={e => isUserPassword(e.target.value)} className="getPassword" type="text" id="isPassword" name="isPassword"/><br/><br/>
        <input className= "isSubmission" type="button" id="isSubmit" onClick={e=>inputCredentials(e)} value={"Sign Up"}/>
      </form>
    </div>
  )
}

export default SignUp;
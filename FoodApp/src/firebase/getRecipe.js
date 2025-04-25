import { doc, getDoc, getFirestore } from "firebase/firestore";
import { firebaseApp } from "./firebaseConfig.js";
import FirebaseConverter from "../managers_and_parsers/FirebaseConverter.js";

const db = getFirestore(firebaseApp);

const fb = new FirebaseConverter();
const recipeConverter = fb.recipeConverter;

/**
 * this function sucks ass cause it returns a promise
 * @param {String} recipeID
 * @returns promise
 */
async function GetRecipes(collection, recipeID) {
  //console.log("getting "+ recipeID + " from colleciton "+collection);

  const docRef = doc(db, collection, recipeID);
  const docSnap = await getDoc(docRef);

  if (docSnap.exists()) {
    const data = recipeConverter.fromFirestore(docSnap);
    return data;
  } else {
    // docSnap.data() will be undefined in this case
    console.log("No such document!");
    return null;
  }
}

export default GetRecipes;

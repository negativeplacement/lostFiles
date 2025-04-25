import {
  collection,
  query,
  where,
  onSnapshot,
  getFirestore,
} from "firebase/firestore";
import { firebaseApp } from "./firebaseConfig.js";

const db = getFirestore(firebaseApp);

/**
 * needs a collection name and useState setter 
 * returns an unsubscribe method to stop listening
 * @param {ReactUseStateFunction} setter
 * @param {String} collectionName
 * @returns {Unsubscribe}
 */
function getListener(collectionName, setter) {

  var q = query(collection(db, collectionName));

  const unsubscribe = onSnapshot(q, (querySnapshot) => {
    const recipes = [];
    querySnapshot.forEach((doc) => {

        //console.log("id="+doc.data().id)
        if(doc.data().id != 0){
            recipes.push(doc.data());
        }
      
    });
    setter(recipes);
  });
  return unsubscribe;
}

export default getListener;

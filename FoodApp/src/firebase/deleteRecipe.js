import { doc, deleteDoc, getFirestore } from "firebase/firestore";
import { firebaseApp } from "./firebaseConfig.js";

const db = getFirestore(firebaseApp);

async function deleteRecipe(collection, recipeID) {
  deleteDoc(doc(db, collection, recipeID));
}

export default deleteRecipe;

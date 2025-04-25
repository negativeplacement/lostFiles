import React, { useState, useEffect } from "react";
import getListener from "../firebase/setListener.js";
import {
  Card,
  ListGroup,
  ListGroupItem,
  ListGroupItemHeading,
  ListGroupItemText,
  ListInlineItem,
  Button,
} from "reactstrap";

import RecipeDetails from "./recipeDetails.js";
import deleteRecipe from "../firebase/deleteRecipe.js";

const savedMeals = () => {
  const [savedRecipes, setSavedRecipes] = useState([""]);
  const [showDetails, setShowDetails] = useState(false);
  const [meal, setMeal] = useState();

  const toggle = (recipe) => {
    setMeal(recipe);
    setShowDetails(!showDetails);
  };

  //important to only get 1 listener, so use this thingy
  useEffect(() => {
    const unsubscibe = getListener("savedRecipes", setSavedRecipes);
  }, []);

  function unsaveRecipe() {
    meal.isSaved = false;
    //close the modal and remove the recipe
    toggle();
    deleteRecipe("savedRecipes", String(meal.id));
  }

  let recipeDetails;

  const buttonOptions = (
    <>
      <Button color="primary" onClick={unsaveRecipe}>
        Unsave recipe
      </Button>
      <Button color="secondary" onClick={toggle}>
        Cancel
      </Button>
    </>
  );

  if (showDetails) {
    recipeDetails = (
      <RecipeDetails
        meal={meal}
        showDetails={showDetails}
        toggle={toggle}
        buttonOptions={buttonOptions}
      />
    );
  }

  return (
    <ListGroup>
      <ListGroupItemHeading>My Recipes</ListGroupItemHeading>
      {recipeDetails}
      {savedRecipes.map((recipe, key) => {
        return (
          <ListGroupItem action onClick={() => toggle(recipe)} key={key}>
            {recipe.name}
          </ListGroupItem>
        );
      })}
    </ListGroup>
  );
};

export default savedMeals;

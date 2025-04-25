import React, { useState, useEffect } from "react";
import getListener from "../firebase/setListener.js";
import {
  ListGroup,
  ListGroupItem,
  ListGroupItemHeading,
  Button,
  Input,
} from "reactstrap";

import RecipeDetails from "./recipeDetails.js";
import deleteRecipe from "../firebase/deleteRecipe.js";
import { Ingredient } from "../CustomObjects/Ingredient.js";

const quickOrder = () => {
  const [savedRecipes, setSavedRecipes] = useState([""]);
  const [showDetails, setShowDetails] = useState(false);
  const [meal, setMeal] = useState();
  const [email, setEmail] = useState("");

  const subject = "Your CookBook Pro shopping list";

  const mailLinkGenerator = () => {
    let body = "";
    if (savedRecipes != "") {
      let recipeList = "";
      const ingredientMap = new Map();
      savedRecipes.forEach((recipe, index) => {
        recipeList += `%0D%0A${index + 1}: ${recipe.name}`;
        recipe.ingredients.forEach((ingredient) => {
          const newIngredient = new Ingredient(
            ingredient.amount,
            ingredient.id,
            ingredient.name,
            ingredient.unit
          );

          if (ingredientMap.has(newIngredient.id)) {
            const existingIngredient = ingredientMap.get(newIngredient.id);
            existingIngredient.amount += newIngredient.amount;
          } else {
            ingredientMap.set(newIngredient.id, newIngredient);
          }
        });
      });
      body += `This Week's Meals:${recipeList}%0D%0A`;
      body += `%0D%0AIngredients:%0D%0A`;
      ingredientMap.forEach(
        (ingredient) =>
          (body += `[  ] ${ingredient.amount} ${ingredient.unit} ${ingredient.name}\n%0D%0A`)
      );
      body += "%0D%0A";
    }
    return (
      "https://mail.google.com/mail/?view=cm&fs=1&to=" +
      email +
      "&su=" +
      subject +
      "&body=" +
      body
    );
  };

  const handleInputChange = (e) => {
    setEmail(e.target.value);
  };

  const toggle = (recipe) => {
    setMeal(recipe);
    setShowDetails(!showDetails);
  };

  //important to only get 1 listener, so use this thingy
  useEffect(() => {
    const unsubscibe = getListener("quickOrder", setSavedRecipes);
  }, []);

  let recipeDetails;
  const buttonOptions = (
    <Button
      onClick={() => {
        toggle();
        deleteRecipe("quickOrder", String(meal.id));
      }}
    >
      Remove from order
    </Button>
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
    <>
      {recipeDetails}
      <ListGroup>
        <ListGroupItemHeading>Quick Order</ListGroupItemHeading>

        <Input
          type="email"
          placeholder="Enter your email"
          value={email}
          onChange={handleInputChange}
          required
        />

        <Button
          target="_blank"
          rel="noopener noreferrer"
          href={mailLinkGenerator()}
        >
          send an email to {email}
        </Button>

        {savedRecipes.map((recipe, key) => {
          return (
            <ListGroupItem action onClick={() => toggle(recipe)} key={key}>
              {recipe.name}
            </ListGroupItem>
          );
        })}
      </ListGroup>
    </>
  );
};

export default quickOrder;

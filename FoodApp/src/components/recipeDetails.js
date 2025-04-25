import React from "react";
import {
  Button,
  Modal,
  ModalHeader,
  ModalBody,
  ModalFooter,
  Container,
} from "reactstrap";
import PutRecipe from "../firebase/putRecipe.js";
import deleteRecipe from "../firebase/deleteRecipe.js";

/**
 * the parent of this component creates the button options
 * @param {Recipe} meal
 * @returns
 */
function RecipeDetails({ meal, showDetails, toggle, buttonOptions }) {

  if (!buttonOptions) {
    buttonOptions = (
      <Button color="secondary" onClick={toggle}>
        Close
      </Button>
    );
  }

  return (
    <Modal isOpen={showDetails} toggle={toggle}>
      <ModalHeader toggle={toggle}>{meal.name}</ModalHeader>
      <Container className="d-flex justify-content-center">
        <img src={meal.image} />
      </Container>

      <ModalBody>{String(meal.summary).replace(/<[^>]*>/g, "")}</ModalBody>
      <ModalFooter>{buttonOptions}</ModalFooter>
    </Modal>
  );
}

export default RecipeDetails;

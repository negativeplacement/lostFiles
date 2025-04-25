import React from "react";
import { ListGroup, ListGroupItemHeading, ListGroupItem } from "reactstrap";

const MeanPlanBar = () => {
  const week = [
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
  ];

  return (
    <ListGroup>
      <ListGroupItemHeading>My Meal Plan</ListGroupItemHeading>
      <ListGroupItem>Monday</ListGroupItem>
      <ListGroupItem>Tuesday</ListGroupItem>
      <ListGroupItem>Wednesday</ListGroupItem>
      <ListGroupItem>Thursday</ListGroupItem>
      <ListGroupItem>Friday</ListGroupItem>
      <ListGroupItem>Saturday</ListGroupItem>
      <ListGroupItem>Sunday</ListGroupItem>
    </ListGroup>
  );
};

export default MeanPlanBar;

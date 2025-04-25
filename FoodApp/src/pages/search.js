import React, { useState } from "react";
import { Row, Col, Container, Spinner } from "reactstrap";
import MealCard from "../components/mealCard";
import QuickOrder from "../components/quickOrder.js";
import SavedMeals from "../components/savedMeals";
import SearchBox from "../components/searchBox.js";
import MealDataManager from "../managers_and_parsers/MealDataManager.js";
import InfiniteScroll from "react-infinite-scroll-component";

const SearchPage = () => {
  const [searchResults, setSearchResults] = useState("initial page load");
  const [query, setQuery] = useState("");
  const [numResults, setNumResults] = useState(-1);

  const handleSearchResults = (results) => {
    setSearchResults(results.resultsList);
    setNumResults(results.totalResults);
  };

  const mealDataManager = new MealDataManager();

  const spinner = (
    <Col className="d-flex m-5 p-0 justify-content-center">
      <Spinner>Loading</Spinner>
    </Col>
  );
  //for infinte scroll
  const fetchMoreResults = async () => {
    try {
      //setMoreResults(true);
      // Wait for the query to complete and get the results
      const spoonacularQueryResults =
        await mealDataManager.queryRecipeFromSpoonacular(
          query,
          searchResults.length
        );

      setSearchResults(
        searchResults.concat(spoonacularQueryResults.resultsList)
      );
      //spoonacular caps results to 1000
      if (searchResults.length >= numResults || searchResults.length >= 999) {
        console.log(
          "searchResults.length=" +
            searchResults.length +
            " numResults=" +
            numResults
        );
        setNumResults(false);
      }
    } catch (error) {
      console.error("error: " + error); // Handle errors if the Promise is rejected
    }
  };

  //conditionally render the results
  let results;

  //if page loaded
  if (searchResults == "initial page load") {
    results = (
      <Col className="d-flex m-5 p-0 justify-content-center">
        <p className="text-secondary">search something</p>
      </Col>
    );
    //if there are results then put it into results varible to render
  } else if (Array.isArray(searchResults)) {
    results = (
      <InfiniteScroll
        dataLength={searchResults.length}
        next={fetchMoreResults}
        hasMore={numResults}
        loader={spinner}
        endMessage={
          <Col className="d-flex m-5 p-0 justify-content-center">
            <p className="text-secondary">
              Total {searchResults.length} results
            </p>
          </Col>
        }
      >
        <Container className="d-flex col-12 flex-wrap mt-3">
          {searchResults.map((meal, index) => (
            <MealCard key={index} meal={meal} />
          ))}
        </Container>
      </InfiniteScroll>
    );

    //if there are no results then we want to render a spinner :D
  } else if (!Array.isArray(searchResults)) {
    results = spinner;
  }

  return (
    <Container>
      <h1 className="d-flex justify-content-center">Search for recipes</h1>
      <Row>
        <Container className="d-flex justify-content-center">
          <br></br>
          <SearchBox
            onSearch={handleSearchResults}
            query={query}
            setQuery={setQuery}
          />
        </Container>
      </Row>
      <Row>
        <Col className="col-2">
          <SavedMeals />
        </Col>
        <Container className="col-8">{results}</Container>

        <Col className="col-2">
          <QuickOrder />
        </Col>
      </Row>
    </Container>
  );
};

export default SearchPage;

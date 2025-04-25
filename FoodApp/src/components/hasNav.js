import React, { useState, useEffect } from "react";

const HasNav = ({ children }) => {
  const [showNavBar, setShowNavBar] = useState(false);
  useEffect(() => {
    location.pathname == "/Login" || location.pathname == "/SignUp"
      ? setShowNavBar(false)
      : setShowNavBar(true);
  }, [location]);
  return <div>{showNavBar && children}</div>;
};

export default HasNav;

import React from "react";
import ReactDOM from "react-dom";
import App from "./App";
import Background from "./Background";
import "./index.css";
import "./Background.css";
import reportWebVitals from "./reportWebVitals";
import Test2 from "./Test2";
import Test3 from "./Test3.js";

ReactDOM.render(
  <React.StrictMode>
    <Test3 />
  </React.StrictMode>,
  document.getElementById("root")
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

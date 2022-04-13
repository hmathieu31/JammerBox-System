import React from "react";
import ReactDOM from "react-dom";
import {
  Routes,
  Route,
  Link,
  BrowserRouter
} from "react-router-dom";
import "./index.css";
import reportWebVitals from "./components/reportWebVitals";
import MainPage from "./elements/MainPage.js";
import SynthesizeTests from "./elements/SynthesizeTests.js";
import UnderConstruction from "./elements/TestsHistorics";

const rootElement = document.getElementById("root");

ReactDOM.render(
    <div>
      <BrowserRouter>
        <Routes>
            <Route exact path="/" element={<MainPage/>} />   
            <Route exact path="/synthesize_tests" element={<SynthesizeTests />} />
            <Route exact path="/tests_historics" element={<UnderConstruction />} />
        </Routes>
      </BrowserRouter>
    </div>,
    rootElement 
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

import React from "react";
import ReactDOM from "react-dom";
import Background from "./Background";
import "./index.css";
import "./Background.css";
import reportWebVitals from "./reportWebVitals";
import Test2 from "./ButtonList";
import MainPage from "./MainPage";

ReactDOM.render(
  <React.StrictMode>
    <MainPage />

import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import ScreenSelect from './ScreenSelect'
import reportWebVitals from './reportWebVitals';

ReactDOM.render(
  <React.StrictMode>
    <App />
    {/* <ScreenSelect/> */}
  </React.StrictMode>,
  document.getElementById("root")
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

const rootElement = document.getElementById("root");

ReactDOM.render(
    <div>
      <BrowserRouter>
        <Routes>
            <Route exact path="/" element={<MainPage/>} />   
            <Route exact path="/synthesize_tests" element={<SynthesizeTests />} />
        </Routes>
      </BrowserRouter>
    </div>,
    rootElement 
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

<<<<<<< HEAD
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
=======
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
>>>>>>> 510f1e5 (Commit with nothing important)
  </React.StrictMode>,
  document.getElementById("root")
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

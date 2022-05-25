import React from "react";
import ReactDOM from "react-dom";
import "./index.css";
import reportWebVitals from "./components/reportWebVitals";
import MainPage from "./elements/MainPage.js";
import InjectFault from "./elements/InjectFault.js";
import Test_historics from "./elements/TestsHistorics";
import Configuration from "./elements/Configuration";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "./components/alertTemplate";
import "./CSS/alerts.css";

const rootElement = document.getElementById("root");

// const AlertTemplate = ({message}) => (
//   <div className="alert red-bg">{message}</div>
// );

ReactDOM.render(
  <div>
    <BrowserRouter>
      <Routes>
        <Route exact path="/" element={<MainPage />} />
        <Route exact path="/synthesize_tests" element={<InjectFault />} />
        <Route exact path="/tests_historics" element={<Test_historics />} />
        <Route
          exact
          path="/configuration"
          element={
            <AlertProvider template={AlertTemplate} {...options}>
              <Configuration />
            </AlertProvider>
          }
        />
      </Routes>
    </BrowserRouter>
  </div>,
  rootElement
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

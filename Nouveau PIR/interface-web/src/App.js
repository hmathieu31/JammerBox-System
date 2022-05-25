import MainPage from "./elements/MainPage.js";
import SynthesizeTests from "./elements/SynthesizeTests.js";
import Test_historics from "./elements/TestsHistorics";
import Configuration from "./elements/Configuration";
import TestResult from "./elements/TestResult";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "react-alert-template-basic";
import { Routes, Route, BrowserRouter } from "react-router-dom";
import React, { useState } from "react";

export default function App() {
  const [recordState, setRecordState] = useState(false);

  const options = {
    position: "bottom center",
    timeout: 5000,
    offset: "30px",
    transition: "scale",
  };

  console.log(recordState);

  return (
    <div>
      <BrowserRouter>
        <Routes>
          <Route exact path="/" element={<MainPage />} />
          <Route exact path="/synthesize_tests" element={<SynthesizeTests />} />
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
          {/* Testing test result */}
          <Route
            exact
            path="/test_result"
            element={<TestResult name="Testing" />}
          />
        </Routes>
      </BrowserRouter>
    </div>
  );
}

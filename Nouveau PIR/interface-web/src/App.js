import MainPage from "./elements/MainPage.js";
import InjectFault from "./elements/InjectFault.js";
import FaultsInjectionLogs from "./elements/FaultsInjectionLogs";
import Configuration from "./elements/Configuration";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "./components/alertTemplate";
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
          <Route exact path="/synthesize_tests" element={<InjectFault />} />
          <Route
            exact
            path="/tests_historics"
            element={<FaultsInjectionLogs />}
          />
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
    </div>
  );
}

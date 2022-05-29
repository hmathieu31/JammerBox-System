<<<<<<< HEAD
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
=======
import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;
>>>>>>> 80b24cb2 (⚡ Implement the STM32 software  (#157))

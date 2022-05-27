import React from 'react'
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import Testing from "../components/TestList";

export default function FaultsInjectionLogs() {
  return (
    <>
      {ReturnButton()}
      <div className="frame-1">
        <div className="group-19">
          <p className="txt-271 flex-hcenter">Faults Injection Logs</p>
        </div>
        <div>
          <Testing />
        </div>
      </div>
    </>
  );
}
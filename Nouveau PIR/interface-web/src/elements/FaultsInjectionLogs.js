import React from "react";
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import Testing from "../components/TestList";

export default function FaultsInjectionLogs() {
  const deleteHistory = () => {
    fetch("http://localhost:8080/deleteLog", {
      method: "DELETE",
      mode: "cors",
      headers: { "Content-type": "application/json" },
      body: JSON.stringify(),
    }).then(
      (data) => {
        console.log(data.status);
      },
      (error) => {
        console.log(error);
      }
    );
  };

  return (
    <>
      {ReturnButton()}
      <div className="frame-1">
        <div className="group-19">
          <p className="txt-271 flex-hcenter">Faults Injection Logs</p>
        </div>
        <div className="flex-col" style={{ justifyContent: "center", alignContent: "center" }}>
          <button onClick={deleteHistory} className="group-6 txt-733">
            DELETE HISTORY
          </button>
        </div>
        <div>
          <Testing />
        </div>
      </div>
    </>
  );
}

import React from "react";
import "../CSS/TestResult.css";
import "../CSS/loadingSymbol.css";
import { Navigate, useNavigate } from "react-router-dom";
import ReturnButton from "../components/returnButton";

function TestResult(props) {
  return (
    <>
    {ReturnButton() } 
    <div className="frame-1">
      <div className="group-19">
        <p className="txt-271 flex-hcenter">Test result</p>
        <div className="flex-col">
          <h1>{props.name}</h1>
          <div class="lds-spinner"><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div></div>
        </div>
      </div>
    </div>
    </>
  );
}

export default TestResult;
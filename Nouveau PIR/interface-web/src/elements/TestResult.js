import React from "react";
import "../CSS/TestResult.css";
import ReturnButton from "../components/returnButton";
import LoadingSymbol from "../components/loadingSymbol";

function TestResult(props) {
  return (
    <>
    {ReturnButton() } 
    <div className="frame-1">
      <div className="group-19">
        <p className="txt-271 flex-hcenter">Test result</p>
        <div className="flex-col">
          <h1>{props.name}</h1>
          {LoadingSymbol() } 
        </div>
      </div>
    </div>
    </>
  );
}

export default TestResult;
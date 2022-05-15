import React from "react";
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import Testing from "../components/TestList";
import { useNavigate } from "react-router-dom";

export default function UnderConstruction() {
  let navigate = useNavigate();
  return (
    <>
      {ReturnButton()}
      <div className="frame-1">
        <div className="group-19">
          <p className="txt-271 flex-hcenter">Tests Historics</p>
        </div>
        <Testing />
      </div>
    </>
  );
}

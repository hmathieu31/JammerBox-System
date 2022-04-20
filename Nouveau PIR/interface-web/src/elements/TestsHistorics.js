import React from 'react'
import "../CSS/UnderConstruction.css";
import "../components/returnButton.js";
import ReturnButton from "../components/returnButton.js";

export default function UnderConstruction() {
  return (
    <>
      {ReturnButton()}
      <div className="frame-2" />
    </>
  );
}

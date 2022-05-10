import React from 'react'
import "../CSS/UnderConstruction.css";
import ReturnButton from "../components/ReturnButton.js";

export default function UnderConstruction() {
  return (
    <>
      {ReturnButton()}
      <div className="frame-2" />
    </>
  );
}

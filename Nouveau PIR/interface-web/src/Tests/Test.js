import React from "react";
import "./Test.css";

export default function Test() {
  function lol() {
    console.log("Le bouton a été appuyé");
  }
  return (
    <div className="desktop-1 flex-col-hstart-vstart clip-contents">
      <div className="group-374 flex-col">
        <div className="frame-5 flex-col-hcenter-vstart">
          <p className="txt-941">PIR Bail</p>
        </div>
        <button className="group-587" onClick={lol}>
          <p className="txt-831 flex-hcenter">TEST 1</p>
        </button>
        <button className="group-471">
          <p className="txt-831 flex-hcenter">TEST 2</p>
        </button>
        <button className="group-10810">
          <p className="txt-831 flex-hcenter">TEST 3</p>
        </button>
      </div>
    </div>
  );
}

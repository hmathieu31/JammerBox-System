import React from 'react'
import "../CSS/MainPage.css";
import "../components/returnButton.js";
import ReturnButton from "../components/returnButton.js";
import ButtonList from "../components/ButtonList";

function SynthesizeTests() {

  return (
    <>
      <div className="frame-1">
        <p className="txt-271 flex-hcenter">Synthesize Tests</p>
        {ReturnButton()}
        <div>
          <ButtonList />
        </div>
      </div>
    </>
  );
}

export default SynthesizeTests;

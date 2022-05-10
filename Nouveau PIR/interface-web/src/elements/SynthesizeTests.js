import React from 'react'
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";
import { useNavigate } from "react-router-dom";

export default function SynthesizeTests() {
  let navigate = useNavigate();
  return (
    <>
      <div className="frame-1">
        <p className="txt-271 flex-hcenter">Synthesize Tests</p>
        {ReturnButton()}
        <div>
          <ButtonList navigate={navigate} />
        </div>
      </div>
    </>
  );
}

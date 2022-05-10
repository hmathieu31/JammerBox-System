import React from 'react'
import "../CSS/MainPage.css";
import "../components/returnButton.js";
import ReturnButton from "../components/returnButton.js";
import ButtonList from "../components/ButtonList";
import { useNavigate } from "react-router-dom";

<<<<<<< HEAD
function SynthesizeTests() {

=======
export default function SynthesizeTests() {
  let navigate = useNavigate();
>>>>>>> origin/InterfaceWeb
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

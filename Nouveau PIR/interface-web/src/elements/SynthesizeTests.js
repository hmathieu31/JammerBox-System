import React from 'react'
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";
import { useNavigate } from "react-router-dom";
import ButtonAttributes from "../components/ButtonAttributes";

<<<<<<< HEAD
function SynthesizeTests() {

=======
export default function SynthesizeTests() {
  let navigate = useNavigate();
>>>>>>> 7aedd78a (Another merge...)
  return (
    <>
        <p className="txt-271 flex-hcenter">Synthesize Tests</p>
        {ReturnButton()}
        <div>
          <ButtonList navigate={navigate} buttonList={Buttons} />
        </div>
      </div>
    </>
  );
}

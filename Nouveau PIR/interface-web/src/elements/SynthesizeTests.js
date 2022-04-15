import "../CSS/MainPage.css";

import "../components/ReturnButton.js";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";

function SynthesizeTests() {
  return (
    <>
      <div className="frame-1">
        {ReturnButton()}
        <div>{ButtonList()}</div>
      </div>
    </>
  );
}

export default SynthesizeTests;

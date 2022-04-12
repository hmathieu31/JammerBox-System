import "../CSS/MainPage.css";
import "../CSS/Background.css";

import "../components/ReturnButton.js"
import ReturnButton from "../components/ReturnButton.js";

function SynthesizeTests() {
  var Buttons = ["Lol", "Test", "Haha!", "Truc", "NOOOOn"];

  function makeButton(data) {
    return (
      <button
        key={Buttons.indexOf(data)}
        className="group-6"
        onClick={console.log}
      >
        {data}
      </button>
    );
  }

  return (
    <>
    <div className="frame-1">
      { ReturnButton() }
      <div>
        {Buttons.map(makeButton, this)}
      </div>       
    </div>
    </>
  );
}

export default SynthesizeTests
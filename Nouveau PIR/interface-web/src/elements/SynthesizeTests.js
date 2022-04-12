import "../CSS/MainPage.css";
import "../components/ReturnButton.js";
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
        <p className="txt-271 flex-hcenter">Synthesize Tests</p>
        {ReturnButton()}
        <div>{ButtonList()}</div>
      </div>
    </>
  );

export default SynthesizeTests
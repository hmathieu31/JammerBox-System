import "../CSS/MainPage.css";
import "../components/ReturnButton.js";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";

export default function SynthesizeTests() {
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

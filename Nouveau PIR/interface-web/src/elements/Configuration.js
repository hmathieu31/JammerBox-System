import "../CSS/MainPage.css";
import "../components/ReturnButton.js";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";
import { useNavigate } from "react-router-dom";
import ButtonAttributes from "../components/ButtonAttributes";

export default function Configuration() {
  let navigate = useNavigate();
  let camButtons = [
    new ButtonAttributes("CONFIG CAM", false, null, false),
    new ButtonAttributes("RESET CAM CONFIG", false, null, false),
  ];
  let crkButtons = [
    new ButtonAttributes("CONFIG CRK", false, null, false),
    new ButtonAttributes("RESET CRK CONFIG", false, null, false),
  ];
  return (
    <>
      <div className="frame-1">
        <p className="txt-271 flex-hcenter">Configuration</p>
        {ReturnButton()}
        <div>
          <p className="txt-271">CRK</p>
        </div>
        <ButtonList buttonList={crkButtons} />
        <div>
          <p className="txt-271">CAM</p>
        </div>
        <ButtonList buttonList={camButtons} />
      </div>
    </>
  );
}

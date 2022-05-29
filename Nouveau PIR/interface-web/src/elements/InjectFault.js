import React from 'react'
import "../CSS/MainPage.css";
import ReturnButton from "../components/ReturnButton.js";
import ButtonList from "../components/ButtonList";
import { useNavigate } from "react-router-dom";
import ButtonAttributes from "../components/ButtonAttributes";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "../components/alertTemplate";

export default function SynthesizeTests() {
  let navigate = useNavigate();
  
  const options = {
    position: "bottom center",
    timeout: 5000,
    offset: "30px",
    transition: "scale",
    type: "success"
  };

  let Buttons = [
    new ButtonAttributes("CRK SHORT CIRCUIT", true, "Output Signal", true),
    new ButtonAttributes("CAM SHORT CIRCUIT", true, "Output Signal", true),
    new ButtonAttributes("CRK SPK", false, null, false),
    new ButtonAttributes("CRK RUN OUT", true, "Angle", false),
    new ButtonAttributes("CRK TOOTH OFF", true, "Teeth off", false),
    new ButtonAttributes("CRK GAP NOT DET", false, null, false),
    new ButtonAttributes("CRK SEG ADP ERR LIM", true, "Angle", false),
    new ButtonAttributes("CRK PULSE DURATION", true, "Duration", false),
    new ButtonAttributes("CRK POSN ENG STST", true, "Teeth Off", false),
    new ButtonAttributes("CAM DELAY", true, "°CRK", false),
    new ButtonAttributes("CAM SPK", false, null, false),
    new ButtonAttributes("CAM PAT ERR", false, null, false),
  ];
  return (
    <>
      <div className="frame-1">
        <p className="txt-272 flex-hcenter">Inject Fault</p>
        {ReturnButton()}
        <div>
          <AlertProvider template={AlertTemplate} {...options}>
            <ButtonList navigate={navigate} buttonList={Buttons} />
          </AlertProvider>
        </div>
      </div>
    </>
  );
}

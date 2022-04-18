import "../CSS/Background.css";
import "../CSS/MainPage.css";
import Popup from "reactjs-popup";
import ParameterPopup from "./ParameterPopup";
import { useState } from "react";

export default function ButtonList() {
  const [open, setOpen] = useState(false);
  const closeModal = () => setOpen(false);
  var Buttons = [
    "CRK SHORT CIRCUIT",
    "CAM SHORT CIRCUIT",
    "CRK SPK",
    "CRK RUN OUT",
    "CRK TOOTH OFF",
    "CRK GAP NOT DET",
    "CRK SEG ADP ERR LIM",
    "CRK PULSE DURATION",
    "CRK POSN ENG STST",
    "CAM DELAY",
    "CAM SPK",
    "CAM PAT ERR",
  ];

  function truc() {
    setOpen((o) => !o);
    console.log("Hoh");
  }

  function makeButton(data) {
    return (
      <div>
      <button
        key={Buttons.indexOf(data)}
        onClick={truc}
        className="group-6 txt-733"
      >
        {data}
      </button>
      {ParameterPopup(truc)}
      </div>
    );
  }
  return <div>{Buttons.map(makeButton, this)}</div>;
}

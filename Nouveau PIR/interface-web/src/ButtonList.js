import "./Background.css";
import ButtonFault from "./ButtonFault";
import "./MainPage.css";
import Popup from "reactjs-popup";

export default function ButtonList() {
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
    console.log("Lol");
  }

  function makeButton(data) {
    return (
      <button
        key={Buttons.indexOf(data)}
        onClick={truc}
        className="group-6 txt-733"
      >
        <Popup trigger={<button>Lol</button>}>
          <div>Lol</div>
        </Popup>
        {data}
      </button>
    );
  }
  return <div>{Buttons.map(makeButton, this)}</div>;
}

import "../CSS/MainPage.css";
import "../components/ReturnButton.js";
import ReturnButton from "../components/ReturnButton.js";
import React, { useState } from "react";
import { useAlert } from "react-alert";

export default function Configuration() {
  const [inputFileS, setInputFile] = useState(null);
  const inputFile = React.useRef();
  let fileReader;

  const onButtonClick = () => {
    inputFile.current.click();
  };

  const handleFileRead = (e) => {
    const content = fileReader.result;
    console.log(JSON.parse(content));
    // … do something with the 'content' …
  };

  const onChangeFile = (event) => {
    event.stopPropagation();
    event.preventDefault();
    var file = event.target.files[0];
    if (file) {
      fileReader = new FileReader();
      fileReader.onloadend = handleFileRead;
      fileReader.readAsText(file);
      setInputFile(file);
    } else {
      alert.show("Oh look, an alert!");
    }
  };

  return (
    <>
      <div className="frame-1">
        <p className="txt-271 flex-hcenter">Configuration</p>
        {ReturnButton()}
        <div>
          <p className="txt-271">CRK</p>
        </div>
        <button className="group-6 txt-733" onClick={onButtonClick}>
          CONFIG CRK
        </button>
        <button className="group-6 txt-733">RESET CRK CONFIG</button>
        <input
          id="myInput"
          type="file"
          style={{ display: "none" }}
          ref={inputFile}
          onChange={onChangeFile}
          accept=".json"
        />
        <div>
          <p className="txt-271">CAM</p>
          <button className="group-6 txt-733" onClick={onButtonClick}>
            CONFIG CAM
          </button>
          <button className="group-6 txt-733">RESET CAM CONFIG</button>
        </div>
      </div>
    </>
  );
}

import "../CSS/MainPage.css";
import "../components/ReturnButton.js";
import ReturnButton from "../components/ReturnButton.js";
import React, { useState } from "react";
import { useAlert } from "react-alert";
import RecordSignal from "../components/RecordSignal.js";

export default function Configuration() {
  const [inputFileS, setInputFile] = useState(null);
  const inputFile = React.useRef();
  const alert = useAlert();
  let fileReader;

  const sendData = (jsonData) => {
    fetch("http://localhost:8080/config", {
      method: "POST",
      mode: "cors",
      headers: { "Content-type": "application/json" },
      body: JSON.stringify(jsonData),
    }).then(
      (data) => {
        console.log(data.status);
      },
      (error) => {
        console.log(error);
      }
    );
  };

  const onButtonClickUpload = () => {
    inputFile.current.click();
    //alert.show("Configuration uploaded");
  };

  const onButtonClickConf = (conf) => {
    var jsonData;
    return () => {
      if (inputFileS == null) alert.show("No configuration uploaded!");
      else {
        if (conf === "CRK") {
          jsonData = {
            Config: "CRK",
            NumOfCrkTeeth: inputFileS["NumOfTeeth"],
            NumOfMissingTeeth: 0,
            NumOfGaps: inputFileS["NumOfGap"],
            DistanceTDC0toGap: inputFileS["Tdc0"],
            FirstSegErAngle: inputFileS["FirstErSegAngle"],
            NumberCylinder: inputFileS["NumOfCylinder"],
            SensorType: inputFileS["CrkSensorType"],
          };
        } else if (conf === "CAM") {
          jsonData = {
            Config: "CAM",
            NumCamEdge: inputFileS["Cam0NumOfEdges"],
            NumOfCam: 1,
            ActiveEdges: inputFileS["Cam0Active_edge"],
            SensorType: inputFileS["Cam0SensorType"],
            FilterTime: inputFileS["Cam0FilterInMicroSec"],
            CamEdges: inputFileS["Cam0EdgePos"],
          };
        }
        sendData(jsonData);
        alert.show("Configuration successfully uploaded!")
      }
    };
  };

  const onButtonClickRstConf = (conf) => {
    var jsonData;
    return () => {
      if (conf === "RESETCRK") {
        jsonData = { Config: "RESETCRK" };
      } else if (conf === "RESETCAM") {
        jsonData = { Config: "RESETCAM" };
      }
    sendData(jsonData); 
    alert.show("Configuration successfully reset!")
    };
  };

  const handleFileRead = () => {
    const content = fileReader.result;
    const configs = Object.entries(JSON.parse(content));
    const configDict = Object.assign(
      {},
      ...configs.map((x) => ({ [x[0]]: x[1] }))
    );
    setInputFile(configDict);
  };

  const onChangeFile = (event) => {
    event.stopPropagation();
    event.preventDefault();
    var file = event.target.files[0];
    if (file) {
      fileReader = new FileReader();
      fileReader.onloadend = handleFileRead;
      fileReader.readAsText(file);
      console.log(inputFileS);
      alert.show("Configuration file successfully uploaded!");
    } else {
      alert.show("Oh look, an alert!");
    }
  };

  return (
    <>
      <div className="frame-1">
        <p className="txt-271 flex-hcenter">Configuration</p>
        {ReturnButton()}
        <div className="upload-button flex-hcenter">
          <button className="group-6 txt-733" onClick={onButtonClickUpload}>
            UPLOAD CONFIGS
          </button>
        </div>
        <div className="configuration-list">
          <div className="flex-center">
            <p className="txt-271">CRK</p>
            <button
              className="group-6 txt-733"
              onClick={onButtonClickConf("CRK")}
              >
              CONFIG CRK
            </button>
            <button
              className="group-6 txt-733"
              onClick={onButtonClickRstConf("RESETCAM")}
              >
              RESET CRK CONFIG
            </button>
            <input
              id="myInput"
              type="file"
              style={{ display: "none" }}
              ref={inputFile}
              onChange={onChangeFile}
              accept=".json"
              />
          </div>
          <div className="flex-center">
            <p className="txt-271">CAM</p>
            <button
              className="group-6 txt-733"
              onClick={onButtonClickConf("CAM")}
            >
              CONFIG CAM
            </button>
            <button
              className="group-6 txt-733"
              onClick={onButtonClickRstConf("RESETCAM")}
            >
              RESET CAM CONFIG
            </button>
          </div>
        </div>
      </div>
    </>
  );
}

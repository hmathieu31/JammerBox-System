import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ShowTestDiv.css";
import ReplayButton from "../components/replayButton";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "../components/alertTemplate";
import React from "react";

export default function POPOSSpace(props) {

    const { id, test_name, date, parametre, value, result } = props;

    const options = {
      position: "bottom center",
      timeout: 5000,
      offset: "30px",
      transition: "scale",
      type: "success",
    };    

    return (
    <div className="group-13">
        <div className="rectangle-19">
        <p className="txt-8105 flex-hcenter"> {test_name} </p>
        </div>
        <div className="group-814 flex-row-vend">
              <div className="group-17">
              <div className="group-514">
                <p className="txt-311">Date {date} :  --- Result : {result} </p>
                <p className="txt-311">Parameter : {parametre} = {value} </p>
                </div>
              </div>
              <AlertProvider template={AlertTemplate} {...options}>
                <ReplayButton testName={test_name} testParam={parametre} valueSelect={value} />
              </AlertProvider>
        </div>
    </div>
    )
}
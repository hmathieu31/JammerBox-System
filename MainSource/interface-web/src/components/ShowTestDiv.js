import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ShowTestDiv.css";
import "../CSS/reloadSymbol.css";
import React from "react";

export default function POPOSSpace(props) {

    const { id, test_name, date, parametre, result } = props;

    return (
    <div className="group-13">
        <div className="rectangle-19">
        <p className="txt-8105 flex-hcenter"> {test_name} </p>
        </div>
        <div className="group-814 flex-row-vend">
              <div className="group-17">
              <div className="group-514">
                <p className="txt-311">Date {date} :  --- Result : {result} </p>
                <p className="txt-311">Parameter : {parametre}  </p>
                </div>
              </div>
              <button className="reload_symbol"/>
        </div>
    </div>
    )
}
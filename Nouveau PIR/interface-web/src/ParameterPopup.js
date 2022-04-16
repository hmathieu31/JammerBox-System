import React from "react";
import "./ParameterPopup.css";
import "./MainPage.css";

export default function ParameterPopup() {
  return (
    <div className="test-configuration flex-col-hstart-vstart clip-contents">
      <div className="group-917 flex-col-hcenter">
        <p className="txt-120 flex-hcenter">Nom du test</p>
        <div className="group-213 flex-col-hend">
          <div className="group-21">
            <p className="txt-649 flex-hcenter">Parametre :</p>
            <div className="rectangle-17" />
          </div>
          <div className="group-786 flex-row">
            <button className="group-6">
              <p className="txt-905 flex-hcenter">Let’s not go</p>
            </button>
            <button className="group-6">
              <p className="txt-637 flex-hcenter">Let’s go</p>
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}

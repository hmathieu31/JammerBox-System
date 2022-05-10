import React from "react";
import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import Modal from "react-modal";
import { Navigate, useNavigate } from "react-router-dom";

function ParameterPopup(props) {  
  let navigate = useNavigate();

  let Test_result = () => {
    navigate("/test_result")
  }

  return (
    <>
    <div className="test-configuration flex-col-hstart-vstart clip-contents">
      <div className="group-917 flex-col-hcenter">
        <p className="txt-120 flex-hcenter"> {props.test} </p>
        <div className="group-213 flex-col-hend">
          <div className="group-21">
            <p className="txt-649 flex-hcenter">Parametre :</p>
            <input className="rectangle-17 txt-905" />
          </div>
          <div className="group-786 flex-row">
            <button onClick={props.handleOpenClose} className="group-6">
              <p className="txt-905 flex-hcenter">Let’s not go</p>
            </button>
            <button onClick={() => {props.handleOpenClose(); Test_result();} } className="group-6">
              <p className="txt-637 flex-hcenter">Let’s go</p>
            </button>
          </div>
        </div>
      </div>
    </div>
    </>
  );
}


export default class ButtonList extends React.Component {
  
  constructor() {
    super();
    this.state = {
      showModal: false,
      testName: "POLO",
    };

    this.Buttons = [
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
  }

  handleOpenClose() {
    return () => {
      this.setState((prev) => ({
        showModal: !prev.showModal,
      }));
    };
  }

  makeButton(data) {
    return (
      <div>
        <button
          key={this.Buttons.indexOf(data)}
          onClick={this.handleOpenClose(data)}
          className="group-6 txt-733"
        >
          {data}
        </button>
        <Modal isOpen={this.state.showModal}>
          <ParameterPopup test={data} 
                          handleOpenClose={this.handleOpenClose()}
          />
        </Modal>
      </div>
    );
  }
  render() {
    return <div>{this.Buttons.map(this.makeButton, this)}</div>;
  }
}

import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
<<<<<<< HEAD
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
=======
import ParameterPopup from "./ParameterPopup";
import React from "react";
import Modal from "react-modal";
import { Navigate, useNavigate } from "react-router-dom";

class ButtonAttributes {
  constructor(name, hasparam, paramsTab, IsSelect) {
    this.hasParam = hasparam;
    this.testName = name;
    this.params = paramsTab;
    this.isSelect = IsSelect;
  }

  getHasParam() {
    return this.hasParam;
  }

  getParams() {
    return this.params;
  }

  getTestName() {
    return this.testName;
  }

  getIsSelect() {
    return this.isSelect;
  }
>>>>>>> 7aedd78a (Another merge...)
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

  handleOpenClose(data) {
    return () => {
<<<<<<< HEAD
      this.setState((prev) => ({
        showModal: !prev.showModal,
=======
      this.setState(() => ({
        testName: data.getTestName(),
        testParam: data.getParams(),
        showModal: data.getHasParam(),
        isSelect: data.getIsSelect(),
>>>>>>> 7aedd78a (Another merge...)
      }));
    };
  }

<<<<<<< HEAD
  makeButton(data) {
=======
  changeData = (e) => {
    console.log(e.target.value);
    this.setState({
      valueSelect: e.target.value,
    });
  };

  sendData = (jsonData) => {
    fetch("http://localhost:8080/run", {
      method: "POST",
      mode: "cors",
      headers: { "Content-type": "application/json" },
      body: JSON.stringify(jsonData),
    }).then(() => {
      console.log("Success with running test");
    });
  };

  runTest = () => {
    var jsonData = {
      TestName: this.state.testName.replace(/\s/g, ""),
      TestParameter: this.state?.testParam.replace(/\s/g, ""),
      TestValue: this.state.valueSelect,
    };

    console.log("Run test");
    this.sendData(jsonData);

    console.log(JSON.stringify(jsonData));

    this.setState({
      showModal: false,
    });
  };

  directRunTest = (data) => {
    return () => {
      var jsonData = {
        TestName: data.getTestName(),
        TestParameter: "",
        TestValue: "",
      };
      this.sendData(jsonData);
      setTimeout(() => {
        this.props.navigate("/");
      }, 2000);
    };
  };

  makeButton = (data, index) => {
>>>>>>> 7aedd78a (Another merge...)
    return (
      <div>
        <button
          key={this.Buttons.indexOf(data)}
          onClick={this.handleOpenClose}
          className="group-6 txt-733"
        >
<<<<<<< HEAD
          {data}
        </button>
        <Modal isOpen={this.state.showModal}>
          <ParameterPopup test={data} 
                          handleOpenClose={this.handleOpenClose()}
=======
          <ParameterPopup
            handleOpenClose={this.handleOpenClose(data)}
            handleRun={this.runTest}
            handleChange={this.changeData}
            testName={this.state.testName}
            testParam={this.state.testParam}
            isSelect={this.state.isSelect}
>>>>>>> 7aedd78a (Another merge...)
          />
        </Modal>
      </div>
    );
  }
  render() {
    return <div>{this.Buttons.map(this.makeButton, this)}</div>;
  }
}

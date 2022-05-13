import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
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
      this.setState(() => ({
        testName: data.getTestName(),
        testParam: data.getParams(),
        showModal: data.getHasParam(),
        isSelect: data.getIsSelect(),
      }));
    };
  }

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
    }).then(
      (data) => {
        console.log(data.status);
      },
      (error) => {
        console.log(error);
      }
    );
  };

  runTest = () => {
    var jsonData = {
      TestName: this.state.testName,
      TestParameter: this.state?.testParam,
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
    return (
      <div>
        <button
          key={this.Buttons.indexOf(data)}
          onClick={this.handleOpenClose}
          className="group-6 txt-733"
        >
          <ParameterPopup
            handleOpenClose={this.handleOpenClose(data)}
            handleRun={this.runTest}
            handleChange={this.changeData}
            testName={this.state.testName}
            testParam={this.state.testParam}
            isSelect={this.state.isSelect}
          />
        </Modal>
      </div>
    );
  }
  render() {
    return <div>{this.Buttons.map(this.makeButton, this)}</div>;
  }
}

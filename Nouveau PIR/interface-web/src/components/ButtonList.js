import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import ParameterPopup from "./ParameterPopup";
import React from "react";
import Modal from "react-modal";

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
      testName: "",
      testParam: "",
      isSelect: false,
      valueSelect: null,
    };
    this.Buttons = [
      new ButtonAttributes("CRK SHORT CIRCUIT", true, "Output Signal", true),
      new ButtonAttributes("CAM SHORT CIRCUIT", true, "Output Signal", true),
      new ButtonAttributes("CRK SPK", false, null, false),
      new ButtonAttributes("CRK RUN OUT", true, "Angle", false),
      new ButtonAttributes("CRK TOOTH OFF", true, "Teeth off", false),
      new ButtonAttributes("CRK GAP NOT DET", false, null, false),
      new ButtonAttributes("CRK SEG ADP ERR LIM", true, "Angle", false),
      new ButtonAttributes("CRK PULSE DURATION", true, "Duration", false),
      new ButtonAttributes("CRK POSN ENG STST", true, "Teeth Off", false),
      new ButtonAttributes("CAM DELAY", true, "°CRK", false),
      new ButtonAttributes("CAM SPK", false, null, false),
      new ButtonAttributes("CAM PAT ERR", false, null, false),
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
    return (
      <div key={index}>
        <Modal
          isOpen={this.state.showModal}
          className="frame-5"
          ariaHideApp={false}
          key={index}
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
        <button
          onClick={
            data.getHasParam()
              ? this.handleOpenClose(data)
              : this.directRunTest(data)
          }
          className="group-6 txt-733"
        >
          {data.getTestName()}
        </button>
      </div>
    );
  };
  render() {
    return <div>{this.Buttons.map(this.makeButton)}</div>;
  }
}

import React from "react";
import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
<<<<<<< HEAD
=======
import ParameterPopup from "./ParameterPopup";
import React from "react";
>>>>>>> origin/InterfaceWeb
import Modal from "react-modal";
import { Navigate, useNavigate } from "react-router-dom";

<<<<<<< HEAD
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
>>>>>>> origin/InterfaceWeb
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

  handleOpenClose() {
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
>>>>>>> origin/InterfaceWeb
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
>>>>>>> origin/InterfaceWeb
    return (
      <div key={index}>
        <Modal
          isOpen={this.state.showModal}
          className="frame-5"
          ariaHideApp={false}
          key={index}
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
>>>>>>> origin/InterfaceWeb
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

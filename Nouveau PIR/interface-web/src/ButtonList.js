import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import ParameterPopup from "./ParameterPopup";
import React from "react";
import Modal from "react-modal";

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
          {data}
        </button>
        <Modal isOpen={this.state.showModal}>
          <ParameterPopup
            handleOpenClose={this.handleOpenClose(data)}
            testName={this.state.testName}
          />
        </Modal>
      </div>
    );
  };
  render() {
    return <div>{this.props.buttonList.map(this.makeButton)}</div>;
  }
}

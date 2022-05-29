import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import ParameterPopup from "./ParameterPopup";
import React from "react";
import Modal from "react-modal";
import { Provider as AlertProvider } from "react-alert";
import AlertTemplate from "../components/alertTemplate";
import { withAlert } from "react-alert";
import RaspiProp from "../RaspiProp.json";

const options = {
  position: "bottom center",
  timeout: 5000,
  offset: "30px",
  transition: "scale",
  type: "error",
};

class ButtonList extends React.Component {
  constructor() {
    super();
    this.state = {
      showModal: false,
      testName: "POLO",
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
    console.log(jsonData);
    fetch("http://" + RaspiProp["IP_ADDRESS"] + ":8080/run", {
      method: "POST",
      mode: "cors",
      headers: { "Content-type": "application/json" },
      body: JSON.stringify(jsonData),
    }).then(
      (data) => {
        console.log(data.status);
      },
      (error) => {
        console.log("Did not send data!");
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
      valueSelect: null,
    });

    this.props.alert.show("Jamming successfully started");

    console.log("Value after sending test parameters");
    console.log(this.state.valueSelect);
  };

  directRunTest = (data) => {
    return () => {
      var jsonData = {
        TestName: data.getTestName(),
        TestParameter: "",
        TestValue: "",
      };
      this.sendData(jsonData);
      this.props.alert.show("Jamming successfully started");
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
          <AlertProvider template={AlertTemplate} {...options}>
            <ParameterPopup
              handleOpenClose={this.handleOpenClose(data)}
              handleRun={this.runTest}
              handleChange={this.changeData}
              testName={this.state.testName}
              testParam={this.state.testParam}
              isSelect={this.state.isSelect}
              valueSelected={this.state.valueSelect}
            />
          </AlertProvider>
        </Modal>
        <button
          key={this.Buttons.indexOf(data)}
          onClick={this.handleOpenClose}
          className="group-6 txt-733"
        >
          <AlertProvider template={AlertTemplate} {...options}>
            <ParameterPopup
              handleOpenClose={this.handleOpenClose(data)}
              handleRun={this.runTest}
              handleChange={this.changeData}
              testName={this.state.testName}
              testParam={this.state.testParam}
              isSelect={this.state.isSelect}
              valueSelected={this.state.valueSelect}
            />
          </AlertProvider>
        </Modal>
      </div>
    );
  }
  render() {
    return (
      <div className="button-list-div">
        {this.props.buttonList.map(this.makeButton)}
      </div>
    );
  }
}

export default withAlert()(ButtonList);

import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import React from "react";
import Modal from "react-modal";

class ParameterPopup extends React.Component {
  options = [
    {
      label: "Ground",
      value: "ground",
    },
    {
      label: "Battery",
      value: "battery",
    },
  ];

  render() {
    const { handleOpenClose } = this.props;
    return (
      <div className="test-configuration flex-col-hstart-vstart clip-contents">
        <div className="group-917 flex-col-hcenter">
          <p className="txt-120 flex-hcenter">{this.props.testName}</p>
          <div className="group-213 flex-col-hend">
            <div className="group-21">
              <p className="txt-649 flex-hcenter">{this.props.testParam} :</p>
              {this.props.isSelect ? (
                <select
                  onChange={this.props.handleChange}
                  className="rectangle-17 txt-905 flex-hcenter"
                >
                  <option value="none" selected disabled hidden>
                    Select option
                  </option>
                  {this.options.map((option) => (
                    <option value={option.value}>{option.label}</option>
                  ))}
                </select>
              ) : (
                <div>
                  <input
                    type="number"
                    pattern="[0-9]*"
                    className="rectangle-17 txt-905 flex-hcenter"
                    onChange={this.props.handleChange}
                  />
                </div>
              )}
            </div>
            <div className="group-786 flex-row">
              <button onClick={handleOpenClose} className="group-6">
                <p className="txt-637 flex-hcenter">Cancel</p>
              </button>
              <button onClick={this.props.handleRun} className="group-6">
                <p className="txt-637 flex-hcenter">Run Test</p>
              </button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

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
    this.Buttons = new Array(
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
      new ButtonAttributes("CAM PAT ERR", false, null, false)
    );
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

  runTest = () => {
    console.log("Run test");
    console.log(this.state.valueSelect);
    this.setState({
      showModal: false,
    });
  };

  makeButton(data) {
    return (
      <div>
        <Modal isOpen={this.state.showModal} className="frame-5">
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
          key={this.Buttons.indexOf(data)}
          onClick={this.handleOpenClose(data)}
          className="group-6 txt-733"
        >
          {data.getTestName()}
        </button>
      </div>
    );
  }
  render() {
    return <div>{this.Buttons.map(this.makeButton, this)}</div>;
  }
}

import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import React from "react";
import Modal from "react-modal";

class ParameterPopup extends React.Component {
  render() {
    const { handleOpenClose } = this.props;
    return (
      <div className="test-configuration flex-col-hstart-vstart clip-contents">
        <div className="group-917 flex-col-hcenter">
          <p className="txt-120 flex-hcenter">{this.props.testName}</p>
          <div className="group-213 flex-col-hend">
            <div className="group-21">
              <p className="txt-649 flex-hcenter">Parametre :</p>
              <input className="rectangle-17 txt-905" />
            </div>
            <div className="group-786 flex-row">
              <button onClick={handleOpenClose} className="group-6">
                <p className="txt-637 flex-hcenter">Let’s not go</p>
              </button>
              <button onClick={handleOpenClose} className="group-6">
                <p className="txt-637 flex-hcenter">Let’s go</p>
              </button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

class ButtonAttributes {
  constructor(name, hasparam, paramsTab) {
    this.hasParam = hasparam;
    this.testName = name;
    this.params = paramsTab;
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
}

export default class ButtonList extends React.Component {
  constructor() {
    super();
    this.state = {
      showModal: false,
      testName: "",
    };
    this.Buttons = new Array(
      new ButtonAttributes("CRK SHORT CIRCUIT", false, null),
      new ButtonAttributes("CAM SHORT CIRCUIT", false, null),
      new ButtonAttributes("CRK SPK", false, null),
      new ButtonAttributes("CRK RUN OUT", true, "Angle"),
      new ButtonAttributes("CRK TOOTH OFF", true, "Teeth off"),
      new ButtonAttributes("CRK GAP NOT DET", false, null),
      new ButtonAttributes("CRK SEG ADP ERR LIM", false, null),
      new ButtonAttributes("CRK PULSE DURATION", false, null),
      new ButtonAttributes("CRK POSN ENG STST", false, null),
      new ButtonAttributes("CAM DELAY", false, null),
      new ButtonAttributes("CAM SPK", false, null),
      new ButtonAttributes("CAM PAT ERR", false, null)
    );
  }

  handleOpenClose(data) {
    return () => {
      this.setState((prev) => ({
        testName: data.getTestName(),
        showModal: !prev.showModal,
      }));
    };
  }

  truc() {
    console.log("Hoh");
  }

  makeButton(data) {
    console.log(data);
    return (
      <div>
        <Modal isOpen={this.state.showModal} className="frame-5">
          <ParameterPopup
            handleOpenClose={this.handleOpenClose(data)}
            testName={this.state.testName}
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

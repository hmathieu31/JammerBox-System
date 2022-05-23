import React from "react";

export default class ParameterPopup extends React.Component {
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
                    placeholder="0"
                  />
                </div>
              )}
            </div>
            <div className="group-786 flex-row">
              <button onClick={handleOpenClose} className="group-6-cancel">
                <p className="txt-637 flex-hcenter">Cancel</p>
              </button>
              <button onClick={this.props.handleRun} className="group-6-run">
                <p className="txt-637 flex-hcenter">Run Test</p>
              </button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

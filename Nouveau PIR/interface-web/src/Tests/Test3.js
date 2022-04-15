import React from "react";
import "./Test3.css";
import Test2 from "./Test2";
import returnButton from "./returnButton";
import { render } from "@testing-library/react";

class Test3 extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      showComponent: false,
    };
    this._onButtonClick = this._onButtonClick.bind(this);
  }
  testdiv() {
    return (
      <div className="group-19">
        <p className="txt-271 flex-hcenter">PIR Interface</p>
        <div className="flex-col">
          <button className="group-6">
            <p className="txt-733 flex-hcenter" onClick={this._onButtonClick}>
              Synthesize tests
            </p>
          </button>
          <button className="group-6">
            <p className="txt-733 flex-hcenter">Test historics</p>
          </button>
        </div>
      </div>
    );
  }

  _onButtonClick() {
    this.setState({
      showComponent: true,
    });
  }

  render() {
    return (
      <div className="frame-1">
        {this.state.showComponent ?  
          <>
            <Test2 />
            <returnButton />
          </>
        :
        this.testdiv()
        }
      </div>
    );
  }
}

export default Test3;

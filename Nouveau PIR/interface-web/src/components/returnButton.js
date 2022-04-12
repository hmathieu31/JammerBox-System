import React from "react"
import "./returnButton.css"

class returnButton extends React.Component {
    constructor(props) {
      super(props);
      this.state = {
        showComponent: false,
      };
      this._onButtonClick = this._onButtonClick.bind(this);
    }
    testdiv() {
      return (
        <div className="arrow-circle-up flex-col-hstart-vstart clip-contents">
            <button  key={"Return"}> </button>
        </div>
      );
    }

_onButtonClick() {
    this.setState({
      showComponent: true,
    });
  }
}

export default returnButton
import "./Background.css";
import "./MainPage.css";
import React from "react";

class ButtonFault extends React.Component {
  constructor(props) {
    super(props);
  }

  showAlert() {
    console.log("Do not show alert");
  }

  render() {
    this.showAlert();
    return <div className="group-6 txt-733">{this.props.data}</div>;
  }
}

export default ButtonFault;

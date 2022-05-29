import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/ParameterPopup.css";
import "../CSS/replaySymbol.css";
import { withAlert } from "react-alert";
import React from "react";

class ReplayButton extends React.Component {
    constructor() {
        super();
        this.state = {
          testName: "",
          testParam: "",
          valueSelect: null,
        };
      }


    sendData = (jsonData) => {
        fetch("http://localhost:8080/run", {
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

    replayTest = () => {
        var jsonData = {
            TestName: this.props.testName,
            TestParameter: this.props?.testParam,
            TestValue: this.props.valueSelect,
        };
    
        console.log("Run test");
        this.sendData(jsonData);
    
        console.log(JSON.stringify(jsonData));
        
        this.props.alert.show("Jamming successfully replay");
    
        console.log("Test name");
        console.log(this.props.testName)
        console.log("Value after sending test parameters");
        console.log(this.props.valueSelect);
    }

    render() {
        return (
        <div className="reload_symbol">
            <button onClick={this.replayTest} className="replay-symbol" type="submit" value="" />
        </div>
        );
    }
}

export default withAlert()(ReplayButton);

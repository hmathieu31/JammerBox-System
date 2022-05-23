import React from "react";
import "../CSS/reloadSymbol.css";
import { useNavigate } from "react-router-dom";

export default class RelaunchButton extends React.Component{
  // const navigate = useNavigate();
  // const TestResult = () => {
  //   navigate("/test_result");
  // };

  constructor() {
    super();
    this.state = {
      testNumber: 0,
      testName: "",
      testDate: "",
      testParam: "",
      testResult: ""  
    };
  }

  getTestData = () => {
    const jsonData = require('../historicData.json');
    console.log(jsonData);
  
    const spaces = Object.entries(jsonData).map((obj) => {
      var newObj = obj[1][this.testNumber];
      console.log(newObj.id);
    return() => {  
      this.setState(() => ({        
        id={newObj.id}
        testName={newObj.test_name}
        testDate={newObj.date}
        testParam={newObj.parametre}
        testResult={newObj.result}
      }));
  }})
  }

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

    console.log("Running test");
    this.sendData(jsonData);

    console.log(JSON.stringify(jsonData));
  };

  makeButton = (data) => {
    return (
      <div>
        <button
          onClick={
            this.runTest(data)
          }
          className="reload_symbol"
        >
        </button>
      </div>
    );
  };

  render() {
    return <div>{this.props.makeButton}</div>;
  }
}

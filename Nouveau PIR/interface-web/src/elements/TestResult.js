import React from "react";
import "../CSS/MainPage.css";
import "../CSS/TestResult.css";
import LoadingSymbol from "../components/loadingSymbol"; 
import ReturnButton from "../components/ReturnButton";
import POPOSSpace from "../components/ShowTestDiv";

function TestResult() {  
  const jsonData = require("../historicData.json");
  console.log(jsonData);

  var nTest = 0;
  var testRdy = 0;

  const spaces = Object.entries(jsonData).map((obj) => {
      var newObj = obj;
      if (newObj[0] == "numberOfTests") {
        nTest = newObj[1];
      }
      
      if(newObj[1].id == nTest){ 
        return (  
            <POPOSSpace
                id={newObj[1].id}
                test_name={newObj[1].test_name}
                date={newObj[1].date}
                parametre={newObj[1].parametre}
                result={newObj[1].result}
            />
        );
      }
    });
  
  const waitForTest = () => {
    return () => {
      setTimeout(() => {
        testRdy = 1;  
      }, 2000);
    };
  }

  return (
    <>
      <div className="frame-1">
        {ReturnButton()}
        {waitForTest()}
        {testRdy == 1 ?
          (<div className="POPOSList">{spaces}</div>) :
          (<div className="POPOSList"><h1>Estamos esperando al test</h1></div>)   
        }
      </div>
    </> 
  );
}

export default TestResult;

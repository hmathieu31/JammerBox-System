import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/Historics.css";
import React from "react";
import POPOSSpace from "./ShowTestDiv";

export default function Testing() {
  const jsonData = require("../historicData.json");
  console.log(jsonData);

  //console.log(Object.entries(jsonData));

  const spaces = Object.entries(jsonData).map((obj) => {
    var newObj = obj;
    if(newObj[0] != "numberOfTests"){
      console.log(newObj[1].id);
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

  return <div className="POPOSList">{spaces}</div>;
}

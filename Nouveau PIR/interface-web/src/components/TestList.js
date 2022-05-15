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
    var newObj = obj[1];
    console.log(newObj.id);
    return (
      <POPOSSpace
        id={newObj.id}
        test_name={newObj.test_name}
        date={newObj.date}
        parametre={newObj.parametre}
        result={newObj.result}
      />
    );
  });

  return <div className="POPOSList">{spaces}</div>;
}

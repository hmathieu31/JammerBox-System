import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/Historics.css";
import React from "react";
<<<<<<< HEAD
import POPOSSpace from './ShowTestDiv';
=======
import POPOSSpace from "./ShowTestDiv";
>>>>>>> origin/InterfaceWeb

export default function Testing() {
  const jsonData = require("../historicData.json");
  console.log(jsonData);

<<<<<<< HEAD
=======
  //console.log(Object.entries(jsonData));

>>>>>>> origin/InterfaceWeb
  const spaces = Object.entries(jsonData).map((obj) => {
    var newObj = obj[1];
    console.log(newObj.id);
    return (
<<<<<<< HEAD
        <div className="POPOSList">
          { spaces }
        </div>
    )
=======
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
>>>>>>> origin/InterfaceWeb
}

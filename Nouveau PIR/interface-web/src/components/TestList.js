import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/Historics.css";
import React, { useEffect, useState } from "react";
import POPOSSpace from "./ShowTestDiv";
<<<<<<< HEAD
import RaspiProp from "../RaspiProp.json";
=======
>>>>>>> 297663c1 (InterfaceWeb integrated into main (#152))

export default function Testing() {
  const [jsonData, setJsonData] = useState(
    JSON.parse(localStorage.getItem("testlog"))
  );

  useEffect(() => {
    const id = setInterval(
      () =>
<<<<<<< HEAD
        fetch("http://" + RaspiProp["IP_ADDRESS"] + ":8080/getLog", {
=======
        fetch("http://localhost:8080/getLog", {
>>>>>>> 297663c1 (InterfaceWeb integrated into main (#152))
          method: "GET",
          mode: "cors",
          headers: { "Content-type": "application/json" },
        }).then((data) => {
          data.json().then((jsondata) => {
            console.log(jsondata);
            localStorage.setItem("testlog", JSON.stringify(jsondata));
            setJsonData(jsondata);
          });
        }),
      1500
    );
    return () => clearInterval(id);
  }, []);

  const spaces = Object.entries(
    jsonData === null || jsonData === undefined ? "l" : jsonData
<<<<<<< HEAD
=======

>>>>>>> 297663c1 (InterfaceWeb integrated into main (#152))
  ).map((obj) => {
    var newObj = obj[1];

    return (
      <POPOSSpace
        id={newObj.id}
        test_name={newObj.test_name}
        date={newObj.date}
        parametre={newObj.parametreType}
        value={newObj.parametreValue}
        result={newObj.result}
      />
    );
  });

<<<<<<< HEAD
  return (
    <div>
      {jsonData === null || jsonData === undefined ? (
        <div></div>
      ) : (
        <div className="POPOSList">{spaces}</div>
      )}
=======
  return(
    <div>
    {(jsonData === null || jsonData === undefined) ? (
      <div></div>
    ) : (
      <div className="POPOSList">{spaces}</div>
    )}
>>>>>>> 297663c1 (InterfaceWeb integrated into main (#152))
    </div>
  );
}

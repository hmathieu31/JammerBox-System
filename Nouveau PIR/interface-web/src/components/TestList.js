import "../CSS/Background.css";
import "../CSS/MainPage.css";
import "../CSS/Historics.css";
import React, { useEffect, useState } from "react";
import POPOSSpace from "./ShowTestDiv";

export default function Testing() {
  const [jsonData, setJsonData] = useState(
    JSON.parse(localStorage.getItem("testlog"))
  );

  useEffect(() => {
    const id = setInterval(
      () =>
        fetch("http://localhost:8080/getLog", {
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
    jsonData == null || jsonData == undefined ? "l" : jsonData
  ).map((obj) => {
    var newObj = obj[1];

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

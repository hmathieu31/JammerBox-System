const usb = require("usb");
const express = require("express");
const app = express();
const bp = require("body-parser");
const cors = require("cors");
const { spawn } = require("child_process");
const { PythonShell } = require("python-shell");
const fs = require("fs");

const allowedOrigins = ["http://localhost:3000", "http://192.168.1.92:3000"];
const historicPath = "../interface-web/src/historicData.json";

app.use(
  cors({
    origin: function (origin, callback) {
      if (allowedOrigins.indexOf(origin) === -1) {
        var msg =
          "The CORS policy for this site does not " +
          "allow access from the specified Origin.";
        return callback(new Error(msg), false);
      }
      return callback(null, true);
    },
  })
);

app.use(bp.json());
app.use(bp.urlencoded({ extended: true }));

app.post("/run", (req, res) => {
  if (req.body === undefined) {
    res.status(404).send("Body not defined");
  } else {
    var param1 = req.body.TestName;
    var param2 = req.body.TestParameter;
    var param3 = req.body.TestValue;
    var testResult;

    try {
      runPythonScript([param1.replace(/\s/g, ""), param3]);
      testResult = "success";
      res.status(200).json();
    } catch (e) {
      testResult = "failed";
      res.status(400).send("An error occured : ", e);
    }
    var json;
    fs.readFile(historicPath, function (err, data) {
      json = JSON.parse(data);
      var objectId = Object.keys(json).length + 1;
      const date = new Date();
      json["Test " + objectId] = {
        id: objectId,
        test_name: param1,
        date:
          date.getDate() +
          "/" +
          (date.getMonth() + 1) +
          "/" +
          date.getFullYear(),
        parametre: param2 + " = " + param3,
        result: testResult,
      };
      fs.writeFile(historicPath, JSON.stringify(json), function (err) {
        if (err) throw err;
        console.log('The "data to append" was appended to file!');
      });
    });
  }
});

app.post("/config", (req, res) => {
  if (req.body === undefined) {
    res.status(404).send("Body not defined");
  } else {
    if (req.body.Config === "CRK") {
      var conf = "CONFIGCRK";
      var NumOfCrkTeeth = req.body.NumOfCrkTeeth;
      var NumOfMissingTeeth = req.body.NumOfMissingTeeth;
      var NumOfGaps = req.body.NumOfGaps;
      var DistanceTDC0toGap = req.body.DistanceTDC0toGap;
      var FirstSegErAngle = req.body.FirstSegErAngle;
      var NumberCylinder = req.body.NumberCylinder;
      var SensorType = req.body.SensorType;
      try {
        runPythonScript([
          conf,
          NumOfCrkTeeth,
          NumOfMissingTeeth,
          NumOfGaps,
          DistanceTDC0toGap,
          FirstSegErAngle,
          NumberCylinder,
          SensorType,
        ]);
        res.status(200).json();
      } catch (e) {
        res.status(404).send(e);
        console.log(e);
      }
    } else {
      var conf = "CONFIGCAM";
      var NumCamEdge = req.body.NumCamEdge;
      var NumOfCam = req.body.NumOfCam;
      var ActiveEdges = req.body.ActiveEdges;
      var SensorType = req.body.SensorType;
      var FilterTime = req.body.FilterTime;
      var CamEdges = req.body.CamEdges;
      try {
        runPythonScript([
          conf,
          NumCamEdge,
          NumOfCam,
          ActiveEdges,
          SensorType,
          FilterTime,
          CamEdges,
        ]);
        res.status(200).json();
      } catch (e) {
        res.status(404).send(e);
        console.log(e);
      }
      res.status(200).json();
    }
  }
});

app.listen(8080, () => {
  console.log("Serveur à l'écoute");
});

function runPythonScript(params) {
  PythonShell.run(
    "../USART_Script.py",
    { args: params },
    function (err, results) {
      if (err) throw err;
      // results is an array consisting of messages collected during execution
      console.log("results: %j", results);
    }
  );
}

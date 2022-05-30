const express = require("express");
const app = express();
const bp = require("body-parser");
const cors = require("cors");
const { PythonShell } = require("python-shell");
const fs = require("fs");
const IP = require("../interface-web/src/RaspiProp.json")["IP_ADDRESS"];

const allowedOrigins = ["http://" + IP + ":3000"];

//Has to be absolute path!
const historicPath = "./interface-web/src/historicData.json";
const pythonScripPath = "./USART_Script.py";

//Configuring CORS
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

//Call for running test
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
      testResult = "test ran successfully";
      res.status(200).json();
    } catch (e) {
      testResult = "failed to run test";
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
        parametreType: param2,
        parametreValue: param3,
        result: testResult,
      };
      fs.writeFile(historicPath, JSON.stringify(json), function (err) {
        if (err) throw err;
        console.log('The "data to append" was appended to file!');
      });
    });
  }
});

//Call for configuring CAM or CRK signals
app.post("/config", (req, res) => {
  if (req.body === undefined) {
    res.status(404).send("Body not defined");
  } else {
    var params;
    if (req.body.Config === "CRK") {
      var conf = "CONFIGCRK";
      var NumOfCrkTeeth = req.body.NumOfCrkTeeth;
      var NumOfMissingTeeth = req.body.NumOfMissingTeeth;
      var NumOfGaps = req.body.NumOfGaps;
      var DistanceTDC0toGap = req.body.DistanceTDC0toGap;
      var FirstSegErAngle = req.body.FirstSegErAngle;
      var NumberCylinder = req.body.NumberCylinder;
      var SensorType = req.body.SensorType;
      params = [
        conf,
        NumOfCrkTeeth,
        NumOfMissingTeeth,
        NumOfGaps,
        DistanceTDC0toGap,
        FirstSegErAngle,
        NumberCylinder,
        SensorType,
      ];
    } else if (req.body.Config === "CAM") {
      var conf = "CONFIGCAM";
      var NumCamEdge = req.body.NumCamEdge;
      var NumOfCam = req.body.NumOfCam;
      var ActiveEdges = req.body.ActiveEdges;
      var SensorType = req.body.SensorType;
      var FilterTime = req.body.FilterTime;
      var CamEdges = req.body.CamEdges;
      params = [
        conf,
        NumCamEdge,
        NumOfCam,
        ActiveEdges,
        SensorType,
        FilterTime,
        CamEdges,
      ];
    } else if (req.body.Config === "RESETCRK") {
      var conf = "RESETCRK";
      params = [conf];
    } else if (req.body.Config === "RESETCAM") {
      var conf = "RESETCAM";
      params = [conf];
    }
    try {
      runPythonScript(params);
      res.status(200).json();
    } catch (e) {
      res.status(400).send(e);
      console.log(e);
    }
  }
});

//Recording signals call
app.put("/record", (req, res) => {
  try {
    runPythonScript(["RECORD"]);
    res.status(200).json();
  } catch (e) {
    res.status(400).send(e);
    console.log(e);
  }
});

//Call for fetching tests historic log
app.get("/getlog", (req, res) => {
  try {
    fs.readFile(historicPath, function (err, data) {
      historicJson = JSON.parse(data);
      res.status(200).json(historicJson);
    });
  } catch (e) {
    res.status(404).send(e);
  }
});

//Call for deleting the log completely
app.delete("/deleteLog", (req, res) => {
  fs.writeFile(historicPath, JSON.stringify({}), function (err) {
    if (err) throw err;
    console.log("Deleted log successfully");
  });
});

app.listen(8080, () => {
  console.log("Serveur à l'écoute");
});

function runPythonScript(params) {
  PythonShell.run(pythonScripPath, { args: params }, function (err, results) {
    if (err) throw err;
    // results is an array consisting of messages collected during execution
    console.log("results: %j", results);
  });
}

const usb = require("usb");
const express = require("express");
const app = express();
const shell = require("shelljs");
const bp = require("body-parser");
const cors = require("cors");
const fs = require("fs");

var allowedOrigins = ["http://localhost:3000", "http://192.168.1.92:3000"];

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
    shell.exec("../script_exemple.sh " + param1 + " " + param2 + " " + param3);
    res.status(200).json();
  }
});

app.listen(8080, () => {
  console.log("Serveur à l'écoute");
});

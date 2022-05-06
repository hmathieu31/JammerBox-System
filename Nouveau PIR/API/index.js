const express = require("express");
const app = express();
const exemple = require("./exemple.json");
const shell = require("shelljs");
const bp = require("body-parser");

const cors = require("cors");
app.use(
  cors({
    origin: "http://localhost:3000",
  })
);

app.use(bp.json());
app.use(bp.urlencoded({ extended: true }));

app.post("/exemple", (req, res) => {
  var param1 = req.body.TestName;
  var param2 = req.body.TestParameter;
  var param3 = req.body.TestValue;
  shell.exec("../script_exemple.sh " + param1 + " " + param2 + " " + param3);
  res.status(200).json(exemple);
});

app.listen(8080, () => {
  console.log("Serveur à l'écoute");
});

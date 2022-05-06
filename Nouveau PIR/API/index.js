const express = require("express");
const app = express();
const exemple = require("./exemple.json");
const shell = require("shelljs");

const cors = require("cors");
app.use(
  cors({
    origin: "http://localhost:3000",
  })
);

app.get("/exemple", (req, res) => {
  shell.exec("../script_exemple.sh");
  res.status(200).json(exemple);
});

app.listen(8080, () => {
  console.log("Serveur à l'écoute");
});

#!/bin/bash

WEB_FOLDER="./interface-web"
API_FOLDER="./API"

#Running the API
node $API_FOLDER/index.js &
npm --prefix $WEB_FOLDER start 
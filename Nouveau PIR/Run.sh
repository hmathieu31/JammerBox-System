#!/bin/bash

WEB_FOLDER="../MainSource/interface-web"
API_FOLDER="../MainSource/API"

#Running the API
node $API_FOLDER/index.js &
npm --prefix $WEB_FOLDER start 
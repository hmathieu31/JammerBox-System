#!/bin/bash

PIR_FOLDER=./Nouveau\ PIR
WEB_FOLDER=PIR_FOLDER/interface-web
API_FOLDER=PIR_FOLDER/API

#Running the API
node API_FOLDER/index.js &
npm --prefix WEB_FOLDER start 
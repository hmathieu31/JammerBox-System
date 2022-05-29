#!/bin/bash

PIR_FOLDER="./Nouveau\ PIR"
WEB_FOLDER="${PIR_FOLDER}/interface-web"
API_FOLDER="${PIR_FOLDER}/API"

echo $WEB_FOLDER

npm --prefix "$WEB_FOLDER" install "$WEB_FOLDER"
npm --prefix "$API_FOLDER" install "$API_FOLDER"
pip install pyserial 
#!/bin/bash

if [ $# != 1 ]
then
    echo "Please type in the device's IP address as the argument"
    exit 1
fi

WEB_FOLDER="./interface-web"
API_FOLDER="./API"

echo "{\"IP_ADDRESS\":\"$1\"}" > $WEB_FOLDER/src/RaspiProp.json

sudo su
curl -fsSL https://deb.nodesource.com/setup_17.x | bash -
sudo apt install nodejs

node --version
npm --version

npm --prefix "$WEB_FOLDER" install "$WEB_FOLDER"
npm --prefix "$API_FOLDER" install "$API_FOLDER"
pip install pyserial 

echo "Do you want to install Powershell? It will be used for testing purposes (type in yes or no) "
read x
if [ $x = "yes" ]
then
    sudo apt-get update
    sudo apt-get install '^libssl1.0.[0-9]$' libunwind8 -y
    wget https://github.com/PowerShell/PowerShell/releases/download/v7.2.4/powershell-7.2.4-linux-arm32.tar.gz
    mkdir ~/powershell
    tar -xvf ./powershell-7.2.4-linux-arm32.tar.gz -C ~/powershell
    echo "Powershell installed"
fi
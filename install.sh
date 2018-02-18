#!/bin/bash

# DO NOT MODIFY

bold=`tput bold`
normal=`tput sgr0`

# Download dependencies
printf "\n${bold}==> Downloading dependencies... ${normal} \n"
npm install
# Install dependencies
printf "\n${bold}==> Installing dependencies... ${normal} \n"
# Copy Eyeslib
mkdir -p ~/Arduino/libraries/Eyeslib
cp -R node_modules/arduino-eyelib/* ~/Arduino/libraries/Eyeslib 
# Copy Drivelib
mkdir -p ~/Arduino/libraries/Drivelib
cp -R node_modules/arduino-drivelib/* ~/Arduino/libraries/Drivelib 
# Copy IRremote
mkdir -p ~/Arduino/libraries/IRremote
cp -R node_modules/arduino-irremote/* ~/Arduino/libraries/IRremote 
# Remove temp files
printf "\n${bold}==> Removing temp files. ${normal} \n"
rm -r node_modules
# End install
printf "\n${bold}==> Dependencies installed. ${normal} \n"
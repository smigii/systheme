IN PROGRESS

# Systheme
A convenient way to manage and create custom themes for your unix environment.

## Overview
Systheme works by reading in themes that you specify in JSON files and assembling and overwriting your programs configuration files according to this JSON recipe.\
Your configuration files will be broken down into modular parts, so that you can mix and match different pieces of your config files for different themes.\

## Installation
1. (something something install/build) systheme
2. Run the `install.sh` script

You will now have the `~/.config/systheme` directory, which contains `data` and `themes` subdirectories, as well as the `refresh.sh` script.

## The Data Directory
This is the directory that will hold all your config file parts. It has the following structure...

  * data
    * PROGRAM 1         <- First layer
      * CONFIG 1        <- Second layer
        * COMPONENT 1   <- Third layer
        * COMPONENT 2   <- Third layer
        * COMPONENT n   <- Third layer

The first two layers should only contain directories and only exist for organization.

The third layer is where you will put the actual parts of your config files. 
For example, if the config file we want to build is .bashrc, we might want to have the following components...
* Base - For things like aliases, exports or anything that you want to remain constant for all themes.
* Prompt - This would just contain your PS1 export.

## The Themes Directory

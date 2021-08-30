IN PROGRESS

# Systheme
A convenient way to manage and create custom themes for your unix environment.

## Overview
Systheme works by adding in symbols to your config files, then referencing those symbols in JSON 
theme files that you create. Essentially a glorified search/replace that helps you manage your
pretty terminal colors (or whatever you can fit in your config files).

## Installation
1. (something something install/build) systheme
2. Run the `install.sh` script

You will now have the `~/.config/systheme` directory, which contains `data` and `themes` subdirectories, as well as the `refresh.sh` script.

## The Data Directory
This is the directory that will hold the config files for all your programs.
```
* data/
  * PROGRAM_1/
    * template.extension
    * themes/
      * config_1.xyz
      * config_2.abc
      * config_n.jkl
```
The `template.*` file will hold the config file, and will contain the symbols that are 
to be managed by systheme. For example, you may put in your vim template...
```
colorscheme: [%colorscheme%]
```
so that you can synchronize your vim colorschemes with the rest of your system.

## The Systhemes Directory
This is where full system themes are stored. Again, systhem themes are written in JSON
format and define what themes to use for each of your configs.

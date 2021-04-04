#!/bin/bash

usr=$(logname)

cp systheme-completion.bash /home/$usr/Dotfiles/scripts-n-shit/systheme/systheme-completion.bash

cd cmake-build-debug

chown :systheme systheme

cp systheme /bin/systheme

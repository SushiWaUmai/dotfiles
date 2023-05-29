#!/bin/bash

set -xe

# check if the user is root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

make -C ./suckless/chadwm clean install
make -C ./suckless/slock clean install
make -C ./suckless/slstatus clean install

# get the user name
USERNAME=$(logname)
cp -R ./.dwm /home/$USERNAME/
cp -R ./.config /home/$USERNAME/
cp -R ./.wallpaper /home/$USERNAME/
cp ./.xinitrc /home/$USERNAME/
cp ./.zshrc /home/$USERNAME/
cp ./.tmux.conf /home/$USERNAME/

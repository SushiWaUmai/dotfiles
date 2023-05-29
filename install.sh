#!/bin/bash

# check if the user is root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

cd suckless/dmenu
make clean install
cd ../..

cd suckless/dwm
make clean install
cd ../..

cd suckless/slock
make clean install
cd ../..

cd suckless/slstatus
make clean install
cd ../..

# get the user name
USERNAME=$(logname)
cp -R ./.dwm /home/$USERNAME/
cp -R ./.config /home/$USERNAME/
cp -R ./.wallpaper /home/$USERNAME/
cp ./.xinitrc /home/$USERNAME/
cp ./.zshrc /home/$USERNAME/
cp ./.tmux.conf /home/$USERNAME/

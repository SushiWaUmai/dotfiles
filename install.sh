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

cd suckless/st
make clean install
cd ../..

cd suckless/surf
make clean install
cd ../..

cd suckless/tabbed
make clean install
cd ../..

# get the user name
USERNAME=$(logname)
ln -s ./.dwm /home/$USERNAME/
cp -R ./.config /home/$USERNAME/
cp -R ./.surf /home/$USERNAME/
cp -R ./.wallpaper /home/$USERNAME/
cp ./.xinitrc /home/$USERNAME/
cp ./.zshrc /home/$USERNAME/
cp ./.tmux.conf /home/$USERNAME/

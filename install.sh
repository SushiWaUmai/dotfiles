#!/bin/bash

set -xe

# check if the user is root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

echo "Installing Dependencies..."
pacman -Sy
pacman -S base base-devel xorg imlib2 --noconfirm

echo "Installing Packages..."
make -C ./suckless/chadwm clean install
make -C ./suckless/slock clean install
make -C ./suckless/slstatus clean install

echo "Copying Configurations..."
cp -R ./.dwm /home/$USER/
cp -R ./.config /home/$USER/
cp -R ./.wallpaper /home/$USER/
cp ./.xinitrc /home/$USER/
cp ./.zshrc /home/$USER/
cp ./.tmux.conf /home/$USER/

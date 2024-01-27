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
pacman -S git curl --noconfirm


echo "Setting up zsh..."
pacman -S zsh --noconfirm
curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh
git clone https://github.com/jandamm/zgenom.git "/home/$USER/.zgenom"


echo "Cloning dotfiles..."
git clone https://github.com/SushiWaUmai/dotfiles.git --recursive
cd dotfiles


echo "Installing Tools..."
pacman -S thunar flameshot xwallpaper picom autorandr xclip alacritty rofi numlockx --noconfirm


echo "Compiling and Installing dwm..."
make -C ./chadwm clean install


echo "Copying Configurations..."
cp -R ./.dwm /home/$USER/
cp -R ./.config /home/$USER/
cp -R ./.wallpaper /home/$USER/
cp -R ./.librewolf/home/$USER/
cp ./.xinitrc /home/$USER/
cp ./.zshrc /home/$USER/

#!/bin/bash
set -xe

# check if the user is root
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root"
  exit
fi

echo "Updating package lists..."
apt update

echo "Installing Dependencies..."
apt install -y build-essential xorg libimlib2-dev git curl

echo "Setting up zsh..."
apt install -y zsh tmux
curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh | sh
git clone https://github.com/jandamm/zgenom.git "${HOME}/.zgenom"

echo "Cloning dotfiles..."
git clone https://github.com/SushiWaUmai/dotfiles.git --recursive
cd dotfiles

echo "Installing Tools..."
apt install -y pcmanfm scrot xwallpaper picom autorandr xclip alacritty neovim rofi lxsession-gtk3 numlockx bat exa

echo "Compiling and Installing Suckless Tools..."
make -C ./suckless/chadwm clean install
make -C ./suckless/slstatus clean install

echo "Copying Configurations..."
cp -R ./.dwm /home/$USER/
cp -R ./.config /home/$USER/
cp -R ./.wallpaper /home/$USER/
cp -R ./.librewolf /home/$USER/
cp ./.xinitrc /home/$USER/
cp ./.zshrc /home/$USER/
cp ./.tmux.conf /home/$USER/

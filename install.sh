#!/bin/bash

set -xe

# Check if the user is root
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root"
  exit
fi

# Function to install packages
install_packages() {
    local packages=("$@")
    if command -v pacman >/dev/null; then
        pacman -Sy --noconfirm "${packages[@]/#/-S }"
    elif command -v apt-get >/dev/null; then
        apt-get update
        apt-get install -y "${packages[@]}"
    else
        echo "Unsupported package manager. Exiting."
        exit 1
    fi
}

# Install base dependencies
echo "Installing Dependencies..."
if command -v pacman >/dev/null; then
    install_packages base base-devel xorg imlib2 git curl
elif command -v apt-get >/dev/null; then
    install_packages build-essential xorg libimlib2-dev git curl
fi

echo "Setting up zsh..."
install_packages zsh
# Install Oh My Zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
# Clone zgenom for zsh configuration
git clone https://github.com/jandamm/zgenom.git "/home/$USER/.zgenom"

echo "Cloning dotfiles..."
git clone https://github.com/SushiWaUmai/dotfiles.git --recursive
cd dotfiles || exit

echo "Installing Tools..."
install_packages thunar flameshot xwallpaper picom autorandr xclip alacritty rofi numlockx

echo "Compiling and Installing dwm..."
# Ensure build tools are present (make, gcc, etc.)
if command -v apt-get >/dev/null; then
    install_packages build-essential libx11-dev libxft-dev libxinerama-dev
elif command -v pacman >/dev/null; then
    install_packages base-devel libx11 libxft libxinerama
fi
make -C ./chadwm clean install

echo "Copying Configurations..."
cp -R ./.dwm /home/$USER/
cp -R ./.config /home/$USER/
cp -R ./.wallpaper /home/$USER/
cp -R ./.librewolf /home/$USER/
cp ./.xinitrc /home/$USER/
cp ./.zshrc /home/$USER/

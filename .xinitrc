# # see https://unix.stackexchange.com/a/295652/332452
# source /etc/X11/xinit/xinitrc.d/50-systemd-user.sh
#
# # see https://wiki.archlinux.org/title/GNOME/Keyring#xinitrc
# eval $(/usr/bin/gnome-keyring-daemon --start)
# export SSH_AUTH_SOCK
#
# # see https://github.com/NixOS/nixpkgs/issues/14966#issuecomment-520083836
# mkdir -p "$HOME"/.local/share/keyrings
#
# # Use appropriate xrandr config
# xrandr --setprovideroutputsource modesetting NVIDIA-0
# xrandr --auto

# dwm status bar
while $(xsetroot -name "$(date +'%a. %d %b. %Y - %H:%M:%S')" 1>&- 2>&-); do
  sleep 1
done &

~/.fehbg &

picom -b

exec dwm


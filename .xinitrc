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

# # For mozc
# fcitx5 &
#
# # fcitx
# export XMODIFIERS=@im=fcitx
# export QT_IM_MODULE=fcitx
# export GTK_IM_MODULE=fcitx

export WINIT_X11_SCALE_FACTOR=1
export _JAVA_AWT_WM_NONREPARENTING=1

# slstatus
exec slstatus &

# auto mount
udiskie &

# emacs daemon
emacs --daemon &

# dwm suckless (dynamic window manager)
exec dwm


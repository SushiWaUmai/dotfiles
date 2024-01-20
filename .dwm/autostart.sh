numlockx on
lxsession &
exec slstatus &

xset s on
xset s 600
xss-lock -- dm-tool lock &

xwallpaper --zoom "${HOME}/.wallpaper/wallpaper.png"

picom -b

autorandr main

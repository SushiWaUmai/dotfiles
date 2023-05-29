lxsession &
exec slstatus &
xautolock -time 10 -locker slock &

xwallpaper --focus "${HOME}/.wallpaper/wallpaper.png"

picom -b

autorandr main

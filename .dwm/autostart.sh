exec slstatus &
xautolock -time 10 -locker slock &

xwallpaper --center "${HOME}/.wallpaper/wallpaper.png"

picom -b

autorandr main

exec slstatus &
xautolock -time 10 -locker slock &

feh --no-fehbg --bg-scale "${HOME}/.wallpaper/wallpaper.png" "${HOME}/.wallpaper/wallpaper.png" &

picom -b

autorandr main

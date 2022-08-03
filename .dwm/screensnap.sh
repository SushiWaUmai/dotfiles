#!/bin/sh

d="${HOME}/img/screenshot-$(date +%Y-%m-%d-%H_%M-%S).png"
sel=$(slop -f "-i %i -g %g")

shotgun $sel $d
xclip -t 'image/png' -sel c < $d

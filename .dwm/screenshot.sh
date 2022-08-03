#!/bin/sh

d="${HOME}/img/screenshot-$(date +%Y-%m-%d-%H_%M-%S).png"


shotgun -s $d
xclip -t 'image/png' -sel c < $d

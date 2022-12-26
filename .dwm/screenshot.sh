#!/bin/sh

d="${HOME}/pics/screenshot-$(date +%Y-%m-%d-%H_%M-%S).png"


shotgun -s $d
xclip -t 'image/png' -sel c < $d

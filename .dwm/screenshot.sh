#!/bin/sh -e

sel=$(slop -f "-i %i -g %g")
shotgun $sel "$1"


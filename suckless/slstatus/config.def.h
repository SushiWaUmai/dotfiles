/* See LICENSE file for copyright and license details. */
#include "slstatus.h"
#include "themes/dracula.h"
#include <stdio.h>
#include <stdlib.h>

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */

const char battery_icons[10][5] = {
    "󰁺",
    "󰁻",
    "󰁼",
    "󰁽",
    "󰁾",
    "󰁿",
    "󰂀",
    "󰂁",
    "󰂂",
    "󰁹",
};

const char charging_icons[10][5] = {
    "󰢜",
    "󰂆",
    "󰂇",
    "󰂈",
    "󰢝",
    "󰂉",
    "󰢞",
    "󰂊",
    "󰂋",
    "󰂅",
};
const size_t battery_icon_length = 10;

const char no_wifi_icon[] = "󰖪";
const char wifi_icon[]    = "󰖩";

const char volume_icons[3][5] = {
    "󰕿",
    "󰖀",
    "󰕾",
};
const size_t volume_icon_length = 3;

const char brightness_icons[3][5] = {
    "󰃞",
    "󰃟",
    "󰃠",
};
const size_t brightness_icon_length = 3;

const char volume_muted_icon[] = "󰸈";
const char keyboard_icon[]     = "󰥻";
const char clock_icon[]        = "󰥔";

static void
statusstr(size_t *len, char *status) {
  int bat_perc_val = battery_perc_avg();
  int state        = battery_state_any();

  int brightness_perc = brightnessctl_perc();
  int vol_perc_val    = vol_perc_amixer();

  int vol_muted = vol_muted_amixer();

  const char *ssid      = wifi_essid("wlp2s0");
  const char *ssid_perc = wifi_perc("wlp2s0");

  const char *bat_state_str;
  int         battery_icons_idx = bat_perc_val / (100 / battery_icon_length);
  battery_icons_idx             = battery_icons_idx > (battery_icon_length - 1) ? (battery_icon_length - 1) : battery_icons_idx;
  if (state) {
    bat_state_str = charging_icons[battery_icons_idx];
  } else {
    bat_state_str = battery_icons[battery_icons_idx];
  }

  int volume_icons_idx = vol_perc_val / (100 / volume_icon_length);
  volume_icons_idx     = volume_icons_idx > (volume_icon_length - 1) ? (volume_icon_length - 1) : volume_icons_idx;
  const char *vol_state_str;
  if (vol_muted) {
    vol_state_str = volume_muted_icon;
  } else {
    vol_state_str = volume_icons[volume_icons_idx];
  }

  int brightness_icons_idx         = brightness_perc / (100 / brightness_icon_length);
  brightness_icons_idx             = brightness_icons_idx > (brightness_icon_length - 1) ? (brightness_icon_length - 1) : brightness_icons_idx;
  const char *brightness_state_str = brightness_icons[brightness_icons_idx];

  *len = 0;
  *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^ %s %3d%%", green, bat_state_str, bat_perc_val);

  *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^%s %3d%% ", red, brightness_state_str, brightness_perc);
  *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^%s %3d%% ", orange, vol_state_str, vol_perc_val);

  if (ssid) {
    *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^^b%s^ %s ^c%s^^b%s^ %3s%% ", black, pink, wifi_icon, pink, black, ssid_perc);
  } else {
    *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^^b%s^ %s", black, red, no_wifi_icon);
  }

  *len += snprintf(status + *len, MAXLEN - *len, " ^c%s^^b%s^ %s ^b%s^ %s ", black, blue, clock_icon, darkblue, datetime("%a. %d %b. %Y - %H:%M:%S"));
}

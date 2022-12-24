/* See LICENSE file for copyright and license details. */
#include "slstatus.h"
#include <stdio.h>
#include <string.h>
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

const char battery_icons[5][4] = {
  "",
  "",
  "",
  "",
  ""
};

const char charging_icons[5][4] = {
  "",
  "",
  "",
  "",
  ""
};

const char no_wifi_icon[] = "睊";
const char wifi_icon[] = "直";

const char volume_icons[3][4] = {
  "",
  "",
  "",
};

const char brightness_icons[3][4] = {
  "",
  "",
  "",
};

const char volume_muted_icon[] = "婢";
const char keyboard_icon[] = "";
const char kernel_icon[] = "";

void to_upper(const char *str, char *to) {
    for (int i = 0; str[i] != '\0'; i++) {
        to[i] = str[i] - 32;
    }
}

static void
statusstr(size_t * len, char * status)
{
  int bat_perc_val = battery_perc_avg();
  int state = battery_state_any();

  int brightness_perc = brightnessctl_perc();
  int vol_perc_val = vol_perc_amixer();

  const char *nocapkeyboard = keymap();
  static char keyboard[32];
  memset(keyboard, 0, 32);
  to_upper(nocapkeyboard, keyboard);

  const char *ssid = wifi_essid("wlan0");
  const char *ssid_perc = wifi_perc("wlan0");

  const char* bat_state_str;
  int battery_icons_idx = bat_perc_val / (100 / 5);
  battery_icons_idx = battery_icons_idx > 4 ? 4 : battery_icons_idx;
  if (state) {
    bat_state_str = charging_icons[battery_icons_idx];
  } else {
    bat_state_str = battery_icons[battery_icons_idx];
  }

  int volume_icons_idx = vol_perc_val / (100 / 3);
  volume_icons_idx = volume_icons_idx > 2 ? 2 : volume_icons_idx;
  const char *vol_state_str = volume_icons[volume_icons_idx];

  int brightness_icons_idx = brightness_perc / (100 / 3);
  brightness_icons_idx = brightness_icons_idx > 2 ? 2 : brightness_icons_idx;
  const char *brightness_state_str = brightness_icons[brightness_icons_idx];

  *len = 0;
	*len += snprintf(status + *len, MAXLEN - *len,    " | ");
  *len += snprintf(status + *len, MAXLEN - *len,    "%s  %3d%% | "           , bat_state_str, bat_perc_val);
  *len += snprintf(status + *len, MAXLEN - *len,    "%s  %s | "              , keyboard_icon, keyboard); 

  *len += snprintf(status + *len, MAXLEN - *len,    "%s %3d%% | "            , brightness_state_str, brightness_perc);
  *len += snprintf(status + *len, MAXLEN - *len,    "%s %3d%% | "            , vol_state_str, vol_perc_val);

  if (ssid) {
    *len += snprintf(status + *len, MAXLEN - *len,  "%s %3s%% | "           , wifi_icon, ssid_perc);
  }
  else {
    *len += snprintf(status + *len, MAXLEN - *len,  "%s | "                 , no_wifi_icon);
  }

	*len += snprintf(status + *len, MAXLEN - *len,    "%s | "                 , datetime("%a. %d %b. %Y - %H:%M:%S"));
  *len += snprintf(status + *len, MAXLEN - *len,    " %s "                  , kernel_icon);
}


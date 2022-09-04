/* See LICENSE file for copyright and license details. */

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

char battery_icons[5][4] = {
  "",
  "",
  "",
  "",
  ""
};

char charging_icons[5][4] = {
  "",
  "",
  "",
  "",
  ""
};

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 32;
    }
}

static void
statusstr(size_t * len, char * status)
{
  *len = 0;
	*len += snprintf(status + *len, MAXLEN - *len,    " | ");

  int percent = battery_perc_avg();
  int state = battery_state_any();
  char* state_str;

  int battery_icons_idx = percent / (100 / 5) - 1;
  if (state) {
    state_str = charging_icons[battery_icons_idx];
  } else {
    state_str = battery_icons[battery_icons_idx];
  }

  *len += snprintf(status + *len, MAXLEN - *len,    "%s  %3d% | "            , state_str, percent);

  char *keyboard = keymap();
  to_upper(keyboard);

  *len += snprintf(status + *len, MAXLEN - *len,    "  %s | "               , keyboard); 

  char *ssid = wifi_essid("wlan0");
  char *ssid_perc = wifi_perc("wlan0");

  if (ssid) {
    *len += snprintf(status + *len, MAXLEN - *len,  "  %s %3s%% | "         , ssid, ssid_perc);
  }
  else {
    *len += snprintf(status + *len, MAXLEN - *len,  "  NOT FOUND | ");
  }

	*len += snprintf(status + *len, MAXLEN - *len,    "%s | "                 , datetime("%a. %d %b. %Y - %H:%M:%S"));
  *len += snprintf(status + *len, MAXLEN - *len,    "  ");
}


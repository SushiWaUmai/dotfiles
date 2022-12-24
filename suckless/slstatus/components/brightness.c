#include "../slstatus.h"

#if defined(__linux__)
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>

  int
  brightnessctl_perc() {
    const char *current_str = run_command("/bin/sh -c \"brightnessctl g\"");
    int current = atoi(current_str);
    const char *max_str = run_command("/bin/sh -c \"brightnessctl m\"");
    int max = atoi(max_str);

    int perc = (int)(((float)current / max) * 100 + 0.5);

    return perc;
  }
#endif

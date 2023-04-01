#include "../dwm.h"

static const char normfgcolor[] = "#ECEFF4";
static const char normbgcolor[] = "#2E3440";
static const char normbordercolor[] = "#4C566A";

static const char bar_border[] = "#B48EAD";
static const char title_color[] = "#A3BE8C";

static const char selfgcolor[] = "#D08770";
static const char selbgcolor[] = "#4C566A";
static const char selbordercolor[] = "#8FBCBB";

static const char urgfgcolor[] = "#8FBCBB";
static const char urgbgcolor[] = "#88C0D0";
static const char urgbordercolor[] = "#88C0D0";

/* static const char status_fg[] = "#B48EAD"; */

static const char *colors[][3]      = {
    /*                  	fg            		bg             border                         */
    [SchemeNorm]    			= { normfgcolor,  normbgcolor,   normbordercolor }, // unfocused wins
    [SchemeSel]     			= { selfgcolor,   selbgcolor,    selbordercolor },  // the focused win
    [SchemeUrg]     			= { urgfgcolor,   urgbgcolor,    urgbordercolor },
    [SchemeTitleBarNorm]  = { title_color,  normbgcolor,   normbordercolor },
    [SchemeTitleBarSel]   = { title_color,  selbgcolor,    selbordercolor },
 /*   [SchemeStatus]  = { status_fg,   norm_bg,   sel_fg }, // Statusbar right {text,background,not used but cannot be empty} */
};

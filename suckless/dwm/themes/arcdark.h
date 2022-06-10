#include "../dwm.h"

static const char norm_bg[]       = "#2B2E37";
static const char norm_fg[]       = "#dddddd";
static const char norm_border[]       = "#2B2E37";

static const char sel_fg[]       = "#4084D6";
static const char sel_bg[]        = "#252730";
static const char sel_border[]        = "#252730";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};

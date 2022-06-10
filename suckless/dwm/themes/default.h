#include "../dwm.h"

static const char norm_bg[]       = "#222222";
static const char norm_fg[]       = "#bbbbbb";
static const char norm_border[]       = "#444444";

static const char sel_fg[]       = "#eeeeee";
static const char sel_bg[]        = "#005577";
static const char sel_border[]        = "#005577";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};

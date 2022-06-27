/* user and group to drop privileges to */
static const char *user  = "root";
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#2E3440",   /* after initialization */
	[INPUT] =  "#88C0D0",         /* during input */
	[FAILED] = "#D08770",   /* wrong password */
	[CAPS] =   "#B48EAD",   /* CapsLock on */
};
 
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "init",         STRING,  &colorname[INIT] },
		{ "input",        STRING,  &colorname[INPUT] },
		{ "failed",       STRING,  &colorname[FAILED] },
		{ "caps",         STRING,  &colorname[CAPS] },
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

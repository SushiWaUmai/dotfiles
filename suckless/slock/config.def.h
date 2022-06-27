/* user and group to drop privileges to */
static const char *user  = "root";
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#2E3440",   /* after initialization */
	[INPUT] =  "#88C0D0",         /* during input */
	[FAILED] = "#D08770",   /* wrong password */
	[CAPS] =   "#B48EAD",   /* CapsLock on */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

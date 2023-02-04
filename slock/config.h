/* user and group to drop privileges to */
static const char *user  = "rlggyp";
static const char *group = "users";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#1a1b26",   /* after initialization */
	[INPUT] =  "#1a1b26",   /* during input */
	[FAILED] = "#565f89",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

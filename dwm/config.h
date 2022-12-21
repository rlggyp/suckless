/* See LICENSE file for copyright and license details. */
/* appearance */
static const char my_terminal[]       = "kitty";       /* terminal what i use */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int horizpadbar        = 0;//gappx/2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 2;//gappx/2;        /* vertical padding for statusbar */
static const int vertpad            = 0;//gappx;       /* vertical padding of bar */
static const int sidepad            = 0;//gappx;       /* horizontal padding of bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"JetBrains Mono:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Symbola:weight=regular:size=10:antialias=true:autohint=true" 
                                      ,"Noto Sans CJK JP:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK KR:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK SC:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK TC:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"JoyPixels:weight=regular:size=10:antialias=true:autohint=true"};
static const char dmenufont[]       =  "JetBrains Mono:weight=regular:size=10:antialias=true:autohint=true";
static const char bg[]              = "#1a1b26"; // dark
static const char fg[]              = "#c0caf5"; // light
static const char col[]             = "#2ac3de"; // blue
static const char *colors[][3]      = {
	/*                    fg, bg, border   */
	[SchemeNorm]      = { fg, bg, bg },
	[SchemeSel]       = { bg, fg, col },
	[SchemeStatus]    = { fg, bg, bg }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { bg, col, bg }, // Tagbar left selected {text,background,not used but cannot be empty}
        [SchemeTagsNorm]  = { fg, bg, bg }, // Tagbar left unselected {text,background,not used but cannot be empty}
        [SchemeInfoSel]   = { fg, bg, bg }, // infobar middle  selected {text,background,not used but cannot be empty}
        [SchemeInfoNorm]  = { fg, bg, bg }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	instance    		  title       	      tags mask       isfloating   	monitor */
	{ NULL,         NULL,       		  "Volume Control",   0,              1,           	-1 },
	{ "xdman-Main", NULL,       		  NULL,               0,              1,           	-1 },
	{ NULL,		"terminal",		  NULL,	       	      SPTAG(0),	      1,		-1 },
	{ NULL,		"file-manager",	    	  NULL,	       	      SPTAG(1),	      1,		-1 },
	{ NULL,		"network-manager",	  NULL,	       	      SPTAG(2),	      1,		-1 },
	{ NULL,		"simplescreenrecorder",	  NULL,	       	      SPTAG(3),	      1,		-1 },
	{ NULL,		"cmus",	                  NULL,	       	      SPTAG(4),	      1,		-1 },
	{ NULL,		"calculator",	          NULL,	       	      SPTAG(5),	      1,		-1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-p", "Run: ", "-m", dmenumon, "-fn", dmenufont, "-nb", bg, "-nf", fg, "-sb", col, "-sf", bg, NULL};
static const char *termcmd[]  = {my_terminal, NULL};
static const char *browserfcmd[] = {"firefox", NULL};
static const char *browserccmd[] = {"firefox", "--private-window", NULL};
//static const char *browserfcmd[] = {"google-chrome", NULL};
//static const char *browserccmd[] = {"google-chrome", "--incognito", NULL};
static const char *pavucmd[] = {"pavucontrol", NULL};
static const char *libreofficecmd[] = {"libreoffice", NULL};
static const char *brightdocmd[] = {"brightnessctl", "set", "2%-", NULL};
static const char *brightupcmd[] = {"brightnessctl", "set", "2%+", NULL};
static const char *voldocmd[] = {"amixer", "-D", "pulse", "sset", "Master", "4%-", NULL};
static const char *volupcmd[] = {"amixer", "-D", "pulse", "sset", "Master", "4%+", NULL};
static const char *voltogcmd[] = {"amixer", "-D", "pulse", "sset", "Master", "toggle", NULL};
static const char *scrottopiccmd[] = {"scrottopict", NULL};
static const char *scrotcpcmd[] = {"scrotcp", NULL};
static const char *scrottopicselcmd[] = {"scrottopictsel", NULL};
static const char *scrotselcpcmd[] = {"scrotselcp", NULL};
const char *spcmd1[] = {my_terminal, "--class", "terminal", NULL};
const char *spcmd2[] = {my_terminal, "--class", "file-manager", "-e", "ranger", NULL};
const char *spcmd3[] = {my_terminal, "--class", "network-manager", "-e", "nmtui", NULL};
const char *spcmd4[] = {"simplescreenrecorder", NULL};
const char *spcmd5[] = {my_terminal, "--class", "cmus", "-e", "cmus", NULL};
const char *spcmd6[] = {my_terminal, "--class", "calculator", "-e", "python3", NULL};
static Sp scratchpads[] = {
	/* name                 cmd  */
	{"terminal",      	spcmd1},
	{"file-manager",      	spcmd2},
	{"network-manager",     spcmd3},
	{"simplescreenrecorder",spcmd4},
	{"cmus",                spcmd5},
	{"calculator",          spcmd6},
};

static Key keys[] = {
	/* modifier                     key                             function        argument */
	{ MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return,                      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                           togglebar,      {0} },
	{ MODKEY,                       XK_j,                           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                           incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                           setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_w,                           zoom,           {0} },
	{ MODKEY,                       XK_Tab,                         view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                           killclient,     {0} },
	{ MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                       togglefloating, {0} },
	{ MODKEY,                       XK_0,                           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                      tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask, 		XK_f,		                spawn,		{.v = browserfcmd}},
	{ MODKEY|ShiftMask, 		XK_g,		                spawn,		{.v = browserccmd}},
	{ MODKEY|ShiftMask,		XK_v,		                spawn, 		{.v = pavucmd}},
	{ MODKEY|ShiftMask,		XK_l,		                spawn, 		{.v = libreofficecmd}},
	{ 0,		                XF86XK_MonBrightnessDown,	spawn, 		{.v = brightdocmd}},
	{ 0,		                XF86XK_MonBrightnessUp,		spawn, 		{.v = brightupcmd}},
	{ Mod1Mask,			XK_comma,	                spawn,		{.v = voldocmd}},
	{ Mod1Mask,			XK_period,	                spawn,		{.v = volupcmd}},
	{ Mod1Mask,			XK_m,		                spawn,		{.v = voltogcmd}},
	{ 0,				XK_Print,	                spawn,		{.v = scrottopiccmd}},
	{ MODKEY,			XK_Print,	                spawn,		{.v = scrottopicselcmd}},
	{ MODKEY|ShiftMask,		XK_Print,	                spawn,		{.v = scrotcpcmd}},
	{ MODKEY|ControlMask,		XK_Print,	                spawn,		{.v = scrotselcpcmd}},
	{ Mod1Mask,     		XK_Return,     	                togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask, 	        XK_e,	  	                togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,  		XK_n,  		                togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,  		XK_s,  		                togglescratch,  {.ui = 3 } },
	{ MODKEY|ShiftMask,  		XK_m,  		                togglescratch,  {.ui = 4 } },
	{ MODKEY|ShiftMask,  		XK_k,  		                togglescratch,  {.ui = 5 } },
	TAGKEYS(                        XK_1,                           0)
	TAGKEYS(                        XK_2,                           1)
	TAGKEYS(                        XK_3,                           2)
	TAGKEYS(                        XK_4,                           3)
	TAGKEYS(                        XK_5,                           4)
	TAGKEYS(                        XK_6,                           5)
	TAGKEYS(                        XK_7,                           6)
	TAGKEYS(                        XK_8,                           7)
	TAGKEYS(                        XK_9,                           8)
	{ MODKEY|ShiftMask,             XK_q,                           quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


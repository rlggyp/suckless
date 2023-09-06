/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const char my_terminal[]     = "kitty";/* terminal what i use */
static const unsigned int gappx     = 6;       /* gaps between windows */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"JetBrains Mono:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Color Emoji:weight=regular:size=10:antialias=true:autohint=true" 
                                      ,"Noto Sans CJK JP:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK KR:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK SC:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"Noto Sans CJK TC:weight=regular:size=10:antialias=true:autohint=true"
                                      ,"JoyPixels:weight=regular:size=10:antialias=true:autohint=true"};

static const char dmenufont[]       =  "JetBrains Mono:weight=regular:size=10:antialias=true:autohint=true";
static const char col1[]            = "#1a1b26";
static const char col2[]            = "#c0caf5";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col2, col1, col1 },
	[SchemeSel]  = { col1, col2,  col2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	instance    		  			title       	      tags mask       isfloating   	monitor */
	{ NULL,         NULL,										"Volume Control",   0,              1,           	-1 },
	{ "xdman-Main", NULL,										NULL,               0,              1,           	-1 },
	{ NULL,					"terminal",							NULL,	       	      SPTAG(0),	      1,						-1 },
	{ NULL,					"file-manager",					NULL,	       	      SPTAG(1),	      1,						-1 },
	{ NULL,					"network-manager",			NULL,	       	      SPTAG(2),	      1,						-1 },
	{ NULL,					"simplescreenrecorder", NULL,	       	      SPTAG(3),	      1,						-1 },
	{ "Spotify",		NULL,									  NULL,	       				SPTAG(4),	      1,						-1 },
	{ NULL,					"calculator",						NULL,	       	      SPTAG(5),	      1,						-1 },
	{ "discord",		NULL,						        NULL,	       	      SPTAG(6),	      1,						-1 },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col1, "-nf", col2, "-sb", col2, "-sf", col1, NULL };

const char *spcmd1[] = {my_terminal, "--class", "terminal", NULL};
const char *spcmd2[] = {my_terminal, "--class", "file-manager", "-e", "ranger", NULL};
const char *spcmd3[] = {my_terminal, "--class", "network-manager", "-e", "nmtui", NULL};
const char *spcmd4[] = {"simplescreenrecorder", NULL};
const char *spcmd5[] = {"spotify", NULL};
const char *spcmd6[] = {my_terminal, "--class", "calculator", "-e", "python3", NULL};
const char *spcmd7[] = {"discord", NULL};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

static Sp scratchpads[] = {
	/* name                 cmd  */
	{"terminal",            spcmd1},
	{"file-manager",        spcmd2},
	{"network-manager",     spcmd3},
	{"simplescreenrecorder",spcmd4},
	{"spotify",             spcmd5},
	{"calculator",          spcmd6},
	{"discord",             spcmd7},
};

static Key keys[] = {
	/* modifier                     key                             function        argument */
	{ MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                			XK_Return,                      spawn,          SHCMD(my_terminal) },
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
	{ MODKEY|ShiftMask, 						XK_f,		                				spawn,					SHCMD("firefox")},
	{ MODKEY|ShiftMask, 						XK_g,		                				spawn,					SHCMD("firefox --private-window")},
	{ MODKEY|ShiftMask,							XK_v,		                				spawn, 					SHCMD("pavucontrol")},
	{ MODKEY|ShiftMask,							XK_l,		                				spawn, 					SHCMD("libreoffice")},
	{ 0,		                				XF86XK_MonBrightnessDown,				spawn, 					SHCMD("brightnessctl set 2%-")},
	{ 0,		                				XF86XK_MonBrightnessUp,					spawn, 					SHCMD("brightnessctl set 2%+")},
	{ Mod1Mask,											XK_comma,	                			spawn,					SHCMD("amixer -D pulse sset Master 4%-")},
	{ Mod1Mask,											XK_period,	                		spawn,					SHCMD("amixer -D pulse sset Master 4%+")},
	{ Mod1Mask,											XK_m,		   				              spawn,					SHCMD("amixer -D pulse sset Master toggle")},
	{ 0,														XK_Print,	                			spawn,					SHCMD("flameshot full -p ~/Pictures/screenshot_$(date +%Y-%m-%d_%H-%M-%S).png")},
	{ MODKEY,												XK_Print,	              			  spawn,					SHCMD("flameshot gui -p ~/Pictures/screenshot_$(date +%Y-%m-%d_%H-%M-%S).png")},
	{ MODKEY|ShiftMask,							XK_Print,				                spawn,					SHCMD("flameshot full -p .screenshot.png && xclip -selection c -t image/png -i .screenshot.png && rm .screenshot.png")},
	{ MODKEY|ControlMask,						XK_Print,	 				              spawn,					SHCMD("flameshot gui -p .screenshot.png && xclip -selection c -t image/png -i .screenshot.png && rm .screenshot.png")},
	{ MODKEY|ShiftMask, 						XK_z,														spawn, 					SHCMD("slock")},
	{ MODKEY,  				  						XK_period,    		              spawn,  				SHCMD("rofi -show emoji")},
	{ Mod1Mask,     								XK_Return,     	                togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask, 	   	      XK_e,	  	                			togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,  						XK_n,  		                			togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,  						XK_s,  		                			togglescratch,  {.ui = 3 } },
	{ MODKEY|ShiftMask,  						XK_m,  		                			togglescratch,  {.ui = 4 } },
	{ MODKEY|ShiftMask,  						XK_k,  		                			togglescratch,  {.ui = 5 } },
	{ MODKEY|ShiftMask,  						XK_d,  		                			togglescratch,  {.ui = 6 } },
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
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD(my_terminal) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

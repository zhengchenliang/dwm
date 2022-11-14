#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=10" }; // VITAL dwm font here
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=12"; // VITAL dmenu font here
static const char col_black[]       = "#000000";
static const char col_pink[]        = "#FF00FF";
static const char col_red[]         = "#FF0000";
static const char col_orange[]      = "#FFCC00";
static const char col_yellow[]      = "#FFFF00";
static const char col_lightgreen[]  = "#00FF00";
static const char col_darkgreen[]   = "#006600";
static const char col_cyan[]        = "#00FFFF";
static const char col_blue[]        = "#0000FF";
static const char col_purple[]      = "#6600CC";
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#666666";
static const char col_gray3[]       = "#999999";
static const char col_gray4[]       = "#CCCCCC";
static const char col_white[]       = "#FFFFFF";
static const unsigned int baralpha  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg               bg               border   */
	[SchemeNorm] = { col_white,       col_gray1,       col_pink  },
	[SchemeSel]  = { col_lightgreen,  col_darkgreen,   col_cyan  },
	[SchemeHid]  = { col_gray4,       col_gray2,       col_purple  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "Gimp",              NULL,       NULL,       0,            1,           -1 },
	{ "Android Emulator",  NULL,       NULL,       0,            1,           -1 },
	{ "Emulator",          NULL,       NULL,       0,            1,           -1 },
	{ "quemu-system-i386", NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",           NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;   /* number of clients in master area */
static const int resizehints = 1;   /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask // VITAL control key = alt
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */ // VITAL launch scripts
static char dmenumon[2] = "0"; // VITAL dmenu options colors here
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_white, "-sb", col_cyan, "-sf", col_black, "-b", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *browsercmd[]  = { "google-chrome-stable", NULL };

static const char *screenshotcmd[] = { "flameshot", "gui", NULL };

static const char *setqwertycmd[]  = { "~/D0_desktop_base/dwm_me/scripts/david/setxmodmap-qwerty.sh", NULL };
static const char *setcolemakcmd[]  = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/setxmodmap-colemak.sh", NULL };
static const char *suspendcmd[]  = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/suspend.sh", NULL };
static const char *sktogglecmd[]  = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/sck-tog.sh", NULL };
static const char *wpcmd[]  = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/wp-change.sh", NULL };

static const char *upvol[]   = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/vol-up.sh",  NULL };
static const char *downvol[] = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/vol-down.sh",  NULL };
static const char *mutevol[] = { "~/D0_desktop_base/dwm_me/scripts/david/scripts/vol-toggle.sh",  NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x24", NULL };


static Key keys[] = { // VITAL key complex
	/* modifier            key                      function        argument */
	{ MODKEY,              XK_a,                    spawn,          {.v = dmenucmd } }, // open top dialogue - dmenu(1)
	{ MODKEY,              XK_s,                    spawn,          {.v = termcmd } }, // open new terminal - st(1)
	{ MODKEY,              XK_b,                    spawn,          {.v = browsercmd } }, // open browser - defined above google-chrome-stable
	{ 0,                   XK_Print,                spawn,          {.v = screenshotcmd } }, // open screenshot - defined above flameshot
	{ MODKEY|ShiftMask,    XK_z,                    spawn,          {.v = setqwertycmd } }, // open keyset - defined above sh
	{ MODKEY|ShiftMask,    XK_x,                    spawn,          {.v = setcolemakcmd } }, // open colemak - defined above sh
	{ MODKEY|ShiftMask,    XK_c,                    spawn,          {.v = suspendcmd } }, // open suspend - defined above sh
	{ MODKEY|ShiftMask,    XK_v,                    spawn,          {.v = sktogglecmd } }, // open scktog - defined above sh
	{ MODKEY|ShiftMask,    XK_b,                    spawn,          {.v = wpcmd } }, // open wpchange - defined above sh
	{ 0,                   XF86XK_AudioLowerVolume, spawn,          {.v = downvol } }, // volume ctrl - defined above sh
	{ 0,                   XF86XK_AudioMute,        spawn,          {.v = mutevol } }, // volume ctrl - defined above sh
	{ 0,                   XF86XK_AudioRaiseVolume, spawn,          {.v = upvol   } }, // volume ctrl - defined above sh
	{ MODKEY,              XK_bracketleft,          spawn,          {.v = downvol } }, // volume ctrl - defined above sh
	{ MODKEY,              XK_backslash,            spawn,          {.v = mutevol } }, // volume ctrl - defined above sh
	{ MODKEY,              XK_bracketright,         spawn,          {.v = upvol   } }, // volume ctrl - defined above sh
	{ MODKEY|ShiftMask,    XK_l,                    rotatestack,    {.i = +1 } }, // rotate window to next window
	{ MODKEY|ShiftMask,    XK_j,                    rotatestack,    {.i = -1 } }, // rotate window to previous window
	{ MODKEY,              XK_l,                    focusstack,     {.i = +1 } }, // focus window to next window
	{ MODKEY,              XK_j,                    focusstack,     {.i = -1 } }, // focus window to previous window
	// { MODKEY|ControlMask,  XK_n,                    viewtoleft,     {0} }, // functions here are not in use 
	// { MODKEY|ControlMask,  XK_m,                    viewtoright,    {0} }, // can add your function in dwm.c
	// { MODKEY|ShiftMask,    XK_n,                    tagtoleft,      {0} }, // leaving the n and m keys to st
	// { MODKEY|ShiftMask,    XK_m,                    tagtoright,     {0} }, // as the , and . keys below too
	{ MODKEY,              XK_o,                    incnmaster,     {.i = +1 } }, // increase one more main window (vertical layout)
	{ MODKEY,              XK_p,                    incnmaster,     {.i = -1 } }, // decrease one more main window (vertical layout)// windows in page - main window in page left per vertical block - focus window is highlighted - windows can be tiled or floating
	{ MODKEY,              XK_k,                    setmfact,       {.f = -0.05} }, // make main window smaller
	{ MODKEY,              XK_i,                    setmfact,       {.f = +0.05} }, // make main window bigger
	{ MODKEY,              XK_u,                    hidewin,        {0} }, // hide focus window
	{ MODKEY|ShiftMask,    XK_u,                    restorewin,     {0} }, // show hided window
	{ MODKEY,              XK_y,                    hideotherwins,  {0} }, // hide other windows
	{ MODKEY|ShiftMask,    XK_y,                    restoreotherwins,{0}}, // show other windows
	{ MODKEY,              XK_f,                    zoom,           {0} }, // throw/bounce focus window to main window
	{ MODKEY,              XK_g,                    view,           {0} }, // switch between current page and the previous page
	{ MODKEY,              XK_t,                    killclient,     {0} }, // terminate focus window
	{ MODKEY,              XK_q,                    setlayout,      {.v = &layouts[0]} }, // set layout mode - tiled - fixed window
	{ MODKEY,              XK_w,                    setlayout,      {.v = &layouts[1]} }, // set layout mode - float - floating window
	{ MODKEY,              XK_e,                    setlayout,      {.v = &layouts[2]} }, // set layout mode - monocle - focus window fullscreen
	{ MODKEY,              XK_r,                    setlayout,      {0} }, // switch between current layout mode and previous one
	{ MODKEY|ShiftMask,    XK_r,                    fullscreen,     {0} }, // window fullscreen
	{ MODKEY,              XK_space,                togglefloating, {0} }, // switch focus window between tiled/floating modes
	{ MODKEY,              XK_apostrophe,           togglescratch,  {.v = scratchpadcmd } }, // scratchpad defined above
	{ MODKEY,              XK_0,                    view,           {.ui = ~0 } }, // view all windows linked to any page
	{ MODKEY|ShiftMask,    XK_0,                    tag,            {.ui = ~0 } }, // link focus window to all pages
	// { MODKEY|ControlMask,  XK_comma,                focusmon,       {.i = -1 } }, // focus on previous page
	// { MODKEY|ControlMask,  XK_period,               focusmon,       {.i = +1 } }, // focus on next page
	// { MODKEY|ShiftMask,    XK_comma,                tagmon,         {.i = -1 } }, // send focus window to previous page
	// { MODKEY|ShiftMask,    XK_period,               tagmon,         {.i = +1 } }, // send focus window to next page
	TAGKEYS(               XK_1,                                    0) // ModMask + 5 = switch current page to page 5
	TAGKEYS(               XK_2,                                    1) // ModMask + Shift + 5 = link focus window to page 5
	TAGKEYS(               XK_3,                                    2) // ModMask + Shift + Ctrl + 5 = link/unlink focus window to/from page 5
	TAGKEYS(               XK_4,                                    3) // ModeMask + Ctrl + 5 = bring/bonce all windows linked to page 5 to current page
	TAGKEYS(               XK_5,                                    4)
	TAGKEYS(               XK_6,                                    5)
	TAGKEYS(               XK_7,                                    6)
	TAGKEYS(               XK_8,                                    7)
	TAGKEYS(               XK_9,                                    8)
	{ MODKEY|ShiftMask,    XK_p,                    spawn,          SHCMD("killall .base-dwm-bar dwm") }, // exit dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = { // VITAL mouse simplex
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


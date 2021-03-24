/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=14:antialias=true:autohint=true", "JoyPixels:size14:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=14";
#include "/home/xzecora/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
        { "尚",       dwindle },
        /*{ "├┬╴",      dwindle },*/
        { "帝",       tile },
        /*{ "[]=",      tile },*/    /* first entry is default */
        { "虚",       NULL },
        /*{ "<><",      NULL },*/    /* no layout function means floating behavior */
        { "単",       monocle },
        /*{ "[ ]",      monocle },*/
        { "比",       spiral },
        /*{ "[@]",      spiral },*/
};
#include <X11/XF86keysym.h>
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
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont,  "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, topbar ? NULL : "-b", NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *walldwmcmd[] = { "walldwm" , "/home/xzecora/Documents/Wallpapers", NULL };
static const char *browsecmd[]     = { "qutebrowser", NULL };
static const char *powermenu[]     = { "powermenu.sh", NULL};
static const char *volumemute[]    = { "pactl", "set-sink-mute", "1", "toggle", NULL };
static const char *volumelower[]   = { "pactl", "set-sink-volume", "1", "-5%", NULL };
static const char *volumeraise[]   = { "pactl", "set-sink-volume", "1", "+5%", NULL };
static const char *mediaplay[]     = { "playerctl", "play-pause", NULL };
static const char *medianext[]     = { "playerctl", "next", NULL};
static const char *mediaprev[]     = { "playerctl", "previous", NULL};
static const char *mediastop[]     = { "playerctl", "stop", NULL};
static const char *fileman[]       = { "thunar", NULL };
static const char *musicplayer[]   = { "st", "-e", "spotify-tui", NULL };
static const char *discord[]       = { "Discord", NULL }; 
static const char *ygopro[]       = { "YGOPRO", NULL }; 
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_j,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ ControlMask|ShiftMask,        XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_m,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_l,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_h,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = +1 } },
  { MODKEY,                       XK_backslash, spawn,       {.v = walldwmcmd } },
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ ControlMask,                  XK_grave,  spawn,          {.v = termcmd } },
  { MODKEY|ControlMask,           XK_f,      spawn,          {.v = browsecmd } },
  { MODKEY|ControlMask,           XK_t,      spawn,          {.v = fileman } },
  { MODKEY|ControlMask,           XK_s,      spawn,          {.v = musicplayer } },
  { MODKEY|ControlMask,           XK_d,      spawn,          {.v = discord } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = powermenu } },
  { MODKEY|ControlMask,             XK_y,      spawn,          {.v = ygopro } },
  TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },

  { 0,                            XF86XK_AudioPlay, spawn, {.v = mediaplay } },
  { 0,                            XF86XK_AudioNext, spawn, {.v = medianext } },
  { 0,                            XF86XK_AudioPrev, spawn, {.v = mediaprev } },
  { 0,                            XF86XK_AudioStop, spawn, {.v = mediastop } },
  { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volumeraise } },
  { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = volumelower } },
  { 0,                            XF86XK_AudioMute, spawn, {.v = volumemute } }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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


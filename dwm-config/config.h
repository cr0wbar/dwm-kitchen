/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = 
"-*-stlarch-medium-*-*-*-10-*-*-*-*-*-*-*" 
"," 
"-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#AAAAAA";
static const char normbgcolor[]     = "#000F25";
static const char normfgcolor[]     = "#FFFFFF";
static const char selbordercolor[]  = "#1A62CA";
static const char selbgcolor[]      = "#1A62CA";
static const char selfgcolor[]      = "#F5F5F5";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const unsigned bottommargin = 14;    /*Bottom margin in pixel*/
/* tagging */
//static const char *tags[] = { "", "", "", "" };
static const char *tags[] = {"1","2","3","4","5"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Deja-dup", NULL,       "Back Up",  1<<4,         True,        -1 },
};

/* const static Ignore ignored[] = { */
/*   /\*class        instance      ontop*\/ */
/*   {"stalonetray","stalonetray",False}, */
/*   {"Nautilus","desktop_window",False}, */
/* }; */

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      bstack},
	{ "",      monocle },
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

#include "scrolllayout.c"
#include "push.c"
/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
/*static const char *musiccmd[] = { "st","-e","ncmpcpp"};*/
/*static const char *termcmd[]  = { "gnome-terminal","--hide-menubar", NULL };*/
static const char *termcmd[] = { "st", NULL };
static const char *browsercmd[] = { "chromium", NULL};
static const char *filemgcmd[] = { "nautilus" , NULL};
static const char *filemgcmd2[] = { "st" ,"-e" , "ranger", NULL};
static const char *lockandsuspendcmd[] = {"locksusp",NULL};
static const char *lockscreencmd[] ={"slock",NULL}; 
static const char *mpcprevcmd[] = {"mpc","prev",NULL};
static const char *mpctogglecmd[] = {"mpc","toggle",NULL};
static const char *mpcnextcmd[] = {"mpc","next",NULL};
static const char *mpcstopcmd[] = {"mpc","stop",NULL};
static const char *volmutecmd[] = {"amixer","set","Master","Playback","toggle",NULL};
static const char *voldowncmd[] = {"amixer", "set", "Master","5%-",NULL};
static const char *volupcmd[] = {"amixer", "set", "Master","5%+",NULL};
static const char *eclipsecmd[] = {"eclipse", "-nosplash",NULL};
static Key keys[] = {
	/* modifier                     key        function        argument */
        { MODKEY,                       XK_F1,     spawn,          {.v = browsercmd} },
        { MODKEY,                       XK_F2,     spawn,          {.v = filemgcmd} },
        { MODKEY,                       XK_F3,     spawn,          {.v = filemgcmd2} },
        { MODKEY,                       XK_F4,     spawn,          {.v = eclipsecmd} },
        { MODKEY|ShiftMask,             XK_F3,     spawn,          {.v = lockscreencmd} },
        { MODKEY|ShiftMask,             XK_F4,     spawn,          {.v = lockandsuspendcmd} },
        { MODKEY,                       XK_F5,     spawn,          {.v = mpcprevcmd} },
        { MODKEY,                       XK_F6,     spawn,          {.v = mpctogglecmd} },
        { MODKEY,                       XK_F7,     spawn,          {.v = mpcnextcmd} },
	{ MODKEY,                       XK_F8,     spawn,          {.v = mpcstopcmd} },
        { MODKEY,                       XK_F10,    spawn,          {.v = volmutecmd} },
        { MODKEY,                       XK_F11,    spawn,          {.v = voldowncmd} },
        { MODKEY,                       XK_F12,    spawn,          {.v = volupcmd} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushup,         {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  layoutscroll,   {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	/*TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)*/
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        layoutscroll,      {0} },
	/*{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },*/
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

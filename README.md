footware
========

Using this program you can use a midi-input device as a pc-keyboard extension.

It is called footware because I used it with a 'Foot Controller FCB1010' by Behringer.

I configured five ot the ten pedals of the FCB1010 to help my hands
(especially my pinkies ;o) typing inside vim...
Esc, Shift, Ctrl, End and Alt can now be triggered by my lazy feet.

You can map midi-notes to different keys inside the sourcefile...
I don't think that it is necessary to use an extra configuration file since the whole
program is only a little longer now than a config file would be ;o)

To map note number 35 to an additional Escape-Key use this:

`case 35: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_Escape), inpacket[1], CurrentTime );`

You can add more notes into the case statement...

To find the correct name for the key you want to emulate, look it up in keysymdef.h
(probably /usr/include/X11/keysymdef.h)...

To compile footware try:

`make`

If there are some problems, you may have to change some directories in the Makefile...

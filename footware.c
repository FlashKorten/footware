////////////////////////////////////////////////////////////////////////
//
// footware  -  Version 0.1
// ---------
//
// see README.md for enlightenment ;o)
//
// Written by Sebastian Korten
// eMail: Sebastian.Korten at gmail.com
// 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
////////////////////////////////////////////////////////////////////////

#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>


int main(void) {
		// Set-up the display to send the fake-key-events to...
		Display* pDisplay = XOpenDisplay( NULL );
		if( pDisplay == NULL ) return 1;

		unsigned char inpacket[4];
		unsigned char noteNumber;
		unsigned char result = 0;

		// first open the sequencer device for reading.
		int seqfd = open("/dev/sequencer", O_RDONLY);

		if (seqfd == -1) return 0;

		fd_set readfs;	/* file descriptor set */

		while (1) {
				FD_SET(seqfd, &readfs);

				select(seqfd+1, &readfs, NULL, NULL, NULL);

				if(FD_ISSET(seqfd, &readfs)) {
						read(seqfd, &inpacket, sizeof(inpacket));

						if (inpacket[0] == SEQ_MIDIPUTC) {
								if ((inpacket[1] & 0xf0) == 0x90) {
										read(seqfd, &inpacket, sizeof(inpacket));
										noteNumber = inpacket[1];
										read(seqfd, &inpacket, sizeof(inpacket));
										switch(noteNumber) {
												case 35: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_Escape), inpacket[1], CurrentTime );
														 break;
												case 36: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_Shift_L), inpacket[1], CurrentTime );
														 break;
												case 38: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_Control_L), inpacket[1], CurrentTime );
														 break;
												case 40: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_End), inpacket[1], CurrentTime );
														 break;
												case 41: result = XTestFakeKeyEvent( pDisplay, XKeysymToKeycode( pDisplay, XK_Alt_L), inpacket[1], CurrentTime );
														 break;
										}
								}
						}
						XFlush(pDisplay);
				}
		}
		XCloseDisplay(pDisplay);
		return 0;
}


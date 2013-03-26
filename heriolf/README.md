Heriolf
======

GPS receiver with a simple LCD display.


Install
======

Note: To make this work with a LS20031 GPS receiver, one would need to change;
	#define _NewSS_MAX_RX_BUFF 64 // RX buffer size
to
	#define _NewSS_MAX_RX_BUFF 128 // RX buffer size
in the SoftSerial.h library file.


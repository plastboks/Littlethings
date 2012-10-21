TweenoSTP
=========

Tweeno::SimpleTransferProtocol

A simple protocol for transfering image, and stringdata from a computer.
The library is for now optimized for Python Serial and Python PIL.
As of 2012-10-19 the project is still early Alpha state.


Python
======
The python test code inside the python folder has the following dependencies:
  
  * Python PIL (with libPng or libjpeg)
  * pySerial


UTFT
====
The example Arduino file inside the example directory depends on:

  * TweenoSTP (https://github.com/plastboks/TweenoSTP)
  * TweenoUTFT (https://github.com/plastboks/TweenoUTFT)

Both these libraries need to be located by the Arduino IDE. The standard UTFT library @ henningkarlsen.com will not work.

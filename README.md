squRemote
=========

The PC part of the squRemote app. squRemote is a small utility (only on Android currently) that lets you control all the media running on a computer.
This code is for Linux.

Ok, so what does it do?
------------------------

Basically, when you run the program, it starts a TCP server and starts listening in on port 9999. When it receives a key press (from the android app), it simulates the corresponding key press on the PC. That's it.

You don't need the app to connect to it. You can use any TCP Client, connect it to your PC's ip address and port 9999 and send in. Start a media player (Banshee or Totem or maybe anything), then send in play. It will probably start playing (or pause if it already is). See.

It can be extended to simulate any key press. Currently it supports all the alpha-numeric keys, the media keys and some modifiers (shift, ctrl, alt).

You can send key combinations like this: shift+left.

It only takes combos with two keys at the moment.

You can compile it with g++.

Get the app here: http://squgeim.blogspot.com/2013/12/squremote.html

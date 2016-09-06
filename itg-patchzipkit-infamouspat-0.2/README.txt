ITG2 Arcade patch.zip encrypter/decrypter toolkit - 2007 infamouspat



alright, I suck at these readme.txt things, but I gotta have one so I can spam it
once several people grab these programs, gank their name in it, and release
it as their own *COUGH*mDaWg....


=================
Table of Contents
=================

0x01......................Introduction
0x02......................Major disclaimer that you definitely need to read
0x03......................credits, shout-outs, shoebiting, etc.


=========================================================
0x01 - Intro
=========================================================

	Enough people bugged me on forums and AIM to either have ready-made arcade patch.zip files
or have others decrypted.  This is my answer to their call.  What this package 
has are programs to turn regular zip files into encrypted patch files that can be added to
an ITG2 machine or have already made ones decrypted.  With this, it is possible to add your own
metrics to the theme, noteskins, custom mods, and anything else that can be put into the stepmania
root of an ITG2 system without the hassle of messing with Static.ini.

Q) patch.zip?
	in Roxor's Arcade .itg files (they're just zip files), there is a file named "patch.zip"
within the .itg file.  This file is copied to the machine and becomes
part of the Stepmania file system for ITG2.  In these patch.zip files are updates to steps or the
theme.  The file can be replaced to add other things to ITG2.  Look up an ITG2 arcade hacking 
guide on how to add files and such.  The file you must replace is /Stats/patch/patch.zip

usage: patchdec.exe will take any patch zip file (DO NOT NAME AS patch-dec.zip), and create a single
"patch-dec.zip" regular zip file.

patchenc.exe will do vice versa, only spit out a "patch.zip" rather than "patch-dec.zip" (so that
means be sure not to have anything named "patch.zip" in the folder you're doing the work from).

Q) Why no source code for v0.2?

If you want the source, just ask.


=========================================================
0x02 - DISCLAIMER
=========================================================

you've probably heard it before...

These tools give you the power to tamper with multi-thousand dollar arcade systems in a way
that the makers did not intend for you to configure it.  This should
already set of an alarm in your head, especially if the machine is not yours.  Understand that by
"hacking" a machine you are not only voiding the warranty of the machine, but are completely
responsible for what happens to that machine.  Do not go crying to me or Roxor technical support
if you screw something up permanently because you don't know how to use Linux or something like 
that.  Speaking of Linux, I HIGHLY RECOMMEND that the people who modify arcade machines have
a basic knowledge of how to use a Linux command line interface.  ******IF YOU DON'T KNOW WHAT
YOU'RE DOING, YOU SHOULDN'T BE DOING IT********

=========================================================
0x03......................credits, shout-outs, random shit
=========================================================

these people definitely need to be in here cause they're awesome:

Dr Brian Gladman - developing an amazing implementation of AES
Spectere - creating a non-cygwin version of the tools

KholdFuzion, AJ187, GRIM657 - testers, contributors
Roxor Games - guess...
#boxorroxors - my other dysfunctional family
nevets933, Kyle, Para, xjen0vax, Boredgasm - keeping me plenty of company on AIM while I sat through lines of code
		and letting me vent my frustrations
trance music - apparently it makes me feel smarter


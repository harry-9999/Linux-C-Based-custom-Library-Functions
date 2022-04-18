# Linux-C-Based-custom-Library-Functions

The standard library function for reading directories on Linux is [readdir , which is built on top of the system call.
Programs such as ls, find, sh, zsh, and others use readdir to read contents of directories.

This program will interpose readdir so that it will hide a secret file whose name is set by an environment variable. You do this by setting the LD_PRELOAD environment variable:

export LD_PRELOAD=$PWD/hidefile.so

This tells the system to load the functions in the specified shared library before loading any others and to give these functions precedence.

For example, you can run the command ls to list all files in a directory:

$ ls -l total 196 -rw------- 1 pxk allusers 3855 Feb 20 18:02 present.pptx -rw------- 1 pxk allusers 237 Feb 20 18:02 salaries.xlsx -rw------- 1 pxk allusers 18198 Feb 20 18:02 secretfile -rw------- 1 pxk allusers 3584 Feb 20 18:02 secretfile.docx -rw------- 1 pxk allusers 24879 Feb 20 18:02 secretfile.txt -rw------- 1 pxk allusers 805 Feb 20 18:01 status-report-1.txt -rw------- 1 pxk allusers 13260 Feb 20 18:01 status-report-2.txt -rw------- 1 pxk allusers 29878 Feb 20 18:02 status-report-3.txt -rw------- 1 pxk allusers 5047 Feb 20 18:02 status-report-4.txt -rw------- 1 pxk allusers 19550 Feb 20 18:03 testfile.c

But if you set the environment variable HIDDEN to a specific file name, that file will not be visible:

$ export HIDDEN $ HIDDEN=secretfile.txt $ ls -l total 163 -rw------- 1 pxk allusers 3855 Feb 20 18:02 present.pptx -rw------- 1 pxk allusers 237 Feb 20 18:02 salaries.xlsx -rw------- 1 pxk allusers 18198 Feb 20 18:02 secretfile -rw------- 1 pxk allusers 3584 Feb 20 18:02 secretfile.docx -rw------- 1 pxk allusers 805 Feb 20 18:01 status-report-1.txt -rw------- 1 pxk allusers 13260 Feb 20 18:01 status-report-2.txt -rw------- 1 pxk allusers 29878 Feb 20 18:02 status-report-3.txt -rw------- 1 pxk allusers 5047 Feb 20 18:02 status-report-4.txt -rw------- 1 pxk allusers 19550 Feb 20 18:03 testfile.c

Create an alternate version of the readdir Linux library function that will:

Call the real version of readdir
Check if the returned file name matches the name in the environment variable HIDDEN
If it does, call readdir again to skip over this file entry.
Return the file data to the calling program.
We will use Linux’s LD_PRELOAD mechanism.
This is an environment variable that forces the listed shared libraries to be loaded for programs you run. The dynamic linker will search these libraries first when it resolves symbols in the program.

This allows you to take control and replace library functions that programs use with your own versions.

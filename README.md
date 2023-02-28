
## C++ Keylogger using Windows API

### Setup
Get the latest release or clone this repository and compile.

### How does it work
This program actively listens to keys states with GetKeyState and translates the entire keyboard context to the output streams (log.txt file and console).
It's possible to change the keyboard layout (DLL) via shortcuts (the default is KBDUSX).

## --dllname  
Fetches the KBD**.dll file with that name for meaningful state translation (e.g. "KBDUSX" for the United-States International Keyboard Layout).  
These .dll files are located at /Windows/System32.  

## Usage:
It has hard coded shortcuts:  
ALT + T: hides/shows console window  
ALT + X: kills the process  
ALT + S: stops the keylogging process and provides options to the user:  
"E" to resume keylogging;  
"N" to kill keylog thread and exit;  
any key to change DLL  


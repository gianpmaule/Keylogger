
## C++ Keylogger utilizing Windows API

### Setup
Get the latest release or clone and compile this project.

### How does it work
This program actively listens to keys states with GetKeyState and translates the entire keyboard context to the output streams  
The keylogger receives two command line parameters: --dllname (-d) and --output (-o)  

## --dllname  
Fetches the KBD**.dll file with that name for meaningful state translation (e.g. "KBDUSX" for United-States International Keyboard Layout).  
These .dll files are located at /Windows/System32.  

## --output  
The name of the log file that will be created at the binary file root directory (e.g. "log.txt).  
This application keylogs and attempts to translate diverse keyboard inputs.  

## Usage:
It has hard coded shortcuts:  
ALT + T: hides/shows console window  
ALT + X: kills the process  


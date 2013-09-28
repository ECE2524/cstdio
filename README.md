# Boilerplate C Standard I/O

Set `PROGNAME` in `Makefile` to desired name of compiled program.

Compiled program will accept a number of arguments (run with `-h` to
see the current options) any non-option command line arguments will be
attemped to be opened as a file for read access.  If no additional
command line options are used then the programmer may choose to read
from standard in.

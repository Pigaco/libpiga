Libpiga
=======

This is a compact C-library to provide a fast IPC-mechanism tailored to the pigaco system
to all games and other applications on the piga platform. It provides 
an input event queue, an output event queue (for commands to the system) and 
easy access to the current state of the console (buttons and other inputs). 

This library also has bindings to Lua. 

Dependencies
------------

This library has no dependencies other than libc and Linux. It directly uses system includes
and hides these dependencies in the built binaries to make linking easier for third-party applications.

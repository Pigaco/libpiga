Libpiga
=======

This is a compact C-library to provide a fast IPC-mechanism tailored to the pigaco system
to all games and other applications on the piga platform. It provides 
an input event queue, an output event queue (for commands to the system) and 
easy access to the current state of the console (buttons and other inputs). 

This library also has bindings to Lua. 

Parts of the library
--------------------

The library is structured into three parts: 

  * `piga_common`
  * `piga_client`
  * `piga_server`

The common library is linked to by both the server and the client. The server handles hosting
the `piga_host` structure, receiving inputs and updating the piga system. Clients only have
to initialize a `piga_client`, to be able to talk directly to the system over an internally 
mapped shared memory segment.

Example for a client
--------------------

A client can look the following: 

```C++
#include <piga/client.h>

#include <piga/event.h>
#include <piga/event_app_installed.h>

int main(int argc, char *argv[])
{
    piga_status status = PIGA_STATUS_OK;
    
    // Create the client.
    piga_client *client = piga_client_create();
    piga_client_config *client_config = piga_client_config_default();
    
    piga_client_consume_config(client, client_config);
    
    status = piga_client_connect(client, "Test Client", sizeof("Test Client"));
    if(status != PIGA_STATUS_OK) {
        // Error!
    }
    
    // Client
    piga_event_queue *client_queue = piga_client_get_in_queue(client);
    
    while(piga_event_queue_poll(client_queue, ev) == PIGA_STATUS_OK) {
        switch(piga_event_get_type(ev)) {
            case PIGA_EVENT_APP_INSTALLED:
                break;
               // Other event types, see include/event.h
        }
    }
    
    // Always free the client BEFORE the host!
    piga_client_free(client);
}
```

For more examples, please look into the test/ directory. 

Dependencies
------------

This library has no dependencies other than libc and Linux. It directly uses system includes
and hides these dependencies in the built binaries to make linking easier for third-party applications.

Location of `piga_host`
----------------------

The `piga_host` structure is hosted by [the daemon](https://github.com/pigaco/daemon). All inputs
are also processed by it, so the client applications don't have to worry about system internal things.

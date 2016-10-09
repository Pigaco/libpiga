#define BOOST_TEST_MODULE HostAndClient
#include <boost/test/unit_test.hpp>

#include <piga/host.h>
#include <piga/client.h>

#include <piga/event.h>
#include <piga/event_app_installed.h>

BOOST_AUTO_TEST_CASE(TypeMaskTestCase)
{
    piga_host *host = piga_host_create();
    
    piga_host_config *config = piga_host_config_default();
    
    piga_status status = PIGA_STATUS_OK;
    status = piga_host_consume_config(host, config);
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    status = piga_host_startup(host);
    if(status != PIGA_STATUS_OK) {
        BOOST_TEST_MESSAGE(piga_status_what(&status));
        BOOST_TEST_MESSAGE(piga_errno_what());
    }
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    // Host has started up, now test the client connection.
    piga_client *client = piga_client_create();
    piga_client_config *client_config = piga_client_config_default();
    client_config->event_type_mask = PIGA_EVENT_UNKNOWN
        | PIGA_EVENT_APP_INSTALLED 
        | PIGA_EVENT_PLAYER_JOINED;
    
    piga_client_consume_config(client, client_config);
    
    status = piga_client_connect(client, "Test Client", sizeof("Test Client"));
    if(status != PIGA_STATUS_OK) {
        BOOST_TEST_MESSAGE(piga_status_what(&status));
        BOOST_TEST_MESSAGE(piga_errno_what());
    }
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    // Update the host to register the new client.
    piga_host_update(host);
    
    piga_event *ev = piga_event_create();
    piga_event_set_type(ev, PIGA_EVENT_APP_INSTALLED);
    piga_host_push_event(host, ev);
    piga_host_update(host);
    
    // Client
    piga_event_queue *client_queue = piga_client_get_in_queue(client);
    
    // The event must be okay, because the type mask allows PIGA_EVENT_APP_INSTALLED.
    BOOST_REQUIRE_EQUAL(piga_event_queue_poll(client_queue, ev), PIGA_STATUS_OK);
    
    
    // Test a wrong event type.
    piga_event_set_type(ev, PIGA_EVENT_CONSUMER_REGISTERED);
    piga_host_push_event(host, ev);
    piga_host_update(host);
    // The test should say the queue is empty, because the client type map forbids 
    // PIGA_EVENT_CONSUMER_REGISTERED.
    BOOST_REQUIRE_EQUAL(piga_event_queue_poll(client_queue, ev), PIGA_ERROR_EMPTY_QUEUE);
    
    piga_event_free(ev);
    
    // Always free the client BEFORE the host!
    piga_client_free(client);
    
    // Update the host to unregister the new client.
    piga_host_update(host);
    
    piga_host_free(host);
}

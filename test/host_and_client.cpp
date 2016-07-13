#define BOOST_TEST_MODULE HostAndClient
#include <boost/test/unit_test.hpp>

#include <piga/host.h>
#include <piga/client.h>

#include <piga/event.h>
#include <piga/event_app_installed.h>

BOOST_AUTO_TEST_CASE(HostAndClientCase)
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
    
    piga_client_consume_config(client, client_config);
    
    status = piga_client_connect(client, "Test Client", sizeof("Test Client"));
    if(status != PIGA_STATUS_OK) {
        BOOST_TEST_MESSAGE(piga_status_what(&status));
        BOOST_TEST_MESSAGE(piga_errno_what());
    }
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    // Test input passing
    piga_player *client_player1 = piga_client_get_player_by_id(client, 1);
    piga_player *host_player1 = piga_host_get_player_by_id(host, 1);
    
    piga_player_set_input(host_player1, 1, 100);
    
    BOOST_REQUIRE_EQUAL(piga_player_get_input(client_player1, 1), 100);
    
    piga_player_set_direct_output(client_player1, 1, 100);
    
    BOOST_REQUIRE_EQUAL(piga_player_get_direct_output(host_player1, 1), 100);
    
    // Update the host to register the new client.
    piga_host_update(host);
    
    // Test the event queue (host->client)
    
    piga_event *ev = piga_event_create();
    piga_event_set_type(ev, PIGA_EVENT_APP_INSTALLED);
    piga_event_app_installed *app_ev = piga_event_get_app_installed(ev);
    piga_event_app_installed_set_name(app_ev, "Test App", sizeof("Test App"));
    piga_host_push_event(host, ev);
    
    
    piga_event_set_type(ev, PIGA_EVENT_UNKNOWN);
    
    // Client
    piga_event_queue *client_queue = piga_client_get_in_queue(client);
    BOOST_REQUIRE_EQUAL(piga_event_queue_poll(client_queue, ev), PIGA_STATUS_OK);
    
    BOOST_REQUIRE_EQUAL(piga_event_get_type(ev), PIGA_EVENT_APP_INSTALLED);
    app_ev = piga_event_get_app_installed(ev);
    
    char name_cache[PIGA_EVENT_APP_INSTALLED_NAME_LENGTH];
    
    piga_event_app_installed_get_name(app_ev, name_cache);
    
    std::string name_tester(name_cache);
    
    BOOST_REQUIRE_EQUAL(name_tester, std::string("Test App"));
    
    piga_event_free(ev);
    
    // Always free the client BEFORE the host!
    piga_client_free(client);
    
    // Update the host to unregister the new client.
    piga_host_update(host);
    
    piga_host_free(host);
}

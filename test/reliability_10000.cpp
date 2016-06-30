#define BOOST_TEST_MODULE Reliability10000
#include <boost/test/unit_test.hpp>

#include <thread>
#include <functional>

#include <piga/host.h>
#include <piga/client.h>

BOOST_AUTO_TEST_CASE(HostAndClientCase)
{
    piga_host *host = piga_host_create();
    
    piga_host_config *config = piga_host_config_default();
    
    piga_status status = PIGA_STATUS_OK;
    status = piga_host_consume_config(host, config);
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    status = piga_host_startup(host);
    if(status != PIGA_STATUS_OK) {
        BOOST_TEST_MESSAGE(piga_status_what(status));
        BOOST_TEST_MESSAGE(piga_errno_what());
    }
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    // Host has started up, now test the client connection.
    piga_client *client = piga_client_create();
    piga_client_config *client_config = piga_client_config_default();
    
    piga_client_consume_config(client, client_config);
    
    status = piga_client_connect(client);
    if(status != PIGA_STATUS_OK) {
        BOOST_TEST_MESSAGE(piga_status_what(status));
        BOOST_TEST_MESSAGE(piga_errno_what());
    }
    BOOST_REQUIRE_EQUAL(status, PIGA_STATUS_OK);
    
    // Test input passing
    piga_player *client_player1 = piga_client_get_player_by_id(client, 1);
    piga_player *host_player1 = piga_host_get_player_by_id(host, 1);
    
    std::function<void()> read_test([&]() {
        for(int i = 0; i < 10000; ++i) {
            for(char n = 0; n < host->config->player_count; ++n) {
                piga_player *player = piga_client_get_player_by_id(client, n);
                for(char x = 0; x < PIGA_PLAYER_INPUTS_COUNT; ++x) {
                    piga_player_get_input(player, x);
                }
            }
        }
    });
    std::function<void()> write_test([&]() {
        for(int i = 0; i < 10000; ++i) {
            for(char n = 0; n < host->config->player_count; ++n) {
                piga_player *player = piga_host_get_player_by_id(host, n);
                for(char x = 0; x < PIGA_PLAYER_INPUTS_COUNT; ++x) {
                    piga_player_set_input(player, x, rand() % 1000);
                    piga_player_set_input(player, x, rand() % 1000);
                }
            }
        }
    });
    
    std::thread client1(read_test);
    std::thread client2(read_test);
    
    write_test();
    
    client1.join();
    client2.join();
    
    piga_client_free(client);
    
    piga_host_free(host);
}


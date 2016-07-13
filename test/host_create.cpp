#define BOOST_TEST_MODULE CreateHost
#include <boost/test/unit_test.hpp>

#include <piga/host.h>
BOOST_AUTO_TEST_CASE(CreateHostCase)
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
    
    // Test default name
    piga_player *player = piga_host_get_player_by_id(host, 0);
    char *receivedName_c = piga_player_get_name(player);
    std::string receivedName(receivedName_c);
    free(receivedName_c);
    
    BOOST_REQUIRE_EQUAL(receivedName, PIGA_PLAYER_DEFAULT_NAME);
    
    // Test customized name
    std::string name = "Hello World!";
    piga_player_set_name(player, name.c_str(), name.length());
    
    receivedName_c = piga_player_get_name(piga_host_get_player_by_id(host, 0));
    receivedName = std::string(receivedName_c);
    free(receivedName_c);
    
    BOOST_REQUIRE_EQUAL(name, receivedName);
    
    piga_host_free(host);
}

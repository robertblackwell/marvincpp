//
// Start both a server and a number of client tthreads and have each of the client
// threads make a number of requests from the server.
//
#include <thread>
#include <boost/process.hpp>
#include "http_server.hpp"
#include "pipe_collector.hpp"
#include "collector_base.hpp"
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include "rb_logger.hpp"
RBLOGGER_SETLEVEL(LOG_LEVEL_DEBUG)

/**
 * This is the simplest possible test of the http mitm proxy. To run it needs manual intervention.
 * After starting execution of tp_proxy_simple executable the program will hang waiting for
 * http traffic to be proxied through localhost:9992
 *
 * Such traffic can be generated by running the script curl.sh that resides in the
 * tests/test_proxy_alone directory.
 *
 * If you have cloned this project from github you will need to modify the curl.sh script
 * to access a different url as the one that comes in the script is local to my development
 * system.
 *
 * Each time you run curl.sh the traffic between the curl.sh script and the url/server
 * will be displayed on stdout.
 *
 * Inspect that traffic to satisfy yourself that the traffic is being correctly captured.
 */
int main( int argc, char* argv[] )
{
    LogTrace("hello");
    VLogDebug("hello");
    RBLogging::enableForLevel(LOG_LEVEL_WARN);

    std::vector<std::regex> re{std::regex("^ssllabs(.)*$")};
    std::vector<int> ports{443, 9443};
    ForwardingHandler::configSet_HttpsPorts(ports);
    ForwardingHandler::configSet_HttpsHosts(re);

    HTTPServer* server_ptr;

    auto proxy_func = [&server_ptr](void* param) {
        server_ptr = new HTTPServer([](boost::asio::io_service& io) {
            CollectorBase* pc = new CollectorBase(io, std::cout);
            auto f = new ForwardingHandler(io, pc);
            return f;
        });
        server_ptr->listen(9992);
    };
    std::thread proxy_thread(proxy_func, nullptr);

    proxy_thread.join();
}


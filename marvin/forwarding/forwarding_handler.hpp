//
//  forwarding_handler.hpp
//  MarvinCpp
//
//  Created by ROBERT BLACKWELL on 12/25/16.
//  Copyright © 2016 Blackwellapps. All rights reserved.
//

#ifndef marvin_forwarding_handler_hpp
#define marvin_forwarding_handler_hpp
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <regex>
#include "request.hpp"
#include "request_handler_base.hpp"
#include "rb_logger.hpp"
#include "UriParser.hpp"
#include "client.hpp"
#include "message.hpp"
#include "tcp_connection.hpp"
#include "http_header.hpp"
#include "tunnel_handler.hpp"

enum class ConnectAction;

/**
*  @brief This class implements the proxy forwarding process for http/https protocols.
*  Its a revised version to make way for future requirements of "replaying" an exchange
*   The V2 version of this class makes the composition of functions during the forwarding
*   process more evident.
*  @discussion Reads a message from the downstream client, converts that to a non-proxy request
*  to the targets server, sends that request, collects the response and finally sends that response
*  to the originating client.
*  Along the way it captures (via template parameter TCapture) a summary of the original request and
*  upstream server response and distributes that according to the rules of the particular TCapture object
*/
template<class TCollector> class ForwardingHandler : public RequestHandlerBase
{
    public:
        // these are configuration settings
        static void configSet_HttpsHosts(std::vector<std::regex> re);
        static void configSet_HttpsPorts(std::vector<int> ports);
    
        ForwardingHandler(boost::asio::io_service& io);
        ~ForwardingHandler();
    
        void handleConnect(
            MessageReaderSPtr           req,
            ISocketSPtr                 connPtr,
            HandlerDoneCallbackType     done);

        void handleRequest(
            ServerContext&   server_context,
            MessageReaderSPtr           req,
            MessageWriterSPtr           rep,
            HandlerDoneCallbackType done
        );
    
    private:
    
        static std::vector<std::regex>  s_https_hosts;
        static std::vector<int>         s_https_ports;
    
        // methods that are used in handleRequest
        void p_round_trip_upstream(
            MessageReaderSPtr req,
            std::function<void(Marvin::ErrorType& err, MessageBaseSPtr downstreamReplyMsg)> upstreamCb
        );
        void p_handle_upstream_response_received(Marvin::ErrorType& err);
        void p_make_downstream_response();
        void p_make_downstream_error_response(Marvin::ErrorType& err);
        void p_handle_upgrade();
        void p_on_complete(Marvin::ErrorType& err);
    
        // methods that are used in handleConnect
        ConnectAction p_determine_connection_action(std::string host, int port);
        void p_initiate_tunnel();
    
        // utility methods
        void p_response403Forbidden(MessageWriter& writer);
        void p_response200OKConnected(MessageWriter& writer);
        void p_response502Badgateway(MessageWriter& writer);


        /// @brief Only used by the handleConnect method
        ISocketSPtr                 m_conn;
        /// reader of the initial request from downstream - passed in to our handleRequest method
        MessageReaderSPtr           m_req;
        /// writer of the final response tod own stream - passed in to our handler request method
        MessageBaseSPtr             m_resp;
        MessageWriterSPtr           m_resp_wrtr;
        /// message object to hold final downstream response
        MessageBaseSPtr             m_downstream_msg_sptr;
        /// done callback - passed in to our handleRequest method
        HandlerDoneCallbackType     m_done_callback;
        Marvin::BufferChainSPtr     m_response_body_sptr;

        /// Client instance to handle upstream round trip
        ClientUPtr                  m_upstream_client_uptr;
        MessageBaseSPtr             m_upstream_request_msg_sptr;

    
        /// this will collect summaries of the req and resp
        std::string                 m_scheme;
        std::string                 m_host;
        int                         m_port;
        TCollector*                 m_collector;
    
        /// used for handleConnect - tunnel
        Marvin::MBufferUPtr         m_initial_response_buf;
        TunnelHandlerSPtr           m_tunnel_handler;
        ISocketSPtr                 m_downstream_connection; // used only for tunnel
        TCPConnectionSPtr           m_upstream_connection; // used only for tunnels
    
        /// regexs to define hosts that require mitm not tunnel
        std::vector<std::regex>     m_https_hosts;
    
        /// list of port numbers that can be https mitm'd rather than tunneled
        std::vector<int>            m_https_ports;

};

#include "forwarding_handler.ipp"

#endif /* forwarding_handler_hpp */

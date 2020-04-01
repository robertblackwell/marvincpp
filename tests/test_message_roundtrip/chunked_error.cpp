#include <doctest/doctest.h>

// #include <boost/process.hpp>
#include <boost/algorithm/string.hpp>
#include <json/json.hpp>
#include <marvin/buffer/buffer_chain.hpp>
// #include <marvin/http/uri.hpp>
// #include <marvin/http/message_base.hpp>
// #include <marvin/http/message_factory.hpp>
// #include <marvin/error/marvin_error.hpp>
// #include <marvin/helpers/helpers_fs.hpp>
// #include <marvin/collector/collector_base.hpp>
// #include <marvin/forwarding/forward_helpers.hpp>
#include "chunked_error.hpp"


ChunkedError::ChunkedError(
            std::string path,   // the string that goes after the method usually for non proxy requests a relative path like /echo/smart
            HttpMethod  method,
            std::string scheme, // http or https
            std::string host,   // host name without the port so localhost not localhost:3000
            std::string port,    // port such as 3000){}
            std::string body 
)           
{
    m_path = path;
    m_scheme = scheme;
    m_method = method;
    m_host = host;
    m_port = port;
    m_body = body;
}
std::string ChunkedError::getHost() {return m_host;}
std::string ChunkedError::getPort() {return m_port;}
void ChunkedError::verifyResponse(Marvin::ErrorType& er, Marvin::Http::MessageBaseSPtr response)
{
    CHECK(er);
}
Marvin::BufferChainSPtr ChunkedError::makeBody()
{
    using namespace Marvin;
    BufferChainSPtr chain_sptr  = BufferChain::makeSPtr(m_body);
    return chain_sptr;
}
Marvin::Http::MessageBaseSPtr ChunkedError::makeRequest()
{
    /// this sends the request to our mitm proxy
    Marvin::Http::MessageBaseSPtr msg = std::make_shared<Marvin::Http::MessageBase>();
    msg->setMethod(HTTP_POST);
    msg->setUri(m_path);
    msg->setHeader(Marvin::Http::Headers::Name::Host, m_host);
    msg->setHeader("User-Agent","Opera/9.80 (X11; Linux x86_64; Edition Next) Presto/2.12.378 Version/12.50");
    msg->setHeader(
        "Accept","text/html, application/xml;q=0.9, application/xhtml xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1");
    msg->setHeader("Accept-Language","en");
    msg->setHeader("Accept-Charset","iso-8859-1, utf-8, utf-16, utf-32, *;q=0.1");
    msg->setHeader(Marvin::Http::Headers::Name::AcceptEncoding,"deflate, gzip, x-gzip, identity, *;q=0");

    msg->setHeader(Marvin::Http::Headers::Name::Connection,"Close");
    msg->setHeader(Marvin::Http::Headers::Name::ETag,"1928273tefadseercnbdh");
    msg->setHeader("X-SPECIAL-HEADER", "proof of passthru");
    // std::string s = "012345678956";
    // Marvin::BufferChainSPtr bdy = Marvin::BufferChain::makeSPtr(s);
    // msg->setContent(bdy);
    m_request_sptr = msg;
    return msg;
}
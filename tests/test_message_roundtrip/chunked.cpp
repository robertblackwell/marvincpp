#include "chunked.hpp"

#include <doctest/doctest.h>
#include <boost/algorithm/string.hpp>
#include <json/json.hpp>

#include <marvin/buffer/buffer_chain.hpp>
#include <marvin/configure_trog.hpp>
TROG_SET_FILE_LEVEL(Trog::LogLevelDebug)

#include <marvin/m_log.hpp>

using namespace Marvin;

Chunked::Chunked(
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
std::string Chunked::getHost() {return m_host;}
std::string Chunked::getPort() {return m_port;}
void Chunked::verifyResponse(ErrorType& er, MessageBaseSPtr response)
{
    CHECK(!er);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    BufferChainSPtr bsp = response->getContentBuffer();
    std::string raw_body = bsp->to_string();
    if (response->statusCode() != 200) {
        auto x = response->statusCode();
        std::cout << "chunked verifyResponse statusCode: " << x << std::endl;
    }
    CHECK(response->statusCode() == 200);
    
    bool te_check = response->hasHeader(HeadersV2::TransferEncoding);
    CHECK(te_check);
    if (te_check) {
        std::string te = response->getHeader(HeadersV2::TransferEncoding);
        CHECK(te == "chunked");
    }

    bool cl_check = response->hasHeader(HeadersV2::ContentLength);
    CHECK(!cl_check);

    std::string tech = response->getHeader(HeadersV2::TransferEncoding);
    TROG_DEBUG("Body of response is : ", raw_body);
    bool test = raw_body == "abcdefghijklmnopqrstuvwxyz1234567890ABCEDFGHIJKLMNOPQRSTUVWXYZ";
    MTRACE( __func__ << std::endl);
    return;
}
BufferChainSPtr Chunked::makeBody()
{
    using namespace Marvin;
    BufferChainSPtr chain_sptr  = BufferChain::makeSPtr(m_body);
    return chain_sptr;
}
MessageBaseSPtr Chunked::makeRequest()
{
    /// this sends the request to our mitm proxy
    MessageBaseSPtr msg = std::make_shared<MessageBase>();
    msg->setMethod(HTTP_POST);
    msg->setUri(m_path);
    msg->setHeader(HeadersV2::Host, m_host);
    msg->setHeader("User-Agent","Opera/9.80 (X11; Linux x86_64; Edition Next) Presto/2.12.378 Version/12.50");
    msg->setHeader(
        "Accept","text/html, application/xml;q=0.9, application/xhtml xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1");
    msg->setHeader("Accept-Language","en");
    msg->setHeader("Accept-Charset","iso-8859-1, utf-8, utf-16, utf-32, *;q=0.1");
    msg->setHeader(HeadersV2::AcceptEncoding,"deflate, gzip, x-gzip, identity, *;q=0");

    msg->setHeader(HeadersV2::Connection,"Close");
    msg->setHeader(HeadersV2::ETag,"1928273tefadseercnbdh");
    msg->setHeader("X-SPECIAL-HEADER", "proof of passthru");
    // std::string s = "012345678956";
    // BufferChainSPtr bdy = BufferChain::makeSPtr(s);
    // msg->setContent(bdy);
    m_request_sptr = msg;
    return msg;
}

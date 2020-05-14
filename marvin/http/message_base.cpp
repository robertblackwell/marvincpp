#include <marvin/http/message_base.hpp>

#include <string>
#include <map>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include<http-parser/http_parser.h>
#include <marvin/error_handler/error_handler.hpp>

namespace Marvin{

std::string traceMessage(MessageBase& msg)
{
    std::stringstream ss;
    ss << std::endl << "MSG[" << std::hex << &msg << std::dec << "]: ";
    
    if( msg.isRequest() ){
        ss << msg.getMethodAsString() << " " << msg.uri() << " HTTP/1." << msg.httpVersMinor();
    }else{
        ss << "HTTP/1." << msg.httpVersMinor() << " " << msg.statusCode() << " " << msg.status()<< " ";
    }
    
    ss << (msg.getHeaders().str());
    std::string s = ss.str();
    return ss.str();
}

void serializeHeaders(MessageBase& msg, Marvin::MBuffer& mb)
{
    boost::asio::streambuf b;
    std::ostream os(&b);

    std::string vers = "HTTP/" + std::to_string(msg.httpVersMajor()) + "." + std::to_string(msg.httpVersMinor());
    if( msg.isRequest() ){
        std::string m = msg.getMethodAsString();
        std::string u = msg.uri();
        os << m << " " << u << " " << vers << "\r\n";
    } else{
        os << vers << " " << msg.m_status_code << " " << msg.m_status <<  "\r\n";
    }
    
    for(auto const& h : msg.m_headers) {
        os << h.key << ": " << h.value << "\r\n";
    }
    // end of headers
    os << "\r\n";
    // debugging only
    boost::asio::streambuf::const_buffers_type bufs = b.data();

    std::string ss(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + b.size() );
    mb.append((void*) ss.c_str(), ss.size());
//    return b;
//    std::string sss = ss;
//    std::cout << __FUNCTION__ << ":" << ss << std::endl;
    
}
Marvin::MBufferSPtr serializeHeaders(MessageBase& msg)
{
    std::string h = "";
    serialize_headers(msg, h);
    return Marvin::MBuffer::makeSPtr(h);
}
std::string serialize_headers(MessageBase& msg)
{
    std::string h{""};
    serialize_headers(msg, h);
    return h;
}
void serialize_headers(MessageBase& msg, std::string& str)
{
    str = "";
    std::ostringstream os;
    os.str(str);
    std::string vers = "HTTP/" + std::to_string(msg.httpVersMajor()) + "." + std::to_string(msg.httpVersMinor());
    if( msg.isRequest() ) {
        std::string m = msg.getMethodAsString();
        std::string u = msg.uri();
        os << m << " " << u << " " << vers << "\r\n";
    } else{
        os << vers << " " << msg.m_status_code << " " << msg.m_status <<  "\r\n";
    }
    for(auto const& h : msg.m_headers) {
        os << h.key << ": " << h.value << "\r\n";
    }
    // end of headers
    os << "\r\n";
    str = os.str();
}
//void serialize_headers(MessageBase& msg, BufferChainSPtr bchain_sptr)
//{
//    int num_bytes = 0;
//    MBufferSPtr mb1;
//    if( msg.isRequest() ) {
//        std::string m = msg.getMethodAsString();
//        std::string u = msg.uri();
//        os << m << " " << u << " " << vers << "\r\n";
//    } else{
//        do {
//            mb1 = MBuffer::makeSPtr(1000 + num_bytes + 10);
//            num_bytes = snprintf((char *) mb1->data(), mb1->capacity(), "HTTP/%1d.%1d %3.d %s\r\n",
//                                 msg.httpVersMajor(), msg.httpVersMinor(), msg.m_status_code, msg.m_status.c_str());
//            mb1->setSize(num_bytes);
//        } while(num_bytes > 1000 - 1);
//    }
//    bchain_sptr->push_back(mb1);
//    MBufferSPtr mb2 = MBuffer::makeSPtr(256);
//    for(auto const& h : msg.m_headers) {
//        num_bytes = 0;
//        do {
//            mb2 = MBuffer::makeSPtr(256 + num_bytes + 10);
//            num_bytes = snprintf((char *) mb2->data(), mb2->capacity(), "%s: %s\r\n", h.key.c_str(), h.value.c_str());
//            mb2->setSize(num_bytes);
//        } while(num_bytes > 256 - 1);
//        bchain_sptr->push_back(mb2);
//    }
//    bchain_sptr->append("\r\n");
//    std::string schain = bchain_sptr->to_string();
////    std::cout << schain << std::endl;
//}
void serialize(Marvin::HeadersV2& hdrs, MBufferSPtr mb)
{
    for(auto const& h : hdrs) {
        mb->append((void*)h.key.c_str(), h.key.size());
        mb->append((void*)(char*)": ", 2);
        mb->append((void*)h.value.c_str(), h.value.size());
        mb->append((void*)(char*)"\r\n", 2);
    }
}

void serialize(MessageBase& msg, MBufferSPtr mb)
{
    static std::string const req_vers1_0 = " HTTP/1.0\r\n";
    static std::string const req_vers1_1 = " HTTP/1.1\r\n";
    static std::string const resp_vers1_0 = "HTTP/1.0 ";
    static std::string const resp_vers1_1 = "HTTP/1.1 ";
    static std::string const lfcr = "\n\r";
    int num_bytes = 0;
    if( msg.isRequest() ) {
        mb->append(msg.getMethodAsString());
        mb->append(" ");
        mb->append((void*)msg.uri().c_str(), msg.uri().size());
        if (msg.httpVersMinor() == 0) {
            mb->append(req_vers1_0);
        } else {
            mb->append(req_vers1_1);
        }
    } else{
        if (msg.httpVersMinor() == 0) {
            mb->append(resp_vers1_0);
        } else {
            mb->append(resp_vers1_1);
        }
        std::string remainder_of_line = std::to_string(msg.m_status_code) + " " + msg.m_status + "\r\n";
        mb->append(remainder_of_line);
    }
    serialize(msg.m_headers, mb);
    mb->append((void*)(char*)"\r\n", 2);
    serialize(msg.m_trailers, mb);
//    std::cout << schain << std::endl;
}
///
/// KeepAlive is true if:
///     there is a connection header that contains the string "[ ,]keep-alive[ ,]" case independent
///     or
///     there is NOT a connection header that contain the string 'close' case insensitive
///         and the msg http version is 1.1
///
/// Keepalive is explicitly false if
///     there is a connection header that contain the string 'close' case insensitive
///     or
///     there is NOT a connection header that contain the string 'keep-alive' case insensitive
///         and the msg http version is 1.0
///
bool isConnectionKeepAlive(Marvin::MessageBase& msg)
{
    if (msg.hasHeader(HeadersV2::Connection)) {
        if (isConnectionKeepAlive(msg.getHeader(HeadersV2::Connection))) {
            return true;
        } else if (isConnectionClose(msg.getHeader(HeadersV2::Connection))) {
            return false;
        }
    }
    if (msg.httpVersMinor() == 1) {
        return true;
    } else {
        return false;
    }
}

#pragma - http message base impl

MessageBase::MessageBase()
{
    this->m_is_request = true;
    this->setHttpVersMajor(1);
    this->setHttpVersMinor(1);
    this->m_body_chain_sptr = std::make_shared<BufferChain>();
}
MessageBase::MessageBase(MessageBase& other)
{
    *this = other;
    m_body_chain_sptr = std::make_shared<BufferChain>(*other.m_body_chain_sptr);
}
MessageBase::MessageBase(MessageBase&& other)
{
    *this = std::move(other);
}
MessageBase& MessageBase::operator =(MessageBase& other)
{
    if (this == &other) {
        return *this;
    }
    m_is_request    = other.m_is_request;
    m_method        = other.m_method;
    m_methodStr     = other.m_methodStr;
    m_uri           = other.m_uri;
    m_status_code   = other.m_status_code;
    m_status        = other.m_status;
    m_http_major    = other.m_http_major;
    m_http_minor    = other.m_http_minor;
    m_headers       = other.m_headers;
    m_trailers      = other.m_trailers; 
    m_body_chain_sptr = std::make_shared<BufferChain>(*other.m_body_chain_sptr);
    return *this;
}
MessageBase& MessageBase::operator =(MessageBase&& other)
{
    if (this == &other) {
        return *this;
}
    m_is_request    = other.m_is_request;
    m_method        = other.m_method;
    m_methodStr     = other.m_methodStr;
    m_uri           = other.m_uri; other.m_uri = "";
    m_status_code   = other.m_status_code;
    m_status        = other.m_status;
    m_http_major    = other.m_http_major;
    m_http_minor    = other.m_http_minor;
    m_headers       = std::move(other.m_headers);
    m_trailers      = std::move(other.m_trailers);
    m_body_chain_sptr = other.m_body_chain_sptr;
    other.m_body_chain_sptr = BufferChain::makeSPtr();
}

MessageBase::~MessageBase(){}

bool MessageBase::isRequest(){ return m_is_request; }

void MessageBase::setIsRequest(bool flag){ m_is_request = flag;}

void MessageBase::setStatusCode(int sc){ m_status_code = sc; m_is_request = false; }

void MessageBase::setStatus(std::string st){ m_status = st; m_is_request = false; }

int MessageBase::statusCode() {return m_status_code; };

std::string MessageBase::status() {return m_status;};

void MessageBase::setMethod(HttpMethod m){ m_method = (enum http_method)m;  m_is_request = true; }
void MessageBase::setMethod(enum http_method m){ m_method = m; m_is_request = true; }
void MessageBase::setMethod(std::string m){ m_methodStr = m; m_is_request = true; }

std::string MessageBase::getMethodAsString(){return httpMethodString((HttpMethod) m_method);};

void
MessageBase::setUri(std::string u){ m_uri = u;}

std::string
MessageBase::uri()
{
    return m_uri;
}
std::string MessageBase::getPath()
{
    return m_uri;
}
void MessageBase::setPath(std::string path)
{
    m_uri = path;
}
void MessageBase::setHttpVersMajor(int major)
{ 
    m_http_major = major; 
}

int MessageBase::httpVersMajor() {return m_http_major; }

void MessageBase::setHttpVersMinor(int minor){ m_http_minor = minor; }

int MessageBase::httpVersMinor(){return m_http_minor; }

void MessageBase::setHeader(std::string key, std::string value)
{
    std::string v(value);
    std::string v2 = boost::algorithm::trim_copy(v);
    m_headers.setAtKey(key, v2);
};

bool MessageBase::hasHeader( std::string key) 
{
    return ( m_headers.find(key) != m_headers.end() );
};

std::string MessageBase::header(std::string key) 
{
    boost::optional<std::string> res{m_headers.atKey(key)};
    if(res) {
        return res.get();
    } else {
        MARVIN_THROW("header " + key + " does not exist");
    }
}

void MessageBase::removeHeader( std::string keyIn)
{
    m_headers.removeAtKey(keyIn);
}

std::string MessageBase::getHeader(std::string key)
{
    boost::optional<std::string> result{m_headers.atKey(key)};
    if(result) {
        return result.get();
    }
    MARVIN_THROW("trying to access non-existent header value");
    return nullptr;
}
std::size_t MessageBase::contentLength()
{
    std::string s = header(HeadersV2::ContentLength);
    int v = std::atoi(s.c_str());
    return (std::size_t)v;
}
Marvin::HeadersV2& MessageBase::getHeaders()
{
    return m_headers;
}
std::string MessageBase::str()
{
    return serialize_headers(*this);
}
Marvin::BufferChainSPtr MessageBase::getContentBuffer()
{
    return m_body_chain_sptr;
}
void MessageBase::setContentBuffer(Marvin::BufferChainSPtr bufSPtr)
{
    m_body_chain_sptr = bufSPtr;
}
Marvin::BufferChainSPtr MessageBase::getContent()
{
    return m_body_chain_sptr;
}
void MessageBase::setContent(Marvin::BufferChainSPtr bufSPtr)
{
    m_body_chain_sptr = bufSPtr;
    removeHeader(Marvin::HeadersV2::TransferEncoding);
    setHeader(Marvin::HeadersV2::ContentLength, std::to_string(bufSPtr->size()));
}
void MessageBase::setContent(std::string content)
{
    m_body_chain_sptr = Marvin::BufferChain::makeSPtr(content);
    removeHeader(Marvin::HeadersV2::TransferEncoding);
    setHeader(Marvin::HeadersV2::ContentLength, std::to_string(m_body_chain_sptr->size()));
}

void MessageBase::dumpHeaders(std::ostream& os)
{
    HeadersV2::Iterator it = m_headers.begin();
    while(it != m_headers.end()) {
        os<<it->key <<" : "<<it->value<<std::endl;
        it++;
    }
}
void MessageBase::setTrailer(std::string key, std::string value)
{ 
    m_trailers.setAtKey(key, value); 
};
bool MessageBase::hasTrailer( std::string key)
{ 
    return ( m_trailers.find(key) != m_trailers.end() ); 
};
std::string MessageBase::trailer(std::string key)
{
    boost::optional<std::string> result{m_headers.atKey(key)};
    if( result ){
        return result.get();
    } else{ 
        return nullptr;
    } 
}
    
std::ostream &operator<< (std::ostream &os, MessageBase &msg)
{
    os << msg.str() ;
    return os;
}

} //namespace Marvin

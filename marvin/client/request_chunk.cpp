//
// Implements the function sequence to write a chunk of body data
//
#include <marvin/client/request.hpp>
#include <cassert>                                      // for assert
#include <istream>                                      // for string
#include <marvin/connection/socket_factory.hpp>         // for socketFactory
#include <marvin/external_src/rb_logger/rb_logger.hpp>  // for LogInfo, LogD...
#include <marvin/message/message_reader.hpp>            // for MessageReader
#include <memory>                                       // for operator!=
#include <string>                                       // for to_string
#include <boost/asio/streambuf.hpp>                     // for streambuf
#include <cert/error.hpp>                               // for THROW
#include <marvin/http/http_header.hpp>                  // for Headers, Head...
#include <marvin/http/uri.hpp>                          // for Uri
#include <marvin/message/message_writer.hpp>            // for MessageWriter
#include <marvin/external_src/rb_logger/rb_logger.hpp>
RBLOGGER_SETLEVEL(LOG_LEVEL_WARN)

namespace boost { namespace asio { namespace ip { class tcp; } } }
namespace boost { namespace system { class error_code; } }

using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::io_service;
using boost::asio::streambuf;
using namespace Marvin;
using namespace Marvin::Http;

//--------------------------------------------------------------------------------
// start sequence of functions to write a the headers and a single body buffer.
//--------------------------------------------------------------------------------
void Request::p_internal_write_body_chunk(Marvin::BufferChainSPtr body_chunk_chain_sptr, WriteBodyDataCallbackType cb)
{

}
#ifndef test_case_hpp
#define test_case_hpp

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <marvin/error/marvin_error.hpp>
#include <marvin/http/http_header.hpp>

typedef std::vector<std::string> TestcaseType;
typedef std::string TestcaseResultType;

//-----------------------------------------------------------------------------------------------------
class Testcase
{
public:
    Testcase(
    std::string description,
    std::vector<std::string> rawMessage,
    std::string result_first_line,
    int status_code,
    Marvin::ErrorType result_onheader_err,
    Marvin::Http::Headers::Initializer result_headers,
    std::string result_body
);
    std::string getDescription();
    std::string lineAt(std::size_t ix);
    std::vector<std::string> buffers();
    bool verify_first_line(std::string fl);
    
    bool verify_headers(Marvin::Http::Headers& h);
    
    bool verify_body(std::string b);
    
    std::string result_first_line();
    
    int result_status_code();
    
    Marvin::ErrorType result_onheaders_err();

    Marvin::Http::Headers& result_headers();
    
    std::string result_body();
    
    std::string next();
    
    bool finished();
    
    bool is_error_case();
    
    std::string case_result();
    
    int                                     _index;
    std::string                             _description;
    std::vector<std::string>                _rawMessage;
    int                                     _result_status_code;
    Marvin::ErrorType                       _result_onheaders_err;
    std::string                             _result_first_line;
    Marvin::Http::Headers::Initializer      _result_headers_vec;
    Marvin::Http::Headers                   _result_headers;
    std::string                             _result_body;
};

#endif

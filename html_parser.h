#ifndef __HTML_PARSER_H__
#define __HTML_PARSER_H__
#include <string>
#include <vector>
#include "http_fetch.h"
class HtmlParser {
public:
    HtmlParser(HttpFetch *http) :
        _http(http) {
	}
    std::vector<std::string> GetAllLinks(const std::string& uri) const 
	{
        // TODO(cboumenot): implement
		_http->GetUriAsString(uri);
		std::vector<std::string> ret;
		ret.push_back(uri);

        return ret;
    }
private:
    HttpFetch *_http;
};
#endif // __HTML_PARSER_H__

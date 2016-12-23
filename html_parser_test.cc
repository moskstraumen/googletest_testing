#include <string>
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "http_fetch.h"
#include "html_parser.h"
using ::testing::Return;

class HttpFetchMock : public HttpFetch
{
public:
    MOCK_CONST_METHOD1(GetUriAsString, std::string(const std::string& uri));
};

TEST(HtmlParser, OneLink)
{
    char *html = "<html>"
    "<head></head>"
    "<body>"
    "<a href='/index.html'>index.html</a>"
    "</body>"
    "</html>";
    HttpFetchMock mock;
    EXPECT_CALL(mock, GetUriAsString(::testing::_))
        .WillOnce(Return(std::string(html)));
	HtmlParser parser(&mock);
    std::vector<std::string> links = parser.GetAllLinks("http://example.net");
    EXPECT_EQ(1, links.size());
    EXPECT_STREQ("http://example.net", links[0].c_str());
}

TEST(HtmlParser, NoData)
{
    char *html = "";
    HttpFetchMock mock;
    HtmlParser parser(&mock);
    EXPECT_CALL(mock, GetUriAsString("http://example.net"))
        .WillOnce(Return(std::string(html)));
    std::vector<std::string> links = parser.GetAllLinks("http://example.net");
    EXPECT_EQ(1, links.size());
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

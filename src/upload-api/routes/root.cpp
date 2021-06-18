#include "upload-api/responses/response_200.h"
#include "upload-api/routes/root.h"

boost::beast::http::response<boost::beast::http::string_body> Root(const boost::beast::http::request<boost::beast::http::dynamic_body>& req)
{
	return make_200<boost::beast::http::string_body>(req, "", "text/html");;
}

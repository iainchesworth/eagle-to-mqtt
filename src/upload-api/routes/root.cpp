#include "upload-api/responses/response_200.h"
#include "upload-api/routes/root.h"

const std::string ApiRoute_Root::APIROUTE_REGEX{ "^/$" };

ApiRoute_Root::ApiRoute_Root() : 
	IApiRoute(boost::beast::http::verb::get, APIROUTE_REGEX)
{
}

ApiRoute_Root::~ApiRoute_Root()
{
}

HttpResponse ApiRoute_Root::Handler(const HttpRequest& request)
{
	return make_200<boost::beast::http::string_body>(request, "", "text/html");
}

#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#include <boost/beast/http.hpp>

#include <memory>
#include <string>
#include <vector>

#include "interfaces/iapiroute.h"
#include "interfaces/ihttprouter.h"
#include "upload-api/http_types.h"

class HttpRouter : public IHttpRouter
{
public:
	HttpRouter();
	virtual ~HttpRouter() = default;

public:
	HttpResponse HandleRoute(const HttpRequest& req) const final;

public:
	HttpRouter& AddRoute(const std::shared_ptr<IApiRoute> route);

private:
	std::vector<std::shared_ptr<IApiRoute>> m_Routes;
};

#endif // HTTP_ROUTER_H

#ifndef ROUTEROOT_H
#define ROUTEROOT_H

#include "interfaces/iapiroute.h"
#include "upload-api/http_types.h"

class ApiRoute_Root : public IApiRoute
{
	static const std::string APIROUTE_REGEX;

public:
	ApiRoute_Root();
	virtual ~ApiRoute_Root();

public:
	HttpResponse Handler(const HttpRequest& request);
};

#endif // ROUTEROOT_H

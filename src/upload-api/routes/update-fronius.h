#ifndef ROUTEUPDATE_H
#define ROUTEUPDATE_H

#include "interfaces/iapiroute.h"
#include "upload-api/http_types.h"

class ApiRoute_Fronius : public IApiRoute
{
	static const std::string APIROUTE_REGEX;

public:
	ApiRoute_Fronius();
	virtual ~ApiRoute_Fronius();

public:
	HttpResponse Handler(const HttpRequest& request);
};

#endif // ROUTEUPDATE_H

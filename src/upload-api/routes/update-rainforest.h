#ifndef ROUTE_UPDATE_EAGLE_H
#define ROUTE_UPDATE_EAGLE_H

#include "interfaces/iapiroute.h"
#include "upload-api/http_types.h"

class ApiRoute_Rainforest : public IApiRoute
{
	static const std::string APIROUTE_REGEX;

public:
	ApiRoute_Rainforest();
	virtual ~ApiRoute_Rainforest() = default;

public:
	HttpResponse Handler(const HttpRequest& request) final;
}; 

#endif // ROUTE_UPDATE_EAGLE_H

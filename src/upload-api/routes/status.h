#ifndef ROUTESTATUS_H
#define ROUTESTATUS_H

#include "interfaces/iapiroute.h"
#include "upload-api/http_types.h"

class ApiRoute_Status : public IApiRoute
{
	static const std::string APIROUTE_REGEX;

public:
	ApiRoute_Status();
	virtual ~ApiRoute_Status() = default;

public:
	HttpResponse Handler(const HttpRequest& request) final;
};

#endif // ROUTESTATUS_H

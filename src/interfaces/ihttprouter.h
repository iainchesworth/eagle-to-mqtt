#ifndef IHTTPROUTER_H
#define IHTTPROUTER_H

#include "upload-api/http_types.h"

class IHttpRouter
{
public:
	virtual HttpResponse HandleRoute(const HttpRequest& req) const = 0;
};

#endif // IHTTPROUTER_H

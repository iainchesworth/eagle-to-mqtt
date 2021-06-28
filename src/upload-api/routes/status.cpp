#include <boost/json.hpp>

#include "metering/device_registry.h"
#include "metering/devices/eagle.h"
#include "serialization/eagle_serializer.h"
#include "upload-api/responses/response_200.h"
#include "upload-api/routes/status.h"

boost::beast::http::response<boost::beast::http::string_body> Status(const boost::beast::http::request<boost::beast::http::dynamic_body>& req)
{
    boost::json::object response_object;
	std::stringstream response_stream;
    
    /*
    {
      "bridge": {
        "":"",
        "":""
      },
      "device_id":{
        "ZigbeeId":"",
        "Firmware":"",
        "Hardware":"",
        "Model":"",
        "Stats":{
          "MessageCount":"",
          "MissingPayloadFields":"",
          "ErrorsWhileProcessing":"",
          "ConnectionStatusCount":"",
          "CurrentSummationCount":"",
          "DeviceInfoCount":"",
          "MessageClusterCount":"",
          "NetworkInfoCount":"",
          "PriceClusterCount":""
        },
        "PricingTiers":[
          {
            "tier_id":{
              "RateLabel":"",
              "StartsAt":"",
              "EndsAt":"",
              "":""
            },
            "tier_id":{
              "RateLabel":"",
              "StartsAt":"",
              "EndsAt":"",
              "":""
            }
          }
        ]
      },
      "device_id":{

      }
    }
    */

	// Report the bridge information
	// response_tree.add_child("bridge", bridge_node);

	// Report the collection of Eagle devices
	for (auto device : DeviceRegistry::Get())
	{
        response_object[EthernetMacId::ToString(device.first)] = Eagle_Serializer(device.second).Serialize();
	}

    const auto test_string = boost::json::serialize(response_object);
	return make_200<boost::beast::http::string_body>(req, boost::json::serialize(response_object), "application/json");
}

#ifndef TEST_TOOLS_NOTIFICATION_PAYLOAD_TEST_H
#define TEST_TOOLS_NOTIFICATION_PAYLOAD_TEST_H

#include "notifications/common/metering_payload_types.h"

namespace test_tools
{

void NotificationPayload_ValueTester(const MeteringPayload_ElementMap& map, const MeteringPayload_ElementMap::key_type& key, const std::string& value_as_string);

}
// namespace test_tools

#endif // TEST_TOOLS_NOTIFICATION_PAYLOAD_TEST_H

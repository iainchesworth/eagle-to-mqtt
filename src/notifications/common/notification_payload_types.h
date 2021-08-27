#ifndef NOTIFICATION_PAYLOAD_TYPES_H
#define NOTIFICATION_PAYLOAD_TYPES_H

#include <cstdint>

#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "notifications/metering/notification_publishpayload.h"

using EagleNotification_PublishPayload = Notification_PublishPayload<EthernetMacId>;
using SymoNotification_PublishPayload = Notification_PublishPayload<uint32_t>;

#endif // NOTIFICATION_PAYLOAD_TYPES_H

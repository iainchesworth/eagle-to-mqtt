#ifndef NOTIFICATION_BASE_DEVICESTATS_H
#define NOTIFICATION_BASE_DEVICESTATS_H

#include <cstdint>
#include <string>

#include "metering/common/timestamps.h"

template<typename PUBLISH_PAYLOAD_TYPE>
class Notification_BaseDeviceStats : public PUBLISH_PAYLOAD_TYPE
{
public:
	explicit Notification_BaseDeviceStats(typename PUBLISH_PAYLOAD_TYPE::Types::DeviceId device_id) :
		PUBLISH_PAYLOAD_TYPE(device_id)
	{
	}

public:
	template<typename DEVICE_STATS_TYPE>
	Notification_BaseDeviceStats& DeviceStats(const DEVICE_STATS_TYPE& statistics)
	{
		LastMessageTimestamp(statistics.LastMessageTimestamp);
		MissingPayloadFields(statistics.MissingPayloadFields);
		ErrorsWhileProcessing(statistics.ErrorsWhileProcessing);
		TotalMessageCount(statistics.TotalMessageCount);
		UnknownMessageCount(statistics.UnknownMessageCount);

		return *this;
	}

public:
	Notification_BaseDeviceStats& LastMessageTimestamp(const UnixTimepoint& timestamp)
	{
		static const std::string MAPKEY_LASTMESSAGETIMESTAMP{ "last_message_timestamp" };
		this->m_ElementsMap.insert_or_assign(MAPKEY_LASTMESSAGETIMESTAMP, timestamp);
		return *this;
	}

	Notification_BaseDeviceStats& MissingPayloadFields(const uint64_t& missing_payload_fields)
	{
		static const std::string MAPKEY_MISSINGPAYLOADFIELDS{ "missing_payload_fields" };
		this->m_ElementsMap.insert_or_assign(MAPKEY_MISSINGPAYLOADFIELDS, missing_payload_fields);
		return *this;
	}

	Notification_BaseDeviceStats& ErrorsWhileProcessing(const uint64_t& errors_while_processing)
	{
		static const std::string MAPKEY_ERRORSWHILEPROCESSING{ "errors_while_processing" };
		this->m_ElementsMap.insert_or_assign(MAPKEY_ERRORSWHILEPROCESSING, errors_while_processing);
		return *this;
	}

	Notification_BaseDeviceStats& TotalMessageCount(const uint64_t& total_message_count)
	{
		static const std::string MAPKEY_TOTALMESSAGECOUNT{ "total_message_count" };
		this->m_ElementsMap.insert_or_assign(MAPKEY_TOTALMESSAGECOUNT, total_message_count);
		return *this;
	}

	Notification_BaseDeviceStats& UnknownMessageCount(const uint64_t& unknown_message_count)
	{
		static const std::string MAPKEY_UNKNOWNMESSAGECOUNT{ "unknown_message_count" };
		this->m_ElementsMap.insert_or_assign(MAPKEY_UNKNOWNMESSAGECOUNT, unknown_message_count);
		return *this;
	}
};

#endif // NOTIFICATION_BASE_DEVICESTATS_H

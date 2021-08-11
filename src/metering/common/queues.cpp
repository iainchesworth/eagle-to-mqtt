#include <spdlog/spdlog.h>

#include "exceptions/invalid_queue_value.h"
#include "metering/common/queues.h"

const std::string Queues::NOT_SPECIFIED{ "Not Specified" };
const std::string Queues::ACTIVE{ "Active" };
const std::string Queues::CANCEL_PENDING{ "Cancel Pending" };
const std::string Queues::UNKNOWN{ "Unknown" };

Queues::Queues() :
	Queues(QueueTypes::NotSpecified)
{
}

Queues::Queues(QueueTypes queue) :
	m_Queue(queue)
{
}

Queues::Queues(const std::string& queue) :
	m_Queue(FromString(queue))
{
}

Queues::QueueTypes Queues::FromString(const std::string& queue_string)
{
	QueueTypes queue_type = QueueTypes::NotSpecified;

	if (0 == queue_string.length())
	{
		spdlog::warn("Invalid Queue provided to converter (zero-length)");
		throw InvalidQueueValue("Zero-length queue value");
	}
	else if (ACTIVE == queue_string)
	{
		queue_type = QueueTypes::Active;
	}
	else if (CANCEL_PENDING == queue_string)
	{
		queue_type = QueueTypes::CancelPending;
	}
	else
	{
		spdlog::warn("Unknown Queue provided to converter: {}", queue_string);
		queue_type = QueueTypes::Unknown;
	}

	return queue_type;
}

std::string Queues::ToString(const QueueTypes queue_type)
{
	switch (queue_type)
	{
	case QueueTypes::NotSpecified:
		return NOT_SPECIFIED;
	case QueueTypes::Active:
		return ACTIVE;
	case QueueTypes::CancelPending:
		return CANCEL_PENDING;
	case QueueTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Queues::operator==(const Queues& other) const
{
	return (m_Queue == other.m_Queue);
}

bool Queues::operator==(const QueueTypes& queue_type) const
{
	return (m_Queue == queue_type);
}

bool Queues::operator<(const Queues& other) const
{
	return (m_Queue < other.m_Queue);
}

std::ostream& operator<<(std::ostream& os, const Queues& queue)
{
	os << queue.ToString(queue.m_Queue);
	return os;
}

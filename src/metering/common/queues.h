#ifndef QUEUES_H
#define QUEUES_H

#include <ostream>
#include <string>

class Queues
{
	static const std::string NOT_SPECIFIED;
	static const std::string ACTIVE;
	static const std::string CANCEL_PENDING;
	static const std::string UNKNOWN;

public:
	enum class QueueTypes
	{
		NotSpecified,
		Active,
		CancelPending,
		Unknown
	};

public:
	Queues();
	explicit Queues(QueueTypes queue);
	explicit Queues(const std::string& queue);

private:
	QueueTypes m_Queue;

public:
	static QueueTypes FromString(const std::string& queue_string);
	static std::string ToString(const QueueTypes queue_type);

public:
	bool operator==(const Queues& other) const;
	bool operator==(const QueueTypes& queue_type) const;
	bool operator<(const Queues& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Queues& queue);
};


#endif // QUEUES_H

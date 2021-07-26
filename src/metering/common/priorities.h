#ifndef PRIORITIES_H
#define PRIORITIES_H

#include <ostream>
#include <string>

class Priorities
{
	static const std::string NOT_SPECIFIED;
	static const std::string LOW;
	static const std::string MEDIUM;
	static const std::string HIGH;
	static const std::string CRITICAL;
	static const std::string UNKNOWN;

public:
	enum class PriorityTypes
	{
		NotSpecified,
		Low,
		Medium,
		High,
		Critical,
		Unknown
	};

public:
	Priorities();
	explicit Priorities(PriorityTypes priority);
	explicit Priorities(const std::string& priority);

private:
	PriorityTypes m_Priority;

public:
	static PriorityTypes FromString(const std::string& priority_string);
	static std::string ToString(const PriorityTypes priority_type);

public:
	bool operator==(const Priorities& other) const;
	bool operator==(const PriorityTypes& priority_type) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Priorities& priority);
};

#endif // PRIORITIES_H

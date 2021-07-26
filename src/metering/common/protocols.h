#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <ostream>
#include <string>

#include <string>

class Protocols
{
	static const std::string NOT_SPECIFIED;
	static const std::string ZIGBEE;
	static const std::string UNKNOWN;

public:
	enum class ProtocolTypes
	{
		NotSpecified,
		Zigbee,
		Unknown
	};

public:
	Protocols();
	explicit Protocols(ProtocolTypes protocol);
	explicit Protocols(const std::string& protocol);

private:
	ProtocolTypes m_Protocol;

public:
	static ProtocolTypes FromString(const std::string& protocol_string);
	static std::string ToString(const ProtocolTypes protocol_type);

public:
	bool operator==(const Protocols& other) const;
	bool operator==(const ProtocolTypes& protocol_type) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Protocols& protocol);
};

#endif // PROTOCOLS_H


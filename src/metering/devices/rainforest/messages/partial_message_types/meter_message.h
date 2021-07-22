#ifndef METERMESSAGE_H
#define METERMESSAGE_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <queue>
#include <string>

#include "metering/common/priorities.h"

class MeterMessage
{
public:
	MeterMessage(const std::string& id, const std::string& text, Priorities priority, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration, bool confirmation_required, bool confirmed);

public:
	std::string Id() const;
	std::string Text() const;
	Priorities Priority() const;
	std::chrono::time_point<std::chrono::system_clock> ValidFrom() const;
	std::chrono::time_point<std::chrono::system_clock> ValidTill() const;
	bool ConfirmationRequired() const;
	bool IsConfirmed() const;

public:
	static MeterMessage ExtractFromPayload(const boost::property_tree::ptree& node);

private:
	std::string m_Id;
	std::string m_Text;
	Priorities m_Priority;
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::minutes m_Duration;
	bool m_ConfirmationRequired;
	bool m_Confirmed;
};

using MeterMessageQueue = std::queue<MeterMessage>;

#endif // METERMESSAGE_H

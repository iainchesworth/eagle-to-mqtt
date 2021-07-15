#ifndef BLOCK_PERIOD_H
#define BLOCK_PERIOD_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>

class BlockPeriod
{
public:
	BlockPeriod(double consumption, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration);

public:
	std::chrono::time_point<std::chrono::system_clock> Starts() const;
	std::chrono::time_point<std::chrono::system_clock> Ends() const;
	double Consumption() const;

public:
	static BlockPeriod ExtractFromPayload(const boost::property_tree::ptree& node);

private:
	double m_Consumption;
	std::chrono::time_point<std::chrono::system_clock> m_Start;
	std::chrono::minutes m_Duration;
};

#endif // BLOCK_PERIOD_H

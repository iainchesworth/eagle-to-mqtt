#include <boost/log/trivial.hpp>

#include "bridge/bridge.h"
#include "bridge/bridge_registry.h"

BridgeRegistry::BridgeRegistry() :
	m_Bridge(nullptr),
	m_BridgeMutex()
{
	BOOST_LOG_TRIVIAL(debug) << L"Initialising the BridgeRegistry";
}

std::shared_ptr<Bridge> BridgeRegistry::operator()()
{
	std::lock_guard<std::mutex> guard(m_BridgeMutex);
	return m_Bridge;
}

void BridgeRegistry::Add(std::shared_ptr<Bridge> bridge)
{
	std::lock_guard<std::mutex> guard(m_BridgeMutex);
	m_Bridge = bridge;
}

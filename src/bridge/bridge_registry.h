#ifndef BRIDGE_REGISTRY_H
#define BRIDGE_REGISTRY_H

#include <memory>
#include <mutex>

#include "utils/singleton.h"

// Forward declarations
class Bridge;

class BridgeRegistry
{
public:
	BridgeRegistry();

public:
	std::shared_ptr<Bridge> operator()();

private:
	void Add(std::shared_ptr<Bridge> bridge);

private:
	std::mutex m_BridgeMutex;
	std::shared_ptr<Bridge> m_Bridge{ nullptr };

private:
	friend class Bridge;
};

struct BridgeRegistrySingleton : public Singleton<BridgeRegistry, BridgeRegistrySingleton>
{
};

#endif // BRIDGE_REGISTRY_H

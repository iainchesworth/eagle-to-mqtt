#ifndef DEVICE_REGISTRY_H
#define DEVICE_REGISTRY_H

#include <memory>
#include <unordered_map>

#include "metering/device_factory.h"
#include "metering/devices/eagle.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"

class DeviceRegistry
{
	using DeviceRegistryMap = std::unordered_map<EthernetMacId, std::shared_ptr<Eagle>, EthernetMacId::EthernetMacId_Hasher>;

public:
	static DeviceRegistry& Get();

public:
	void Add(const EthernetMacId device_ethernet_mac_id, std::shared_ptr<Eagle> device);
	std::shared_ptr<Eagle> Find(const EthernetMacId device_ethernet_mac_id);

public:
	DeviceRegistryMap::const_iterator begin() { return m_Registry.begin(); }
	DeviceRegistryMap::const_iterator end() { return m_Registry.end(); }

private:
	DeviceRegistry();
	~DeviceRegistry() = default;
	DeviceRegistry(const DeviceRegistry&) = delete;
	DeviceRegistry& operator=(const DeviceRegistry&) = delete;

private:
	DeviceRegistryMap m_Registry;
};

template<class DEVICE_TYPE>
std::shared_ptr<Eagle> CheckRegistryAndGetOrCreate(EthernetMacId device_mac_id)
{
	auto device = DeviceRegistry::Get().Find(device_mac_id);
	if (!device)
	{
		device = DeviceFactory::CreateDevice<DEVICE_TYPE>();
		DeviceRegistry::Get().Add(device_mac_id, device);
	}

	return device;
}

#endif // DEVICE_REGISTRY_H

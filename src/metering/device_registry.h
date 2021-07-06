#ifndef DEVICE_REGISTRY_H
#define DEVICE_REGISTRY_H

#include <memory>
#include <unordered_map>

#include "metering/device_factory.h"
#include "metering/devices/eagle.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "utils/singleton.h"

class DeviceRegistry
{
	using DeviceRegistryMap = std::unordered_map<EthernetMacId, std::shared_ptr<Eagle>, EthernetMacId::EthernetMacId_Hasher>;

public:
	DeviceRegistry();

public:
	void Add(const EthernetMacId device_ethernet_mac_id, std::shared_ptr<Eagle> device);
	std::shared_ptr<Eagle> Find(const EthernetMacId device_ethernet_mac_id);

public:
	DeviceRegistryMap::const_iterator begin() { return m_Registry.begin(); }
	DeviceRegistryMap::const_iterator end() { return m_Registry.end(); }

private:
	DeviceRegistryMap m_Registry;
};

struct DeviceRegistrySingleton : public Singleton<DeviceRegistry, DeviceRegistrySingleton>
{
};

template<class DEVICE_TYPE>
std::shared_ptr<Eagle> CheckRegistryAndGetOrCreate(EthernetMacId device_mac_id)
{
	auto device = DeviceRegistrySingleton()->Find(device_mac_id);
	if (!device)
	{
		device = DeviceFactory::CreateDevice<DEVICE_TYPE>();
		DeviceRegistrySingleton()->Add(device_mac_id, device);
	}

	return device;
}

#endif // DEVICE_REGISTRY_H

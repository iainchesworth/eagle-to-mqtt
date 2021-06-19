#ifndef DEVICE_REGISTRY_H
#define DEVICE_REGISTRY_H

#include <memory>
#include <unordered_map>

#include "interfaces/ieagle.h"
#include "metering/device_factory.h"
#include "metering/common/ethernet_mac_id.h"

class DeviceRegistry
{
public:
	static DeviceRegistry& Get();

public:
	void Add(const EthernetMacId device_ethernet_mac_id, std::shared_ptr<IEagle> device);
	std::shared_ptr<IEagle> Find(const EthernetMacId device_ethernet_mac_id);

private:
	DeviceRegistry();
	~DeviceRegistry() = default;
	DeviceRegistry(const DeviceRegistry&) = delete;
	DeviceRegistry& operator=(const DeviceRegistry&) = delete;

private:
	std::unordered_map<EthernetMacId, std::shared_ptr<IEagle>, EthernetMacId::EthernetMacId_Hasher> m_Registry;
};

template<class DEVICE_TYPE>
std::shared_ptr<IEagle> CheckRegistryAndGetOrCreate(EthernetMacId device_mac_id)
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

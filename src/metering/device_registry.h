#ifndef DEVICE_REGISTRY_H
#define DEVICE_REGISTRY_H

#include <boost/log/trivial.hpp>

#include <memory>
#include <unordered_map>

#include "exceptions/duplicate_device_insertion.h"
#include "interfaces/idevice.h"
#include "metering/device_factory.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "utils/singleton.h"

class DeviceRegistry
{
	using device_key = EthernetMacId;
	using device_hash = EthernetMacId::EthernetMacId_Hasher;
	using device_registry = std::unordered_map<device_key, std::shared_ptr<IDevice>, device_hash>;

public:
	DeviceRegistry();

public:
    template<typename DEVICE_TYPE>
    std::shared_ptr<IDevice> GetOrCreate(const EthernetMacId& device_ethernet_mac_id)
    {
        if (auto device = GetExisting(device_ethernet_mac_id); nullptr == device)
        {
			BOOST_LOG_TRIVIAL(debug) << L"No existing device with matching Ethernet MAC id...creating a new one";
            return CreateNew<DEVICE_TYPE>(device_ethernet_mac_id);
        }
        else
        {
			BOOST_LOG_TRIVIAL(debug) << L"Existing device with matching Ethernet MAC id";
            return device;
        }
    }

public:
	std::shared_ptr<IDevice> GetExisting(const EthernetMacId& device_ethernet_mac_id) const
	{
		if (auto it = m_Registry.find(device_ethernet_mac_id); m_Registry.end() == it)
		{
			BOOST_LOG_TRIVIAL(trace) << L"Failed to find device with matching Ethernet MAC id";
			return nullptr;
		}
		else
		{
			BOOST_LOG_TRIVIAL(trace) << L"Found device with matching Ethernet MAC id";
		    return it->second;
		}
	}

public:
	template<typename DEVICE_TYPE>
	std::shared_ptr<IDevice> CreateNew(const EthernetMacId& device_ethernet_mac_id)
	{
		try
		{
			if (auto result = m_Registry.insert(std::make_pair(device_ethernet_mac_id, DeviceFactory::CreateDevice<DEVICE_TYPE>())); !result.second)
			{
				BOOST_LOG_TRIVIAL(warning) << L"Attempted to add multiple devices with the same Ethernet MAC address";
				throw DuplicateDeviceInsertion();
			}
			else
			{
				return GetExisting(device_ethernet_mac_id);
			}
		}
		catch (const std::exception& ex)
		{
			BOOST_LOG_TRIVIAL(warning) << L"Exception occurred: " << ex.what();
			throw;
		}
	}

public:
    device_registry::iterator begin() { return m_Registry.begin(); }
    device_registry::iterator end() { return m_Registry.end(); }

private:
    device_registry m_Registry;
};

struct DeviceRegistrySingleton : public Singleton<DeviceRegistry, DeviceRegistrySingleton>
{
};

#endif // DEVICE_REGISTRY_H

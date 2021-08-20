#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <stdexcept>

#include "metering/device_registry.h"
#include "metering/devices/fronius/symo.h"

#include "test_tools/test_tools_solarapi_generator.h"

BOOST_AUTO_TEST_SUITE(Symo_DataModel);

BOOST_AUTO_TEST_CASE(Test_SolarApi_PowerFlow)
{
	using namespace test_tools;

	try
	{
		auto base_device = DeviceRegistrySingleton()->GetOrCreate<Symo>(EthernetMacId("0x77F8ED465CAD"));
		
		{
			std::stringstream raw_payload;
			
			raw_payload << SolarApi_Generator(SolarApi_Generator::SolarApiVersions::FroniusNonHybrid).Generate_CurrentData_PowerFlow();

			boost::property_tree::ptree payload;
			boost::property_tree::read_json(raw_payload, payload);
			base_device->ProcessPayload(payload);
		}

		// Deducing which overload to use (const vs. non-const) is based on the const'ness of *this.
		const auto symo_device = std::dynamic_pointer_cast<const Symo>(base_device);

		BOOST_TEST(symo_device->EnergyProduction().Inverters.size() == 4);

		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(1).Today.ValueIn<WattHours>() == 1393.2000732421875l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(1).Year.ValueIn<WattHours>() == 322593.5l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(1).AllTime.ValueIn<WattHours>() == 1734796.125l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(1).InstantaneousGeneration.ValueIn<Watts>() == 88.0f);

		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(2).Today.ValueIn<WattHours>() == 1618.5l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(2).Year.ValueIn<WattHours>() == 385172.09375l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(2).AllTime.ValueIn<WattHours>() == 3026782.0l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(2).InstantaneousGeneration.ValueIn<Watts>() == 104.0f);

		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(3).Today.ValueIn<WattHours>() == 1695.800048828125l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(3).Year.ValueIn<WattHours>() == 399904.09375l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(3).AllTime.ValueIn<WattHours>() == 3160499.75l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(3).InstantaneousGeneration.ValueIn<Watts>() == 109.0f);

		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(55).Today.ValueIn<WattHours>() == 1699.0l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(55).Year.ValueIn<WattHours>() == 403993.21875l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(55).AllTime.ValueIn<WattHours>() == 3275219.75l);
		BOOST_TEST(symo_device->EnergyProduction().Inverters.at(55).InstantaneousGeneration.ValueIn<Watts>() == 109.0f);

		BOOST_TEST(symo_device->EnergyProduction().Site.Today.ValueIn<WattHours>() == 6406.5001220703125l);
		BOOST_TEST(symo_device->EnergyProduction().Site.Year.ValueIn<WattHours>() == 1511662.90625l);
		BOOST_TEST(symo_device->EnergyProduction().Site.AllTime.ValueIn<WattHours>() == 11197297.625l);
		BOOST_TEST(symo_device->EnergyProduction().Site.InstantaneousGeneration.ValueIn<Watts>() == 410.0f);

	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

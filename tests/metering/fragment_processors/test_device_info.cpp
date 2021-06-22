#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/device_info.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<DeviceInfo>
 <DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
 <InstallCode>0xFFFFFFFFFFFFFFFF</InstallCode>
 <LinkKey>0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF</LinkKey>
 <FWVersion>{string}</FWVersion>
 <HWVersion>{string}</HWVersion>
 <ImageType>0xFFFF</ImageType>
 <Manufacturer>{string}</Manufacturer>
 <ModelId>{string}</ModelId>
 <DateCode>{string}</DateCode>
</DeviceInfo>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<DeviceInfo>
 <DeviceMacId>0xd8d5b9000000b200</DeviceMacId>
 <InstallCode>0xcc15a871ce590351</InstallCode>
 <LinkKey>0xe13e7838b6322f2fca2dcd9c4cf205d8</LinkKey>
 <FWVersion>2.1.6 (9463)</FWVersion>
 <HWVersion>1.3.4</HWVersion>
 <ImageType>0x2101</ImageType>
 <Manufacturer>Rainforest Automation, Inc.</Manufacturer>
 <ModelId>Z114-EAGLE3</ModelId>
 <DateCode>2017040529021003</DateCode>
 <Protocol>Zigbee</Protocol>
</DeviceInfo>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_DeviceInfo)
{
	static const std::string V1_HEADER = "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">";
	static const std::string V2_HEADER = "<?xml version=\"1.0\"?><rainforest timestamp=\"0000000000s\" version=\"2.0\" macId=\"0xffffffffffff\">";

	static const std::string V1_BODY = 
		"<DeviceInfo>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<InstallCode>0xFFFFFFFFFFFFFFFF</InstallCode>"
		"<LinkKey>0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF</LinkKey>"
		"<FWVersion>{string}</FWVersion>"
		"<HWVersion>{string}</HWVersion>"
		"<ImageType>0xFFFF</ImageType>"
		"<Manufacturer>{string}</Manufacturer>"
		"<ModelId>{string}</ModelId>"
		"<DateCode>{string}{string}</DateCode>"
		"</DeviceInfo>";
	static const std::string V2_BODY = 
		"<DeviceInfo>"
		"<DeviceMacId>0xd8d5b9000000b200</DeviceMacId>"
		"<InstallCode>0xcc15a871ce590351</InstallCode>"
		"<LinkKey>0xe13e7838b6322f2fca2dcd9c4cf205d8</LinkKey>"
		"<FWVersion>2.1.6 (9463)</FWVersion>"
		"<HWVersion>1.3.4</HWVersion>"
		"<ImageType>0x2101</ImageType>"
		"<Manufacturer>Rainforest Automation, Inc.</Manufacturer>"
		"<ModelId>Z114-EAGLE3</ModelId>"
		"<DateCode>2017040529021003</DateCode>"
		"<Protocol>Zigbee</Protocol>"
		"</DeviceInfo>";

	static const std::string FOOTER = "</rainforest>";

	boost::property_tree::ptree v1_deviceinfo, v2_deviceinfo;
	std::stringstream v1_iss, v2_iss;

	v1_iss << V1_HEADER << V1_BODY << FOOTER;
	v2_iss << V2_HEADER << V2_BODY << FOOTER;

	boost::property_tree::read_xml(v1_iss, v1_deviceinfo);
	boost::property_tree::read_xml(v2_iss, v2_deviceinfo);

	try
	{
		DeviceInfo di_v1(v1_deviceinfo.get_child("rainforest.DeviceInfo"));
		DeviceInfo di_v2(v2_deviceinfo.get_child("rainforest.DeviceInfo"));

		BOOST_TEST(di_v1.DeviceMacId() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(di_v1.FirmwareVersion() == std::string("{string}"));
		BOOST_TEST(di_v1.HardwareVersion() == std::string("{string}"));
		BOOST_TEST(di_v1.ModelId() == std::string("{string}"));
		BOOST_TEST(di_v1.ManufactureDate() == std::string("{string}"));
		BOOST_TEST(di_v1.LotNumber() == std::string("{string}"));

		BOOST_TEST(di_v2.DeviceMacId() == ZigBeeMacId("0xd8d5b9000000b200"));
		BOOST_TEST(di_v2.FirmwareVersion() == std::string("2.1.6 (9463)"));
		BOOST_TEST(di_v2.HardwareVersion() == std::string("1.3.4"));
		BOOST_TEST(di_v2.ModelId() == std::string("Z114-EAGLE3"));
		BOOST_TEST(di_v2.ManufactureDate() == std::string("20170405"));
		BOOST_TEST(di_v2.LotNumber() == std::string("29021003"));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

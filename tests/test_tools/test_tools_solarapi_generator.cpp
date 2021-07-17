#include <stdexcept>

#include "test_tools/test_tools_solarapi_generator.h"

test_tools::SolarApi_Generator::SolarApi_Generator(SolarApiVersions version) :
	m_Version(version)
{
}

std::string test_tools::SolarApi_Generator::Generate_CurrentData_Inverter() const
{
	static const std::string PAYLOAD_CURRENTDATA_INVERTER =
    "{"
        "\"Body\" : {"
           "\"DAY_ENERGY\" : {"
              "\"Unit\" : \"Wh\","
              "\"Values\" : {"
                  "\"1\" : 14868,"
                  "\"2\" : 12345,"
                  "\"3\" : 54321"
              "}"
           "},"
           "\"PAC\" : {"
              "\"Unit\" : \"W\","
              "\"Values\" : {"
                  "\"1\" : 0,"
                  "\"2\" : 0,"
                  "\"3\" : 0"
              "}"
           "},"
           "\"TOTAL_ENERGY\" : {"
              "\"Unit\" : \"kWh\","
              "\"Values\" : {"
                  "\"1\" : 27803902,"
                  "\"2\" : 12345678,"
                  "\"3\" : 43214321"
              "}"
           "},"
           "\"YEAR_ENERGY\" : {"
              "\"Unit\" : \"kW\","
              "\"Values\" : {"
                  "\"1\" : 6692366,"
                  "\"2\" : 1234567,"
                  "\"3\" : 7654321"
              "}"
           "}"
        "},"
        "\"Head\" : {"
           "\"RequestArguments\" : {"
              "\"Query\" : \"Inverter\","
              "\"Scope\" : \"System\""
           "},"
           "\"Status\" : {"
              "\"Code\" : 0,"
              "\"Reason\" : \"\","
              "\"UserMessage\" : \"\""
           "},"
           "\"Timestamp\" : \"2021-07-14T17:11:58+10:00\""
        "}"
    "}";

	switch (m_Version)
	{
	case SolarApiVersions::V1: 
		return PAYLOAD_CURRENTDATA_INVERTER;

	case SolarApiVersions::V0:
	case SolarApiVersions::V2:
	default:
		throw std::runtime_error("Generate_CurrentData_Inverter(): Invalid version present in the SOLAR API Generator test tool");
	}
}

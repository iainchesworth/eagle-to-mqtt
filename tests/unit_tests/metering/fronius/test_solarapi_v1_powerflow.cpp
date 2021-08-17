#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>

#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"

#include "test_tools/test_tools_solarapi_generator.h"

BOOST_AUTO_TEST_SUITE(SolarAPI_v1);

BOOST_AUTO_TEST_CASE(Test_PowerFlow)
{
    using namespace test_tools;

    std::stringstream hybrid{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::FroniusHybrid).Generate_CurrentData_PowerFlow() };
    std::stringstream nonhybrid{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::FroniusNonHybrid).Generate_CurrentData_PowerFlow() };
    std::stringstream gen24{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::GEN24_Primo).Generate_CurrentData_PowerFlow() };

    boost::property_tree::ptree hybrid_inverter, nonhybrid_inverter, gen24_inverter;
    boost::property_tree::read_json(hybrid, hybrid_inverter);
    boost::property_tree::read_json(nonhybrid, nonhybrid_inverter);
    boost::property_tree::read_json(gen24, gen24_inverter);

    try
    {
        SolarApi_CurrentData_PowerFlow sacdpf_hybrid(hybrid_inverter);
        SolarApi_CurrentData_PowerFlow sacdpf_nonhybrid(nonhybrid_inverter);
        SolarApi_CurrentData_PowerFlow sacdpf_gen24(gen24_inverter);
    }
    catch (const std::exception& ex)
    {
        BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
    }
}

BOOST_AUTO_TEST_SUITE_END();

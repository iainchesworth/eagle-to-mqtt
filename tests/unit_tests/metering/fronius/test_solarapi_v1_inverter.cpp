#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>

#include "metering/devices/fronius/messages/solarapi_currentdata_inverter.h"

#include "test_tools/test_tools_solarapi_generator.h"

BOOST_AUTO_TEST_SUITE(SolarAPI_v1);

BOOST_AUTO_TEST_CASE(Test_Inverter, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Energy value testing (floating-point)
{
    using namespace test_tools;

    std::stringstream v1{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::V1).Generate_CurrentData_Inverter() };

    boost::property_tree::ptree v1_inverter;
    boost::property_tree::read_json(v1, v1_inverter);

    try
    {
        SolarApi_CurrentData_Inverter sacdi_v1(v1_inverter);

        BOOST_TEST(sacdi_v1.Power_AC().Units == UnitsOfMeasure(UnitsOfMeasure::Units::Watts));
        BOOST_TEST(3 == sacdi_v1.Power_AC().Values.size());
        BOOST_TEST(1 == sacdi_v1.Power_AC().Values[0].first);
        BOOST_TEST(0 == sacdi_v1.Power_AC().Values[0].second);
        BOOST_TEST(2 == sacdi_v1.Power_AC().Values[1].first);
        BOOST_TEST(0 == sacdi_v1.Power_AC().Values[1].second);
        BOOST_TEST(3 == sacdi_v1.Power_AC().Values[2].first);
        BOOST_TEST(0 == sacdi_v1.Power_AC().Values[2].second);

        BOOST_TEST(sacdi_v1.GeneratedEnergy_Day().Units == UnitsOfMeasure(UnitsOfMeasure::Units::WattHours));
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_Day().Values.size());
        BOOST_TEST(1 == sacdi_v1.GeneratedEnergy_Day().Values[0].first);
        BOOST_TEST(14868.0f == sacdi_v1.GeneratedEnergy_Day().Values[0].second);
        BOOST_TEST(2 == sacdi_v1.GeneratedEnergy_Day().Values[1].first);
        BOOST_TEST(12345.0f == sacdi_v1.GeneratedEnergy_Day().Values[1].second);
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_Day().Values[2].first);
        BOOST_TEST(54321.0f == sacdi_v1.GeneratedEnergy_Day().Values[2].second);

        BOOST_TEST(sacdi_v1.GeneratedEnergy_Year().Units == UnitsOfMeasure(UnitsOfMeasure::Units::Kilowatts));
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_Year().Values.size());
        BOOST_TEST(1 == sacdi_v1.GeneratedEnergy_Year().Values[0].first);
        BOOST_TEST(6692366.0f == sacdi_v1.GeneratedEnergy_Year().Values[0].second);
        BOOST_TEST(2 == sacdi_v1.GeneratedEnergy_Year().Values[1].first);
        BOOST_TEST(1234567.0f == sacdi_v1.GeneratedEnergy_Year().Values[1].second);
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_Year().Values[2].first);
        BOOST_TEST(7654321.0f == sacdi_v1.GeneratedEnergy_Year().Values[2].second);

        BOOST_TEST(sacdi_v1.GeneratedEnergy_AllTime().Units == UnitsOfMeasure(UnitsOfMeasure::Units::KilowattHours));
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_AllTime().Values.size());
        BOOST_TEST(1 == sacdi_v1.GeneratedEnergy_AllTime().Values[0].first);
        BOOST_TEST(27803902.0f == sacdi_v1.GeneratedEnergy_AllTime().Values[0].second);
        BOOST_TEST(2 == sacdi_v1.GeneratedEnergy_AllTime().Values[1].first);
        BOOST_TEST(12345678.0f == sacdi_v1.GeneratedEnergy_AllTime().Values[1].second);
        BOOST_TEST(3 == sacdi_v1.GeneratedEnergy_AllTime().Values[2].first);
        BOOST_TEST(43214321.0f == sacdi_v1.GeneratedEnergy_AllTime().Values[2].second);
    }
    catch (const std::exception& ex)
    {
        BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
    }
}

BOOST_AUTO_TEST_SUITE_END();

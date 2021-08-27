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

    std::stringstream hybrid{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::FroniusHybrid).Generate_CurrentData_Inverter() };
    std::stringstream nonhybrid{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::FroniusNonHybrid).Generate_CurrentData_Inverter() };
    std::stringstream gen24{ SolarApi_Generator(SolarApi_Generator::SolarApiVersions::GEN24_Primo).Generate_CurrentData_Inverter() };

    boost::property_tree::ptree hybrid_inverter, nonhybrid_inverter, gen24_inverter;
    boost::property_tree::read_json(nonhybrid, nonhybrid_inverter);

    try
    {
        SolarApi_CurrentData_Inverter sacdi_nonhybrid(nonhybrid_inverter);
        
        BOOST_TEST(3 == sacdi_nonhybrid.CurrentData().size());
        
        ///FIXME BOOST_TEST(sacdi_nonhybrid.CurrentData().Power_AC().Values.Units == UnitsOfMeasure(UnitsOfMeasure::Units::Watts));        
        ///FIXME BOOST_TEST(sacdi_nonhybrid.GeneratedEnergy_Day().Units == UnitsOfMeasure(UnitsOfMeasure::Units::WattHours));       
        ///FIXME BOOST_TEST(sacdi_nonhybrid.GeneratedEnergy_Year().Units == UnitsOfMeasure(UnitsOfMeasure::Units::Kilowatts));        
        ///FIXME BOOST_TEST(sacdi_nonhybrid.GeneratedEnergy_AllTime().Units == UnitsOfMeasure(UnitsOfMeasure::Units::KilowattHours));
        
        BOOST_TEST(14868.0f == sacdi_nonhybrid.CurrentData().at(1).Today.ValueIn<WattHours>());
        BOOST_TEST(6692366.0f == sacdi_nonhybrid.CurrentData().at(1).Year.ValueIn<WattHours>());
        BOOST_TEST(27803902.0f == sacdi_nonhybrid.CurrentData().at(1).AllTime.ValueIn<WattHours>());
        BOOST_TEST(0 == sacdi_nonhybrid.CurrentData().at(1).InstantaneousGeneration.ValueIn<Watts>());
        BOOST_TEST(12345.0f == sacdi_nonhybrid.CurrentData().at(2).Today.ValueIn<WattHours>());
        BOOST_TEST(1234567.0f == sacdi_nonhybrid.CurrentData().at(2).Year.ValueIn<WattHours>());
        BOOST_TEST(12345678.0f == sacdi_nonhybrid.CurrentData().at(2).AllTime.ValueIn<WattHours>());
        BOOST_TEST(0 == sacdi_nonhybrid.CurrentData().at(2).InstantaneousGeneration.ValueIn<Watts>());
        BOOST_TEST(54321.0f == sacdi_nonhybrid.CurrentData().at(3).Today.ValueIn<WattHours>());
        BOOST_TEST(7654321.0f == sacdi_nonhybrid.CurrentData().at(3).Year.ValueIn<WattHours>());
        BOOST_TEST(43214321.0f == sacdi_nonhybrid.CurrentData().at(3).AllTime.ValueIn<WattHours>());
        BOOST_TEST(0 == sacdi_nonhybrid.CurrentData().at(3).InstantaneousGeneration.ValueIn<Watts>());
    }
    catch (const std::exception& ex)
    {
        BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
    }
}

BOOST_AUTO_TEST_SUITE_END();

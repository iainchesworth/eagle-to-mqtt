#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>

#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"

#include "test_tools/test_tools_solarapi_generator.h"

BOOST_AUTO_TEST_SUITE(SolarAPI_v1);

BOOST_AUTO_TEST_CASE(Test_PowerFlow, *boost::unit_test::tolerance(0.00001)) // Tolerance is for energy prodction testing (floating-point)
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

        BOOST_TEST(sacdpf_hybrid.PowerFlowVersion() == PowerFlowVersions(PowerFlowVersions::Versions::Version12));
        BOOST_TEST(sacdpf_hybrid.LocalSite().Mode() == OperatingModes(OperatingModes::Modes::BiDirectional));
        BOOST_TEST(sacdpf_hybrid.LocalSite().BatteryInStandby().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().BatteryInStandby().value() == false);
        BOOST_TEST(!sacdpf_hybrid.LocalSite().BackupMode().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Grid().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Grid().Measurement().Power == -511.99000000000001l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Grid().Measurement().Direction == GridFlow::FlowMeanings(GridFlow::FlowMeanings::ToGrid));
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Generation().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Generation().Measurement().Power == 5.9900000000000091l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Generation().Measurement().Direction == LoadFlow::FlowMeanings(LoadFlow::FlowMeanings::Producer));
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Battery().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Battery().Measurement().Power == -384.70000000000005l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Battery().Measurement().Direction == ChargeFlow::FlowMeanings(ChargeFlow::FlowMeanings::Charging));
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Production().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Production().Measurement().Power == 941.60000000000002l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().PowerFlow_Production().Measurement().Direction == ProductionFlow::FlowMeanings(ProductionFlow::FlowMeanings::Producing));
        BOOST_TEST(sacdpf_hybrid.LocalSite().SelfConsumption().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().SelfConsumption().value() == 0.0l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().RelativeAutonomy().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().RelativeAutonomy().value() == 100.0l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().MeterLocation() == MeterLocations(MeterLocations::Locations::Grid));
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Day().value().ValueIn<WattHours>() == 6758.0l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Year().value().ValueIn<WattHours>() == 1342638.2000000002l);
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_hybrid.LocalSite().GeneratedEnergy_Total().value().ValueIn<WattHours>() == 7604385.5l);
        BOOST_TEST(sacdpf_hybrid.Inverters().size() == 1);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).Id() == 0);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).DeviceType() == 99);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).InstananeousPower().value().ValueIn<Watts>() == 506.0l);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).StateOfCharge().value() == 55.0l);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).ComponentId() == 0);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).BatteryMode().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).BatteryMode().value() == std::string("normal"));
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Day().value().ValueIn<WattHours>() == 6758.0l);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Year().value().ValueIn<WattHours>() == 1342638.25l);
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_hybrid.Inverters().at(1).GeneratedEnergy_Total().value().ValueIn<WattHours>() == 7604385.5l);

        SolarApi_CurrentData_PowerFlow sacdpf_nonhybrid(nonhybrid_inverter);

        BOOST_TEST(sacdpf_nonhybrid.PowerFlowVersion() == PowerFlowVersions(PowerFlowVersions::Versions::Version12));
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().Mode() == OperatingModes(OperatingModes::Modes::ProduceOnly));
        BOOST_TEST(!sacdpf_nonhybrid.LocalSite().BatteryInStandby().has_value());
        BOOST_TEST(!sacdpf_nonhybrid.LocalSite().BackupMode().has_value());
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Grid().Hardware().IsInstalled() == false);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Grid().Measurement().Power == 0.0l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Grid().Measurement().Direction == GridFlow::FlowMeanings(GridFlow::FlowMeanings::FromGrid));
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Generation().Hardware().IsInstalled() == false);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Generation().Measurement().Power == 0.0l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Generation().Measurement().Direction == LoadFlow::FlowMeanings(LoadFlow::FlowMeanings::Producer));
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Battery().Hardware().IsInstalled() == false);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Battery().Measurement().Power == 0.0l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Battery().Measurement().Direction == ChargeFlow::FlowMeanings(ChargeFlow::FlowMeanings::Discharging));
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Production().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Production().Measurement().Power == 410.0l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().PowerFlow_Production().Measurement().Direction == ProductionFlow::FlowMeanings(ProductionFlow::FlowMeanings::Producing));
        BOOST_TEST(!sacdpf_nonhybrid.LocalSite().SelfConsumption().has_value());
        BOOST_TEST(!sacdpf_nonhybrid.LocalSite().RelativeAutonomy().has_value());
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().MeterLocation() == MeterLocations(MeterLocations::Locations::Unknown));
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Day().value().ValueIn<WattHours>() == 6406.5001220703125l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Year().value().ValueIn<WattHours>() == 1511662.90625l);
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_nonhybrid.LocalSite().GeneratedEnergy_Total().value().ValueIn<WattHours>() == 11197297.625l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().size() == 4);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).Id() == 0);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).DeviceType() == 102);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).InstananeousPower().value().ValueIn<Watts>() == 88.0l);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(1).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).ComponentId() == 0);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(1).BatteryMode().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Day().value().ValueIn<WattHours>() == 1393.2000732421875l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Year().value().ValueIn<WattHours>() == 322593.5l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(1).GeneratedEnergy_Total().value().ValueIn<WattHours>() == 1734796.125l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).Id() == 0);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).DeviceType() == 86);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).InstananeousPower().value().ValueIn<Watts>() == 104.0l);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(2).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).ComponentId() == 0);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(2).BatteryMode().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Day().value().ValueIn<WattHours>() == 1618.5l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Year().value().ValueIn<WattHours>() == 385172.09375l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(2).GeneratedEnergy_Total().value().ValueIn<WattHours>() == 3026782l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).Id() == 0);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).DeviceType() == 106);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).InstananeousPower().value().ValueIn<Watts>() == 109.0l);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(3).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).ComponentId() == 0);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(3).BatteryMode().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Day().value().ValueIn<WattHours>() == 1695.800048828125l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Year().value().ValueIn<WattHours>() == 399904.09375l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(3).GeneratedEnergy_Total().value().ValueIn<WattHours>() == 3160499.75l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).Id() == 0);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).DeviceType() == 224);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).InstananeousPower().value().ValueIn<Watts>() == 109.0l);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(55).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).ComponentId() == 0);
        BOOST_TEST(!sacdpf_nonhybrid.Inverters().at(55).BatteryMode().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Day().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Day().value().ValueIn<WattHours>() == 1699.0l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Year().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Year().value().ValueIn<WattHours>() == 403993.21875l);
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_nonhybrid.Inverters().at(55).GeneratedEnergy_Total().value().ValueIn<WattHours>() == 3275219.75l);

        SolarApi_CurrentData_PowerFlow sacdpf_gen24(gen24_inverter);

        BOOST_TEST(sacdpf_gen24.PowerFlowVersion() == PowerFlowVersions(PowerFlowVersions::Versions::Version12));
        BOOST_TEST(sacdpf_gen24.LocalSite().Mode() == OperatingModes(OperatingModes::Modes::BiDirectional));
        BOOST_TEST(sacdpf_gen24.LocalSite().BatteryInStandby().has_value());
        BOOST_TEST(sacdpf_gen24.LocalSite().BatteryInStandby().value() == false);
        BOOST_TEST(!sacdpf_gen24.LocalSite().BackupMode().has_value());
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Grid().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Grid().Measurement().Power == -497.62l);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Grid().Measurement().Direction == GridFlow::FlowMeanings(GridFlow::FlowMeanings::ToGrid));
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Generation().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Generation().Measurement().Power == -3.3799999999999955l);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Generation().Measurement().Direction == LoadFlow::FlowMeanings(LoadFlow::FlowMeanings::Consumer));
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Battery().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Battery().Measurement().Power == -1006.1868286132812l);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Battery().Measurement().Direction == ChargeFlow::FlowMeanings(ChargeFlow::FlowMeanings::Charging));
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Production().Hardware().IsInstalled() == true);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Production().Measurement().Power == 1547.739990234375l);
        BOOST_TEST(sacdpf_gen24.LocalSite().PowerFlow_Production().Measurement().Direction == ProductionFlow::FlowMeanings(ProductionFlow::FlowMeanings::Producing));
        BOOST_TEST(sacdpf_gen24.LocalSite().SelfConsumption().has_value());
        BOOST_TEST(sacdpf_gen24.LocalSite().SelfConsumption().value() == 0.67465069860279347l);
        BOOST_TEST(sacdpf_gen24.LocalSite().RelativeAutonomy().has_value());
        BOOST_TEST(sacdpf_gen24.LocalSite().RelativeAutonomy().value() == 100.0l);
        BOOST_TEST(sacdpf_gen24.LocalSite().MeterLocation() == MeterLocations(MeterLocations::Locations::Grid));
        BOOST_TEST(!sacdpf_gen24.LocalSite().GeneratedEnergy_Day().has_value());
        BOOST_TEST(!sacdpf_gen24.LocalSite().GeneratedEnergy_Year().has_value());
        BOOST_TEST(!sacdpf_gen24.LocalSite().GeneratedEnergy_Total().has_value());
        BOOST_TEST(sacdpf_gen24.Inverters().size() == 1);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).Id() == 0);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).DeviceType() == 1);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).InstananeousPower().has_value());
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).InstananeousPower().value().ValueIn<Watts>() == 501.0l);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).StateOfCharge().has_value());
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).StateOfCharge().value() == 30.600000381469727l);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).ComponentId() == 0);
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).BatteryMode().has_value());
        BOOST_TEST(sacdpf_gen24.Inverters().at(1).BatteryMode().value() == std::string("normal"));
        BOOST_TEST(!sacdpf_gen24.Inverters().at(1).GeneratedEnergy_Day().has_value());
        BOOST_TEST(!sacdpf_gen24.Inverters().at(1).GeneratedEnergy_Year().has_value());
        BOOST_TEST(!sacdpf_gen24.Inverters().at(1).GeneratedEnergy_Total().has_value());
    }
    catch (const std::exception& ex)
    {
        BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
    }
}

BOOST_AUTO_TEST_SUITE_END();

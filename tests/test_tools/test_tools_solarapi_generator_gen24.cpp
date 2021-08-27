#include "test_tools/test_tools_solarapi_generator.h"

std::string test_tools::SolarApi_Generator::Generate_CurrentData_Inverter_GEN24() const
{
    static const std::string PAYLOAD_CURRENTDATA_INVERTER{ "" };

    return PAYLOAD_CURRENTDATA_INVERTER;
}

std::string test_tools::SolarApi_Generator::Generate_CurrentData_PowerFlow_GEN24() const
{
    static const std::string PAYLOAD_CURRENTDATA_POWERFLOW =
    "{"
        "\"Body\" : {"
            "\"Inverters\" : {"
                "\"1\" : {"
                    "\"Battery_Mode\" : \"normal\","
                    "\"DT\" : 1,"
                    "\"P\" : 501,"
                    "\"SOC\" : 30.600000381469727"
                    "}"
                "},"
            "\"Site\" : {"
                "\"BatteryStandby\" : false ,"
                "\"E_Day\" : null ,"
                "\"E_Total\" : null ,"
                "\"E_Year\" : null ,"
                "\"Meter_Location\" : \"grid\","
                "\"Mode\" : \"bidirectional\","
                "\"P_Akku\" : -1006.1868286132812,"
                "\"P_Grid\" : -497.62,"
                "\"P_Load\" : -3.3799999999999955,"
                "\"P_PV\" : 1547.739990234375 ,"
                "\"rel_Autonomy\" : 100.0,"
                "\"rel_SelfConsumption\" : 0.67465069860279347"
            "},"
            "\"Version\" : \"12\""
        "},"
        "\"Head\" : {"
            "\"RequestArguments\" : {},"
            "\"Status\" : {"
                "\"Code\" : 0,"
                "\"Reason\" : \"\","
                "\"UserMessage\" : \"\""
            "},"
            "\"Timestamp\" : \"2019-08-28T09:43:29+00:00\""
        "}"
    "}";

    return PAYLOAD_CURRENTDATA_POWERFLOW;
}

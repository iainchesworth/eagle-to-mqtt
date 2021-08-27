#ifndef PTREE_TRANSLATORS_H
#define PTREE_TRANSLATORS_H

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <spdlog/spdlog.h>

#include <string>

#include "exceptions/not_implemented.h"
#include "metering/common/energy_value.h"
#include "metering/common/timestamps.h"
#include "metering/devices/fronius/energy_management/akku_energy_measurement.h"
#include "metering/devices/fronius/energy_management/grid_energy_measurement.h"
#include "metering/devices/fronius/energy_management/load_energy_measurement.h"
#include "metering/devices/fronius/energy_management/pv_energy_measurement.h"
#include "metering/devices/fronius/messages_types/battery_modes.h"
#include "metering/devices/fronius/messages_types/meter_locations.h"
#include "metering/devices/fronius/messages_types/operating_modes.h"
#include "metering/devices/fronius/messages_types/percentage.h"

namespace boost::property_tree
{

template<>
struct translator_between<std::string, AkkuEnergyMeasurement>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = AkkuEnergyMeasurement;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract AkkuEnergyMeasurement...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<AkkuEnergyMeasurement>(str);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, BatteryModes>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = BatteryModes;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract BatteryModes...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<BatteryModes>(BatteryModes::FromString(str));
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, GridEnergyMeasurement>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = GridEnergyMeasurement;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract GridEnergyMeasurement...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<GridEnergyMeasurement>(str);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, LoadEnergyMeasurement>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = LoadEnergyMeasurement;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract LoadEnergyMeasurement...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<LoadEnergyMeasurement>(str);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, MeterLocations>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = MeterLocations;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract MeterLocations...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<MeterLocations>(MeterLocations::FromString(str));
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, OperatingModes>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = OperatingModes;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract OperatingModes...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<OperatingModes>(OperatingModes::FromString(str));
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, Percentage>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = Percentage;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			try
			{
				return boost::optional<Percentage>(std::stold(str));
			}
			catch (const std::invalid_argument& ex_ia)
			{
				spdlog::debug("Cannot extract Percentage...string value ({}) provided was invalid", str);
			}
			catch (const std::out_of_range& ex_oor)
			{
				spdlog::debug("Cannot extract Percentage...string value ({}) provided was out of range", str);
			}

			return boost::optional<external_type>(boost::none);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, Power>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = Power;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			try
			{
				return boost::optional<Power>(std::stod(str));
			}
			catch (const std::invalid_argument& ex_ia)
			{
				spdlog::debug("Cannot extract Power...string value ({}) provided was invalid", str);
			}
			catch (const std::out_of_range& ex_oor)
			{
				spdlog::debug("Cannot extract Power...string value ({}) provided was out of range", str);
			}

			return boost::optional<external_type>(boost::none);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, Production>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = Production;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			try
			{
				return boost::optional<Production>(std::stod(str));
			}
			catch (const std::invalid_argument& ex_ia)
			{
				spdlog::debug("Cannot extract Production...string value ({}) provided was invalid", str);
			}
			catch (const std::out_of_range& ex_oor)
			{
				spdlog::debug("Cannot extract Production...string value ({}) provided was out of range", str);
			}

			return boost::optional<external_type>(boost::none);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, PVEnergyMeasurement>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = PVEnergyMeasurement;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract PVEnergyMeasurement...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<PVEnergyMeasurement>(str);
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

template<>
struct translator_between<std::string, UnixTimepoint>
{
	struct type
	{
		using internal_type = std::string;
		using external_type = UnixTimepoint;

		boost::optional<external_type> get_value(const internal_type& str)
		{
			if (str.empty())
			{
				spdlog::debug("Cannot extract UnixTimepoint...zero-length string provided");
				return boost::optional<external_type>(boost::none);
			}

			return boost::optional<UnixTimepoint>(UnixTimepoint::FromRFC3339String(str));
		}

		boost::optional<internal_type> put_value(const external_type& obj)
		{
			throw NotImplemented();
		}
	};
};

} // namespace boost::property_tree

#endif // PTREE_TRANSLATORS_H

#ifndef BATTERY_MODES_H
#define BATTERY_MODES_H

#include <ostream>
#include <string>

class BatteryModes
{
	static const std::string NOT_SPECIFIED;
	static const std::string DISABLED;
	static const std::string NORMAL;
	static const std::string SERVICE;
	static const std::string CHARGEBOOST;
	static const std::string NEARLYDEPLETED;
	static const std::string SUSPENDED;
	static const std::string CALIBRATE;
	static const std::string GRIDSUPPORT;
	static const std::string DEPLETERECOVERY;
	static const std::string NONOPERABLE_VOLTAGE;
	static const std::string NONOPERABLE_TEMPERATURE;
	static const std::string PREHEATING;
	static const std::string STARTUP;
	static const std::string STOPPED_TEMPERATURE;
	static const std::string BATTERYFULL;
	static const std::string UNKNOWN;

public:
	enum class Modes
	{
		NotSpecified,
		Disabled,
		Normal,
		Service,
		ChargeBoost,
		NearlyDepleted,
		Suspended,
		Calibrate,
		GridSupport,
		DepleteRecovery,
		NonOperable_Voltage,
		NonOperable_Temperature,
		PreHeating,
		StartUp,
		Stopped_Temperature,
		BatteryFull,
		Unknown
	};

public:
	BatteryModes();
	explicit BatteryModes(Modes mode);
	explicit BatteryModes(const std::string& mode);

private:
	Modes m_Mode;

public:
	static Modes FromString(const std::string& mode_string);
	static std::string ToString(const Modes mode_type);

public:
	bool operator==(const BatteryModes& battery_mode) const;
	bool operator==(const Modes& mode) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const BatteryModes& battery_mode);
};

#endif // BATTERY_MODES_H

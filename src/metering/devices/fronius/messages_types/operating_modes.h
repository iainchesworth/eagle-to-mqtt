#ifndef OPERATING_MODES_H
#define OPERATING_MODES_H

#include <ostream>
#include <string>

class OperatingModes
{
	static const std::string NOT_SPECIFIED;
	static const std::string PRODUCE_ONLY;
	static const std::string METER;
	static const std::string VAGUE_METER;
	static const std::string BI_DIRECTIONAL;
	static const std::string AC_COUPLED;
	static const std::string UNKNOWN;

public:
	enum class Modes
	{
		NotSpecified,
		ProduceOnly,
		Meter,
		VagueMeter,
		BiDirectional,
		AC_Coupled,
		Unknown
	};

public:
	OperatingModes();
	explicit OperatingModes(Modes mode);
	explicit OperatingModes(const std::string& mode);

private:
	Modes m_Mode;

public:
	static Modes FromString(const std::string& mode_string);
	static std::string ToString(const Modes mode_type);

public:
	bool operator==(const OperatingModes& operating_mode) const;
	bool operator==(const Modes& mode) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const OperatingModes& operating_mode);
};

#endif // OPERATING_MODES_H

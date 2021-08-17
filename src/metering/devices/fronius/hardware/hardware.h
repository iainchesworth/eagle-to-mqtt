#ifndef HARDWARE_H
#define HARDWARE_H

#include <ostream>
#include <string>

class HardwareBase
{
public:
	HardwareBase(bool is_installed);

public:
	bool IsInstalled() const;

protected:
	virtual std::string DeviceType() const = 0;

public:
	friend std::ostream& operator<<(std::ostream& os, const HardwareBase& hardware_base);

private:
	const bool m_IsInstalled;
};

#endif // HARDWARE_H

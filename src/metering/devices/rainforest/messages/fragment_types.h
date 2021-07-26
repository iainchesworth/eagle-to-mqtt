#ifndef FRAGMENT_TYPES_H
#define FRAGMENT_TYPES_H

#include <ostream>
#include <string>

class Fragments
{
	static const std::string NOT_SPECIFIED;
	static const std::string BILLING_PERIOD_LIST;
	static const std::string BLOCK_PRICE_DETAIL;
	static const std::string CONNECTION_STATUS;
	static const std::string CURRENT_SUMMATION;
	static const std::string CURRENT_SUMMATION_DELIVERED;
	static const std::string DEVICE_INFO;
	static const std::string INSTANTANEOUS_DEMAND;
	static const std::string MESSAGE_CLUSTER;
	static const std::string NETWORK_INFO;
	static const std::string PRICE_CLUSTER;
	static const std::string TIME_CLUSTER;
	static const std::string UNKNOWN;

public:
	enum class FragmentTypes
	{
		NotSpecified,
		BillingPeriodList,
		BlockPriceDetail,
		ConnectionStatus,
		CurrentSummation,
		DeviceInfo,
		InstantaneousDemand,
		MessageCluster,
		NetworkInfo,
		PriceCluster,
		TimeCluster,
		Unknown
	};

public:
	Fragments();
	explicit Fragments(FragmentTypes fragment);
	explicit Fragments(const std::string& fragment);

private:
	FragmentTypes m_Fragment;

public:
	static FragmentTypes FromString(const std::string& fragment_string);
	static std::string ToString(const FragmentTypes fragment_type);

public:
	bool operator==(const Fragments& other) const;
	bool operator==(const FragmentTypes& fragment_type) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Fragments& fragment);
};

#endif // FRAGMENT_TYPES_H

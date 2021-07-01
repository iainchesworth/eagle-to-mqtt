#include <stdexcept>

#include "test_tools/test_tools_fragment_generator.h"

const std::string test_tools::FragmentGenerator::HEADER_V1{ "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">" };
const std::string test_tools::FragmentGenerator::HEADER_V2{ "<?xml version=\"1.0\"?><rainforest timestamp=\"0000000000s\" version=\"2.0\" macId=\"0xffffffffffff\">" };
const std::string test_tools::FragmentGenerator::FOOTER{ "</rainforest>" };

test_tools::FragmentGenerator::FragmentGenerator(FragmentVersions version) :
	m_Version(version),
	m_Fragment()
{
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_BillingPeriodList()
{
	static const std::string V2_BILLING_PERIOD_LIST_FRAGMENT =
		"<BillingPeriodList>"
		"<DeviceMacId>0xd8d5b9000000ff7c</DeviceMacId>"
		"<MeterMacId>0x0013500300118175</MeterMacId>"
		"<TimeStamp>0x286d9310</TimeStamp>"
		"<NumberOfPeriods>0x00</NumberOfPeriods>"
		"<CurrentStart>0x28518880</CurrentStart>"
		"<CurrentDuration>0x3983db9</CurrentDuration>"
		"<Protocol>Zigbee</Protocol>"
		"</BillingPeriodList>";

	switch (m_Version)
	{
	case FragmentVersions::V2: m_Fragment.append(V2_BILLING_PERIOD_LIST_FRAGMENT); break;
	case FragmentVersions::V1:
	default:
		throw std::runtime_error("AddFragment_BillingPeriodList(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_BlockPriceDetail()
{
	static const std::string V2_BLOCK_PRICE_DETAIL_FRAGMENT =
		"<BlockPriceDetail>"
		"<DeviceMacId>0xd8d5b9000000ff7c</DeviceMacId>"
		"<MeterMacId>0x0013500300118175</MeterMacId>"
		"<TimeStamp>0x286d4aa3</TimeStamp>"
		"<CurrentStart>0x00000000</CurrentStart>"
		"<CurrentDuration>0x0000</CurrentDuration>"
		"<BlockPeriodConsumption>0x0000000000000000</BlockPeriodConsumption>"
		"<BlockPeriodConsumptionMultiplier>0x00000001</BlockPeriodConsumptionMultiplier>"
		"<BlockPeriodConsumptionDivisor>0x000003e8</BlockPeriodConsumptionDivisor>"
		"<NumberOfBlocks>0x00</NumberOfBlocks>"
		"<Multiplier>0x00000001</Multiplier>"
		"<Divisor>0x00000001</Divisor>"
		"<Currency>0x0348</Currency>"
		"<TrailingDigits>0x00</TrailingDigits>"
		"<Protocol>Zigbee</Protocol>"
		"</BlockPriceDetail>";

	switch (m_Version)
	{
	case FragmentVersions::V2: m_Fragment.append(V2_BLOCK_PRICE_DETAIL_FRAGMENT); break;
	case FragmentVersions::V1:
	default:
		throw std::runtime_error("AddFragment_BlockPriceDetail(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_ConnectionStatus()
{
	static const std::string V2_CONNECTION_STATUS_FRAGMENT =
		"<ConnectionStatus>"
		"<DeviceMacId>0xd8d5b9000000b200</DeviceMacId>"
		"<MeterMacId>0x000781000081fd0b</MeterMacId>"
		"<Status>Authenticating: Success</Status>"
		"<ExtPanId>0x000781000081fd0b</ExtPanId>"
		"<Channel>14</Channel>"
		"<ShortAddr>0xd291</ShortAddr>"
		"<LinkStrength>0x00</LinkStrength>"
		"<Protocol>Zigbee</Protocol>"
		"</ConnectionStatus>";

	switch (m_Version)
	{
	case FragmentVersions::V2: m_Fragment.append(V2_CONNECTION_STATUS_FRAGMENT); break;
	case FragmentVersions::V1:
	default:
		throw std::runtime_error("AddFragment_ConnectionStatus(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_CurrentSummation()
{
	static const std::string V1_CURRENT_SUMMATION_FRAGMENT =
		"<CurrentSummationDelivered>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<SummationDelivered>0xFFFFFFFF</SummationDelivered>"
		"<SummationReceived>0xFFFFFFFF</SummationReceived>"
		"<Multiplier>0xFFFFFFFF</Multiplier>"
		"<Divisor>0xFFFFFFFF</Divisor>"
		"<DigitsRight>0xFF</DigitsRight>"
		"<DigitsLeft>0xFF</DigitsLeft>"
		"<SuppressLeadingZero>N</SuppressLeadingZero>"
		"</CurrentSummationDelivered>";
	static const std::string V2_CURRENT_SUMMATION_FRAGMENT =
		"<CurrentSummation>"
		"<DeviceMacId>0xd8d5b9000000af85</DeviceMacId>"
		"<MeterMacId>0xd8d5b900000021a7</MeterMacId>"
		"<TimeStamp>0x20acaec0</TimeStamp>"
		"<SummationDelivered>0x000000000001f81f</SummationDelivered>"
		"<SummationReceived>0x0000000000000000</SummationReceived>"
		"<Multiplier>0x00000001</Multiplier>"
		"<Divisor>0x000003e8</Divisor>"
		"<UnitOfMeasure>0x00</UnitOfMeasure>"
		"<DigitsRight>0x03</DigitsRight>"
		"<DigitsLeft>0x00</DigitsLeft>"
		"<SuppressLeadingZero>Y</SuppressLeadingZero>"
		"<Protocol>Zigbee</Protocol>"
		"</CurrentSummation>";

	switch (m_Version)
	{
	case FragmentVersions::V1: m_Fragment.append(V1_CURRENT_SUMMATION_FRAGMENT); break;
	case FragmentVersions::V2: m_Fragment.append(V2_CURRENT_SUMMATION_FRAGMENT); break;
	default: throw std::runtime_error("AddFragment_CurrentSummation(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_DeviceInfo()
{
	static const std::string V1_DEVICE_INFO_FRAGMENT =
		"<DeviceInfo>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<InstallCode>0xFFFFFFFFFFFFFFFF</InstallCode>"
		"<LinkKey>0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF</LinkKey>"
		"<FWVersion>{string}</FWVersion>"
		"<HWVersion>{string}</HWVersion>"
		"<ImageType>0xFFFF</ImageType>"
		"<Manufacturer>{string}</Manufacturer>"
		"<ModelId>{string}</ModelId>"
		"<DateCode>{string}{string}</DateCode>"
		"</DeviceInfo>";
	static const std::string V2_DEVICE_INFO_FRAGMENT =
		"<DeviceInfo>"
		"<DeviceMacId>0xd8d5b9000000b200</DeviceMacId>"
		"<InstallCode>0xcc15a871ce590351</InstallCode>"
		"<LinkKey>0xe13e7838b6322f2fca2dcd9c4cf205d8</LinkKey>"
		"<FWVersion>2.1.6 (9463)</FWVersion>"
		"<HWVersion>1.3.4</HWVersion>"
		"<ImageType>0x2101</ImageType>"
		"<Manufacturer>Rainforest Automation, Inc.</Manufacturer>"
		"<ModelId>Z114-EAGLE3</ModelId>"
		"<DateCode>2017040529021003</DateCode>"
		"<Protocol>Zigbee</Protocol>"
		"</DeviceInfo>";

	switch (m_Version)
	{
	case FragmentVersions::V1: m_Fragment.append(V1_DEVICE_INFO_FRAGMENT); break;
	case FragmentVersions::V2: m_Fragment.append(V2_DEVICE_INFO_FRAGMENT); break;
	default: throw std::runtime_error("AddFragment_DeviceInfo(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_InstantaneousDemand()
{
	switch (m_Version)
	{
	case FragmentVersions::V1: AddFragment_InstantaneousDemand("0xFFFFFFFF", "0xFFFFFF", "0xFFFFFFFF", "0xFFFFFFFF"); break;
	case FragmentVersions::V2: AddFragment_InstantaneousDemand("0x211cc7a8", "0x000032", "0x00000001", "0x000003e8"); break;
	default: throw std::runtime_error("AddFragment_InstantaneousDemand(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_InstantaneousDemand(const std::string& timestamp, const std::string& demand, const std::string& multipler, const std::string& divisor)
{
	static const std::string V1_INSTANTANEOUS_DEMAND_FRAGMENT_PRE =
		"<InstantaneousDemand>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>";
	static const std::string V1_INSTANTANEOUS_DEMAND_FRAGMENT_POST =
		"<DigitsRight>0xFF</DigitsRight>"
		"<DigitsLeft>0xFF</DigitsLeft>"
		"<SuppressLeadingZero>N</SuppressLeadingZero>"
		"</InstantaneousDemand>";

	static const std::string V2_INSTANTANEOUS_DEMAND_FRAGMENT_PRE =
		"<InstantaneousDemand>"
		"<DeviceMacId>0xd8d5b9000000b74d</DeviceMacId>"
		"<MeterMacId>0x001d230100402d72</MeterMacId>";
	static const std::string V2_INSTANTANEOUS_DEMAND_FRAGMENT_POST =
		"<UnitOfMeasure>0x00</UnitOfMeasure>"
		"<DigitsRight>0x03</DigitsRight>"
		"<DigitsLeft>0x06</DigitsLeft>"
		"<SuppressLeadingZero>Y</SuppressLeadingZero>"
		"<Protocol>Zigbee</Protocol>"
		"</InstantaneousDemand>";

	switch (m_Version)
	{
	case FragmentVersions::V1: 
		m_Fragment.append(V1_INSTANTANEOUS_DEMAND_FRAGMENT_PRE);
		m_Fragment.append("<TimeStamp>").append(timestamp).append("</TimeStamp>");
		m_Fragment.append("<Demand>").append(demand).append("</Demand>");
		m_Fragment.append("<Multiplier>").append(multipler).append("</Multiplier>");
		m_Fragment.append("<Divisor>").append(divisor).append("</Divisor>");
		m_Fragment.append(V1_INSTANTANEOUS_DEMAND_FRAGMENT_POST);
		break;

	case FragmentVersions::V2: 
		m_Fragment.append(V2_INSTANTANEOUS_DEMAND_FRAGMENT_PRE);
		m_Fragment.append("<TimeStamp>").append(timestamp).append("</TimeStamp>");
		m_Fragment.append("<Demand>").append(demand).append("</Demand>");
		m_Fragment.append("<Multiplier>").append(multipler).append("</Multiplier>");
		m_Fragment.append("<Divisor>").append(divisor).append("</Divisor>");
		m_Fragment.append(V2_INSTANTANEOUS_DEMAND_FRAGMENT_POST);
		break;

	default: 
		throw std::runtime_error("AddFragment_InstantaneousDemand(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_MessageCluster()
{
	static const std::string V1_MESSAGE_CLUSTER_FRAGMENT =
		"<MessageCluster>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<Id>0xFFFFFFFF</Id>"
		"<Text>{string}</Text>"
		"<Priority>Critical</Priority>"
		"<ConfirmationRequired>N</ConfirmationRequired>"
		"<Confirmed>Y</Confirmed>"
		"<Queue>Cancel Pending</Queue>"
		"</MessageCluster>";
	static const std::string V2_MESSAGE_CLUSTER_FRAGMENT =
		"<MessageCluster>"
		"<DeviceMacId>0xd8d5b9000000af85</DeviceMacId>"
		"<MeterMacId>0xd8d5b900000021a7</MeterMacId>"
		"<TimeStamp>0x20acaeef</TimeStamp>"
		"<Id>0x00000000</Id>"
		"<Text>Welcome to the program</Text>"
		"<Priority>Low</Priority>"
		"<StartTime>0x20acad0d</StartTime>"
		"<Duration>0xffff</Duration>"
		"<ConfirmationRequired>N</ConfirmationRequired>"
		"<Confirmed>N</Confirmed>"
		"<Queue>Active</Queue>"
		"<Protocol>Zigbee</Protocol>"
		"</MessageCluster>";

	switch (m_Version)
	{
	case FragmentVersions::V1: m_Fragment.append(V1_MESSAGE_CLUSTER_FRAGMENT); break;
	case FragmentVersions::V2: m_Fragment.append(V2_MESSAGE_CLUSTER_FRAGMENT); break;
	default: throw std::runtime_error("AddFragment_MessageCluster(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_NetworkInfo()
{
	static const std::string V1_NETWORK_INFO_FRAGMENT =
		"<NetworkInfo>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<CoordMacId>0xFFFFFFFFFFFFFFFF</CoordMacId>"
		"<Status>Join: Success</Status>"
		"<Description>{string}</Description>"
		"<StatusCode>0xFF</StatusCode>"
		"<ExtPanId>0xFFFFFFFFFFFFFFFF</ExtPanId>"
		"<Channel>00</Channel>"
		"<ShortAddr>0xFFFF</ShortAddr>"
		"<LinkStrength>0xFF</LinkStrength>"
		"</NetworkInfo>";

	switch (m_Version)
	{
	case FragmentVersions::V1: m_Fragment.append(V1_NETWORK_INFO_FRAGMENT); break;
	case FragmentVersions::V2:
	default:
		throw std::runtime_error("AddFragment_NetworkInfo(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

test_tools::FragmentGenerator& test_tools::FragmentGenerator::AddFragment_PriceCluster()
{
	static const std::string V1_PRICE_CLUSTER_FRAGMENT =
		"<PriceCluster>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<Price>0xFFFFFFFF</Price>"
		"<Currency>0x03E7</Currency>"
		"<TrailingDigits>0x02</TrailingDigits>"
		"<Tier>00</Tier>"
		"<TierLabel>{string}</TierLabel>"
		"<RateLabel>{string}</RateLabel>"
		"</PriceCluster>";
	static const std::string V2_PRICE_CLUSTER_FRAGMENT = "<PriceCluster>"
		"<DeviceMacId>0xd8d5b9000000fca8</DeviceMacId>"
		"<MeterMacId>0x00078100005a499f</MeterMacId>"
		"<TimeStamp>0x24e5ffd8</TimeStamp>"
		"<Price>0x00000005</Price>"
		"<Currency>0x0348</Currency>"
		"<TrailingDigits>0x01</TrailingDigits>"
		"<Tier>0x01</Tier>"
		"<StartTime>0x24e60010</StartTime>"
		"<Duration>0xffff</Duration>"
		"<RateLabel>Price1</RateLabel>"
		"<Protocol>Zigbee</Protocol>"
		"</PriceCluster>";

	switch (m_Version)
	{
	case FragmentVersions::V1: m_Fragment.append(V1_PRICE_CLUSTER_FRAGMENT); break;
	case FragmentVersions::V2: m_Fragment.append(V2_PRICE_CLUSTER_FRAGMENT); break;
	default: throw std::runtime_error("AddFragment_PriceCluster(): Invalid version present in the FragmentGenerator test tool");
	}

	return *this;
}

std::stringstream test_tools::FragmentGenerator::Generate() const
{
	std::stringstream payload;

	switch (m_Version)
	{
	case FragmentVersions::V1: payload << HEADER_V1 << std::endl; break;
	case FragmentVersions::V2: payload << HEADER_V2 << std::endl; break;
	default: throw std::runtime_error("Generate(): Invalid version present in the FragmentGenerator test tool");
	}

	payload << m_Fragment << std::endl;
	payload << FOOTER << std::endl;

	return payload;
}

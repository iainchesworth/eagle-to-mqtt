#include "exceptions/missing_rainforest_node.h"

MissingRainforestNode::MissingRainforestNode() :
	std::runtime_error("Payload is malformed; missing root Rainforest node")
{
}

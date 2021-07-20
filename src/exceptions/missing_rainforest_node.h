#ifndef MISSING_RAINFOREST_NODE_H
#define MISSING_RAINFOREST_NODE_H

#include <stdexcept>

class MissingRainforestNode : public std::runtime_error
{
public:
	MissingRainforestNode();
	virtual ~MissingRainforestNode() = default;
};


#endif // MISSING_RAINFOREST_NODE_H

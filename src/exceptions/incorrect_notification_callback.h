#ifndef INCORRECT_NOTIFICATION_CALLBACK_H
#define INCORRECT_NOTIFICATION_CALLBACK_H

#include <stdexcept>
#include <string>

class IncorrectNotificationCallback : public std::runtime_error
{
public:
	explicit IncorrectNotificationCallback(const std::string& notification_callback_type);
};


#endif // MISSING_RAINFOREST_NODE_H

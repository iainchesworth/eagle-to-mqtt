#include "exceptions/incorrect_notification_callback.h"

IncorrectNotificationCallback::IncorrectNotificationCallback(const std::string& notification_callback_type) :
	std::runtime_error("Incorrect notification callback type was registered with notification handler: " + notification_callback_type)
{
}

#ifndef CONNECT_ACTION_LISTENER_H
#define CONNECT_ACTION_LISTENER_H

#include <mqtt/iaction_listener.h>
#include <mqtt/token.h>

class ConnectActionListener : public virtual mqtt::iaction_listener
{
public:
	void on_failure(const mqtt::token& tok) override;
	void on_success(const mqtt::token& tok) override;
};

#endif // CONNECT_ACTION_LISTENER_H

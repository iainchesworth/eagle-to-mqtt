#ifndef APPLICATION_H
#define APPLICATION_H

#include <boost/asio.hpp>

#include "interfaces/ibridge.h"
#include "interfaces/ilistener.h"
#include "interfaces/ipublisher.h"
#include "options/options.h"

class Application
{
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

public:
	explicit Application(boost::asio::io_context& ioc, const Options& options, IBridge& bridge, ListenerSet&& listener_set, PublisherSet&& publisher_set);

public:
	void Run();

private:
	const Options& m_Options;
	IBridge& m_Bridge;
	ListenerSet m_Listeners;
	PublisherSet m_Publishers;

private:
	boost::asio::io_context& m_IOContext;
	boost::asio::signal_set m_Signals;
};

#endif // APPLICATION_H

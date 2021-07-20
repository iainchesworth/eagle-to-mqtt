#include <boost/core/ignore_unused.hpp>
#include <boost/log/trivial.hpp>

#include <signal.h>
#include <stdexcept>

#include "application/application.h"
#include "bridge/bridge.h"

Application::Application(boost::asio::io_context& ioc, const Options& options, IBridge& bridge, ListenerSet&& listener_set, PublisherSet&& publisher_set) :
	m_Options(options),
	m_Bridge(bridge),
	m_Listeners(std::move(listener_set)),
	m_Publishers(std::move(publisher_set)),
	m_IOContext(ioc),
	m_Signals(m_IOContext)
{
	m_Signals.add(SIGINT);
	m_Signals.add(SIGTERM);
#if defined(SIGQUIT)
	m_Signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

	m_Signals.async_wait([this](boost::system::error_code ec, int signo)
		{
			boost::ignore_unused(ec);
			boost::ignore_unused(signo);

			BOOST_LOG_TRIVIAL(info) << L"Application termination request received...stopping.";

			// The server is stopped by canceling all outstanding asynchronous
			// operations. Once all operations have finished the io_context::run()
			// call will exit.

			BOOST_LOG_TRIVIAL(debug) << L"Stopping Bridge async handlers";
			m_Bridge.Stop();

			BOOST_LOG_TRIVIAL(debug) << L"Stopping Listener async handlers";
			for (auto listener : m_Listeners)
			{
				listener->Stop();
			}

			BOOST_LOG_TRIVIAL(debug) << L"Stopping Publisher async handlers";
			for (auto publisher : m_Publishers)
			{
				publisher->Stop();
			}

			BOOST_LOG_TRIVIAL(trace) << L"Stopping ASIO io_context";
			m_IOContext.stop();
		});
}

void Application::Run()
{
	try
	{
		// Start the publishers before the listeners as the listeners will
		// effectively trigger the publishers if/when an update comes in
		// and is successfully processed.

		BOOST_LOG_TRIVIAL(debug) << L"Starting Publisher async handlers";
		for (auto publisher : m_Publishers)
		{
			publisher->Run();
		}

		BOOST_LOG_TRIVIAL(debug) << L"Starting Listener async handlers";
		for (auto listener : m_Listeners)
		{
			listener->Run();
		}

		BOOST_LOG_TRIVIAL(debug) << L"Starting Bridge async handlers";
		m_Bridge.Run();

		BOOST_LOG_TRIVIAL(trace) << L"Starting ASIO io_context";
		m_IOContext.run();
	}
	catch (const std::runtime_error& ex)
	{
		BOOST_LOG_TRIVIAL(error) << L"Exception occurred while running async tasks - what(): " << ex.what();
	}
}

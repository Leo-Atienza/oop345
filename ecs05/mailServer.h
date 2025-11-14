#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H

#include <string>
#include <cstddef>
#include "message.h"
#include "plugin.h"

namespace seneca {

	class MailServer {

		// Variables

		std::string m_userName{};
		std::string m_userAddres{};

		Message* m_inbox{};
		std::size_t m_count{};
		void (*m_observer)(const Message&) {};

		Plugin* m_plugins[2]{};

		void appendMessage_(const Message& stc);

	public:

		// Constructor
		MailServer(const char* name, const char* address);

		// Rule of Five
		~MailServer();
		MailServer(const MailServer& other);
		MailServer& operator=(const MailServer& other);
		MailServer(MailServer&& other) noexcept;
		MailServer& operator=(MailServer&& other) noexcept;

		void receiveMail(Message msg);
		void addPlugin(Plugin* thePlugin);
		void setObserver(void(*observer)(const Message&));

		Message& operator[](std::size_t index);
		std::size_t getInboxSize() const;
		void showInbox() const;

	};

}

#endif
#include "mailServer.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <stdexcept>

using namespace std;
namespace seneca {

	// Constructor
	MailServer::MailServer(const char* name, const char* address)
		: m_userName{ name ? name : "" }, m_userAddres{ address ? address : "" },
		m_inbox{ nullptr }, m_count{ 0 }, m_observer{ nullptr } {

		m_plugins[0] = nullptr;
		m_plugins[1] = nullptr;

	}

	// Rule of Five
	MailServer::~MailServer() {
		delete[] m_inbox;
		m_inbox = nullptr;
	}

	MailServer::MailServer(const MailServer& other)
		: m_userName{ other.m_userName }, m_userAddres{ other.m_userAddres }, 
		m_inbox{ nullptr }, m_count{ other.m_count }, m_observer{ other.m_observer } {

		m_plugins[0] = other.m_plugins[0];
		m_plugins[1] = other.m_plugins[1];

		if (m_count > 0) {

			m_inbox = new Message[m_count];
			for (size_t i = 0; i < m_count; ++i) {

				m_inbox[i] = other.m_inbox[i];

			}

		}
	}

	MailServer& MailServer::operator=(const MailServer& other) {

		if (this != &other) {

			Message* newBox = nullptr;
			if (other.m_count > 0) {
				newBox = new Message[other.m_count];
				for (size_t i = 0; i < other.m_count; ++i) {
					newBox[i] = other.m_inbox[i];
				}
			}
			
			delete[] m_inbox;

			m_inbox = newBox;
			m_count = other.m_count;
			m_userName = other.m_userName;
			m_userAddres = other.m_userAddres;
			m_observer = other.m_observer;
			m_plugins[0] = other.m_plugins[0];
			m_plugins[1] = other.m_plugins[1];

		}
		return *this;

	}

	MailServer::MailServer(MailServer&& other) noexcept 
		: m_userName{ move(other.m_userName) }, m_userAddres{ move(other.m_userAddres) }, m_inbox{ other.m_inbox },
			m_count { other.m_count }, m_observer { other.m_observer } 
		{
			m_plugins[0] = other.m_plugins[0];
			m_plugins[1] = other.m_plugins[1];

			other.m_inbox = nullptr;
			other.m_count = 0;
			other.m_observer = nullptr;
			other.m_plugins[0] = nullptr;
			other.m_plugins[1] = nullptr;
	}

	MailServer& MailServer::operator=(MailServer&& other) noexcept {
		
		if (this != &other) {
			
			delete[] m_inbox;

			m_userName = move(other.m_userName);
			m_userAddres = move(other.m_userAddres);
			m_inbox = other.m_inbox;
			m_count = other.m_count;
			m_observer = other.m_observer;
			m_plugins[0] = other.m_plugins[0];
			m_plugins[1] = other.m_plugins[1];

			other.m_inbox = nullptr;
			other.m_count = 0;
			other.m_observer = nullptr;
			other.m_plugins[0] = nullptr;
			other.m_plugins[1] = nullptr;
			
		}
	}

	void MailServer::appendMessage_(const Message& src) {

		Message* newBox = new Message[m_count + 1];
		for (size_t i = 0; i < m_count; ++i) {
			newBox[i] = m_inbox[i];
		}
		newBox[m_count] = src;
		delete[] m_inbox;
		m_inbox = newBox;
		++m_count;
	}

	void MailServer::receiveMail(Message msg) {

		if (msg.m_toAddress != m_userAddres){
			throw runtime_error("Wrong destination");
		}

		appendMessage_(msg);

		for (int i = 0; i < 2; ++i) {
			if (m_plugins[i]) {
				(*m_plugins[i])(m_inbox[m_count - 1]);
			}
		}

		if (m_observer) {
			m_observer(m_inbox[m_count - 1]);
		}
	}

	void MailServer::addPlugin(Plugin* thePlugin) {

		if (!m_plugins[0]) {
			m_plugins[0] = thePlugin;
		}
		else if (!m_plugins[1]) {
			m_plugins[1] = thePlugin;
		}
	}

	void MailServer::setObserver(void(*observer)(const Message&)) {

		m_observer = observer;

	}

	Message& MailServer::operator[](std::size_t index) {

		if (index >= m_count) {
			string msg = "Index " + to_string(index) + " is out of bounds.";
			throw out_of_range(msg);
		}
		return m_inbox[index];
	}

	std::size_t MailServer::getInboxSize() const {

	}

	void MailServer::showInbox() const {

		for (size_t i = 0; i < m_count; ++i) {

			const Message& m = m_inbox[i];
			string dateOnly = m.m_date;
			size_t sp = dateOnly.find(' ');

			if (sp != string::npos) {
				dateOnly = dateOnly.substr(0, sp);
			}

			cout << setw(20) << right << m.m_fromName << " "
				<< setw(40) << left << m.m_fromAddress
				<< setw(15) << left << dateOnly
				<< "      " << m.m_subject << '\n';

		}
	}
}
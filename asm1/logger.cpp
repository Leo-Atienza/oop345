/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
************************************************************************
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "logger.h"

using namespace std;
namespace seneca {

	void Logger::grow() {

		std::size_t newCap = m_capacity ? (m_capacity * 2) : 8;
		Event* cpy = new Event[newCap];

		if (m_events && m_size) {
			std::copy_n(m_events, m_size, cpy);
		}

		delete[] m_events;
		m_events = cpy;
		m_capacity = newCap;
	}

	Logger::~Logger() {
		delete[] m_events;
	}

	Logger::Logger(Logger&& other) noexcept : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {

		other.m_events = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

	}

	Logger& Logger::operator=(Logger&& other) noexcept {

		if (this != &other) {

			delete[] m_events;

			m_events = other.m_events;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			other.m_events = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	void Logger::addEvent(const Event& evnt) {
		if (m_size == m_capacity) {
			grow();
		}
		m_events[m_size++] = evnt;
	}

	ostream& operator<<(std::ostream& os, const Logger& lgr) {
		for (std::size_t i = 0; i < lgr.m_size; ++i) {
			os << lgr.m_events[i] << "\n";
		}
		return os;
	}

}
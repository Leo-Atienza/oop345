/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
#include <cstddef>
#include <ostream>

namespace seneca {

	class Logger {

		Event* m_events = nullptr;
		std::size_t m_size = 0;
		std::size_t m_capacity = 0;

		void grow() {
			
			std::size_t newCap = m_capacity ? (m_capacity * 2) : 8;
			Event* cpy = new Event[newCap];
			
			for (std::size_t i = 0; i < m_size; ++i) {
				cpy[i] = m_events[i];
			}
			
			delete[] m_events;
			m_events = cpy;
			m_capacity = newCap;
		}

	public:

		// Default Constructor
		Logger() = default;

		// Destructor
		~Logger() {
			delete[] m_events;
		}

		// Copy Constructor (not allowed)
		Logger(const Logger& other) = delete;
		
		// Copy Assignment Operator (not allowed)
		Logger& operator=(const Logger& other) = delete;

		// move
		Logger(Logger&& other) noexcept : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {
			
			other.m_events = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;

		}

		Logger& operator=(Logger&& other) noexcept {
			
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

		void addEvent(const Event& evnt) {
			if (m_size == m_capacity) {
				grow();
			}
			m_events[m_size++] = evnt;
		}

		friend std::ostream& operator<<(std::ostream& os, const Logger& lgr) {
			for (std::size_t i = 0; i < lgr.m_size; ++i) {
				os << lgr.m_events[i] << "\n";
			}
			return os;
		}
	};
}

#endif
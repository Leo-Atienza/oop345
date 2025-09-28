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
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
#include <algorithm>
#include <cstddef>
#include <ostream>

namespace seneca {

	class Logger {

		Event* m_events = nullptr;
		std::size_t m_size = 0;
		std::size_t m_capacity = 0;

		void grow();

	public:

		// Default Constructor
		Logger() = default;

		// Destructor
		~Logger();

		// Copy Constructor (not allowed)
		Logger(const Logger& other) = delete;
		
		// Copy Assignment Operator (not allowed)
		Logger& operator=(const Logger& other) = delete;

		// move
		Logger(Logger&& other) noexcept : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity);

		Logger& operator=(Logger&& other) noexcept;

		void addEvent(const Event& evnt);

		friend std::ostream& operator<<(std::ostream& os, const Logger& lgr);

	};
}

#endif
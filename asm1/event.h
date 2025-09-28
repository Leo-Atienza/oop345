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
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <string>
#include <chrono> // vector
#include <iosfwd>

namespace seneca {

	class Event {
		std::string m_name{};
		std::chrono::nanoseconds m_duration{ std::chrono::nanoseconds {0} };

	public: 

		Event() = default; // default contructor
		Event(const char* name, const std::chrono::nanoseconds& duration);

		friend std::ostream& operator<<(std::ostream& os, const Event& ev);
	};
}

#endif
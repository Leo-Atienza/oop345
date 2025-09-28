/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <chrono>
#include <string>
#include "event.h"

namespace seneca {
	
	class TimeMonitor {
		
		std::string m_name{};
		std::chrono::steady_clock::time_point m_start{};

	public:

		void startEvent(const char* name);
		Event stopEvent();

	};
}

#endif
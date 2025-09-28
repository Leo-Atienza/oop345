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
#include "timeMonitor.h"

using namespace std;
namespace seneca {

	void TimeMonitor::startEvent(const char* name) {
		m_name = name ? name : "";
		m_start = chrono::steady_clock::now();
	}

	Event TimeMonitor::stopEvent() {
		auto end = chrono::steady_clock::now();
		auto time_limit = chrono::duration_cast<std::chrono::nanoseconds>(end - m_start);
		Event evnt(m_name.c_str(), time_limit);
		return evnt;
	}
}
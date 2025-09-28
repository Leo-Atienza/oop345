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
#include "event.h"
#include "settings.h"
#include <iostream>
#include <iomanip>

using namespace std;
namespace seneca {

	int width_for_units(const string& units) {
		
		int flag = 11;

		if (units == "seconds") {
			flag = 2;
		}
		else if (units == "milliseconds") {
			flag = 5;
		}
		else if (units == "microseconds") {
			flag = 8;
		}
		return flag;
	}

	long long value_in_units(const chrono::nanoseconds& ns, const string& units) {
		
		long long val = ns.count();

		if (units == "seconds") {
			val = chrono::duration_cast<chrono::seconds>(ns).count();
		}
		else if (units == "milliseconds") {
			val = chrono::duration_cast<chrono::milliseconds>(ns).count();
		}
		else if (units == "microseconds") {
			val = chrono::duration_cast<chrono::microseconds>(ns).count();
		}
		return val;
	}

	Event::Event(const char* name, const chrono::nanoseconds& duration) {

		if (name) {
			m_name = name;
		}
		else {
			m_name.clear();
		}

		m_duration = duration;
	}

	ostream& operator<<(ostream& os, const Event& ev) {
		
		static int count = 0;
		++count;

		const string& units = g_settings.m_time_units;
		os << setw(2) << count << ": " << setw(40) << ev.m_name << " -> " << setw(width_for_units(units))
			<< value_in_units(ev.m_duration, units) << ' ' << units;

		return os;

	}
}
/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
//
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>

namespace seneca {
	struct Settings {
		bool m_show_all = false;
		bool m_verbose = false;
		std::string m_time_units = "nanoseconds";
	};

	extern Settings g_settings;
}

#endif
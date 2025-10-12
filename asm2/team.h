/***********************************************************************
// OOP345 Assignment 2
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: Oct 10, 2025
************************************************************************
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <string>
#include "character.h"

namespace seneca {

	class Team {

		Character** m_arr{};
		std::size_t m_count{};
		std::string m_name{};

		void clear();

	public:

		Team();
		explicit Team(const char* name);

		Team(const Team& other);
		Team(Team&& other) noexcept;
		Team& operator=(const Team& other);
		Team& operator=(Team&& other) noexcept;
		~Team();

		void addMember(const Character* charac);
		void removeMember(const std::string& name);
		Character* operator[](std::size_t index) const;
		void showMembers() const;

	};
}

#endif
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
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"

namespace seneca {

	class Guild {
		Character** m_arr{};
		std::size_t m_count{};
		std::string m_name{};

		void clear();

	public:

		Guild();
		explicit Guild(const char* name);
		Guild(const Guild& other);
		Guild(Guild&& other) noexcept;
		Guild& operator=(const Guild& other);
		Guild& operator=(Guild&& other) noexcept;
		~Guild();

		void addMember(Character* charac);
		void removeMember(const std::string& name);
		Character* operator[](std::size_t indx) const;
		void showMembers() const;
	};
}

#endif
/***********************************************************************
// OOP345 Assignment 2
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: Oct 10, 2025
************************************************************************
//I declare that this submission is mostly the result of my own work and I copied the code that my professor provided to complete my assignments and also asked chatgpt for help with 1 function. 
//This submitted piece of work has been shared with chatgpt.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include <algorithm>
#include "guild.h"

using namespace std;
namespace seneca {

	Guild::Guild() : m_arr(nullptr), m_count(0u), m_name() {

	}

	Guild::Guild(const char* name) : m_arr(nullptr), m_count(0u), m_name(name ? name : "") {

	}

	Guild::Guild(const Guild& other) : m_arr(nullptr), m_count(0u), m_name(other.m_name) {

		if (other.m_arr != nullptr && other.m_count > 0u) {
			m_arr = new Character * [other.m_count] {};
			
			for (std::size_t i = 0; i < other.m_count; ++i) {
				m_arr[i] = other.m_arr[i];
			}
			m_count = other.m_count;
		}
	}

	Guild::Guild(Guild&& other) noexcept : m_arr(other.m_arr), m_count(other.m_count), m_name(std::move(other.m_name)) {
		
		other.m_arr = nullptr;
		other.m_count = 0u;

	}

	Guild& Guild::operator=(const Guild& other) {

		if (this != &other) {
			clear();
			m_name = other.m_name;

			if (other.m_arr != nullptr && other.m_count > 0u) {
				
				m_arr = new Character * [other.m_count] {};

				for (std::size_t i = 0; i < other.m_count; ++i) {
					m_arr[i] = other.m_arr[i];
				}
				m_count = other.m_count;
			}
		}
		return *this;
	}

	Guild& Guild::operator=(Guild&& other) noexcept {
		
		if (this != &other) {
			clear();
			
			m_arr = other.m_arr;
			m_count = other.m_count;
			m_name = move(other.m_name);
			
			other.m_arr = nullptr;
			other.m_count = 0u;
		}
		return *this;
	}

	Guild::~Guild() {
		clear();
	}

	void Guild::clear() {
		
		delete[] m_arr;
		m_arr = nullptr;
		m_count = 0u;

	}

	void Guild::addMember(Character* c) {

		bool flag = (c != nullptr);

		if (flag) {
			
			bool check = false;
			
			for (size_t i = 0; i < m_count && !check; ++i) {
				if (m_arr[i] != nullptr && m_arr[i]->getName() == c->getName()) {
					check = true;
				}
			}
			flag = !check;
		}

		if (flag) {
			
			Character** temp = new Character * [m_count + 1] {};
			
			for (size_t i = 0; i < m_count; ++i) {
				temp[i] = m_arr[i];
			}

			temp[m_count] = c;
			delete[] m_arr;
			m_arr = temp;
			++m_count;

			int newMax = c->getHealthMax() + 300;
			c->setHealthMax(newMax);
		}
	}

	Character* Guild::operator[](size_t indx) const {

		Character* result = nullptr;

		if (m_arr != nullptr && indx < m_count) {
			result = m_arr[indx];
		}

		return result;
	}

	void Guild::showMembers() const {

		if (m_name.empty()) {
			cout << "No guild." << std::endl;
		}
		else {
			cout << "[Guild] " << m_name << std::endl;

			for (std::size_t i = 0; i < m_count; ++i) {
				
				std::cout << "    " << (i + 1) << ": ";

				if (m_arr[i] != nullptr) {
					std::cout << *m_arr[i] << std::endl;
				}

				else {
					cout << "(null)" << std::endl;
				}
			}
		}
	}

	void Guild::removeMember(const std::string& name) { // asked chatgpt for help
		
		std::size_t idx = m_count;
		Character* target = nullptr;

		if (m_arr != nullptr) {
			for (std::size_t i = 0; i < m_count; ++i) {
				if (m_arr[i] != nullptr && m_arr[i]->getName() == name) {
					idx = i;
					target = m_arr[i];
					break;
				}
			}
		}

		if (idx < m_count) {

			if (target != nullptr) {
				int newMax = target->getHealthMax() - 300;
				target->setHealthMax(newMax);
			}

			const std::size_t newCount = m_count - 1u;
			Character** temp = newCount ? new Character * [newCount] {} : nullptr;

			if (newCount) {

				if (idx > 0) {
					std::copy(m_arr, m_arr + idx, temp);
				}

				if (idx + 1 < m_count) {
					std::copy(m_arr + idx + 1, m_arr + m_count, temp + idx);
				}
			}

			delete[] m_arr;
			m_arr = temp;
			m_count = newCount;
		}
	}
}
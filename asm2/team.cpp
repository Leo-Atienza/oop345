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
#include <iostream>
#include "team.h"

using namespace std;
namespace seneca {

	Team::Team() : m_name() {
		
		m_arr = nullptr;
		m_count = 0u;

	}

	Team::Team(const char* name) : m_name(name ? name : "") {

		m_arr = nullptr;
		m_count = 0u;

	}

	Team::Team(const Team& other) : m_arr(nullptr), m_count(0u), m_name(other.m_name) {

		if (other.m_arr != nullptr && other.m_count > 0u) {

			m_arr = new Character *[other.m_count] {};

			for (std::size_t i = 0; i < other.m_count; ++i) {
					
				if (other.m_arr[i] != nullptr) {
					m_arr[i] = other.m_arr[i]->clone();
				}
				else {
					m_arr[i] = nullptr;
				}
			}
			m_count = other.m_count;
		}
	}

	Team::Team(Team&& other) noexcept : m_arr(other.m_arr), m_count(other.m_count), m_name(std::move(other.m_name)) {
		
		other.m_arr = nullptr;
		other.m_count = 0u;

	}

	Team& Team::operator=(const Team& other) {

		if (this != &other) {

			clear();
			m_name = other.m_name;

			if (other.m_arr != nullptr && other.m_count > 0u) {
				
				m_arr = new Character * [other.m_count] {};

				for (size_t i = 0; i < other.m_count; ++i) {

					if (other.m_arr[i] != nullptr) {
						m_arr[i] = other.m_arr[i]->clone();
					}
					else {
						m_arr[i] = nullptr;
					}
				}
				m_count = other.m_count;
			}
		}
		return *this;
	}

	Team::~Team() {
		clear();
	}

	Team& Team::operator=(Team&& other) noexcept {

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

	void Team::showMembers() const {
		
		if (m_name.empty()) {
			cout << "No team." << endl;
		}
		else {
			cout << "[Team] " << m_name << endl;

			for (size_t i = 0; i < m_count; ++i) {
				cout << "    " << (i + 1) << ": ";
				if (m_arr[i] != nullptr) {
					cout << *m_arr[i] << std::endl;
				}
				else {
					cout << "(null)" << std::endl;
				}
			}
		}
	}

	void Team::clear() {

		if (m_arr != nullptr) {

			for (size_t i = 0; i < m_count; ++i) {
				delete m_arr[i];
				m_arr[i] = nullptr;
			}
			delete[] m_arr;
		}
		m_arr = nullptr;
		m_count = 0u;
	}

	void Team::addMember(const Character* c) {

		bool check = (c != nullptr);

		if (check) {

			bool flag = false;

			for (size_t i = 0; i < m_count && !flag; ++i) {

				if (m_arr[i] != nullptr && m_arr[i]->getName() == c->getName()) {
					flag = true;
				}
			}
			check = !flag;
		}
		if (check) {
			
			Character** temp = new Character * [m_count + 1] {};
			
			for (size_t i = 0; i < m_count;  ++i) {
				temp[i] = m_arr[i];
			}
			temp[m_count] = c->clone();
			delete[] m_arr;
			m_arr = temp;
			++m_count;
		}
	}

	void Team::removeMember(const std::string& name) { // had help from chatgpt
		
		size_t idx = m_count;
		
		if (m_arr != nullptr) {
			for (size_t i = 0; i < m_count; ++i) {
				
				if (m_arr[i] != nullptr && m_arr[i]->getName() == name) {
					idx = i;
					break;
				}
			}
		}

		if (idx < m_count) {
		
			delete m_arr[idx];
			const size_t newCount = m_count - 1u;
			
			Character** tmp = newCount ? new Character * [newCount] {} : nullptr;
			size_t k = 0;
			
			for (size_t i = 0; i < m_count; ++i) {
				if (i != idx) {
					tmp[k++] = m_arr[i];
				}
			}

			delete[] m_arr;
			m_arr = tmp;
			m_count = newCount;
		}
	}

	Character* Team::operator[](size_t indx) const {

		Character* result = nullptr;

		if (m_arr != nullptr && indx < m_count) {
			result = m_arr[indx];
		}
		return result;
	}
}
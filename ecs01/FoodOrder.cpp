#define _CRT_SECURE_NO_WARNINGS
#include "FoodOrder.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

double g_taxrate{};
double g_dailydiscount{};

using namespace std;
namespace seneca {

	/*
		char c_Name[10]{};
		char* c_Desc{};
		double c_Price{};
		bool c_isDailySpecial{};
	
	*/

	// Destructor
	FoodOrder::~FoodOrder() {
		delete[] c_Desc;
	}

	// Copy constructor
	FoodOrder::FoodOrder(const FoodOrder& other) {
		*this = other;
	}

	// Copy assignment operator - NEED TO RECHECK (ASK GPT TO EXPLAIN)
	FoodOrder& FoodOrder::operator=(const FoodOrder& other) { 

		// Check for self assignment
		if (this != &other) {

			// Deep copy
			strncpy(c_Name, other.c_Name, sizeof c_Name - 1);
			c_Name[sizeof c_Name - 1] = '\0';

			// Shallow copy
			c_Price = other.c_Price;
			c_isDailySpecial = other.c_isDailySpecial;

			// Delete old data
			delete[] c_Desc;

			if (other.c_Desc) {
				c_Desc = new char[strlen(other.c_Desc) + 1];
				strcpy(c_Desc, other.c_Desc);
			}
			else {
				c_Desc = nullptr;
			}
		}
		return *this;
	}

	void FoodOrder::read(istream& is) {
		string name, desc, price, status;

		if (is) {
			getline(is, name, ',');
			getline(is, desc, ',');
			getline(is, price, ',');
			getline(is, status);

			if (name.empty()) {
				c_Name[0] = '\0';
				dma(c_Desc, "");
				c_Price = 0.0;
				c_isDailySpecial = false;
			}
			else {

				strncpy(c_Name, name.c_str(), sizeof(c_Name) - 1);
				c_Name[sizeof(c_Name) - 1] = '\0';

				// Deep copy
				dma(c_Desc, desc);

				c_Price = price.empty() ? 0.0 : std::stod(price);
				c_isDailySpecial = !status.empty() && (status[0] == 'Y' || status[0] == 'y');
			}
		}
	}

	void FoodOrder::display() const {
		static unsigned counter{};
		++counter;

		cout << left << setw(2) << counter << ". ";
		if (!c_Name[0]) {
			cout << "No Order\n";
			return;
		}

		const double taxed = c_Price * (1.0 + g_taxrate);

		cout << fixed << setprecision(2)
			<< left << setw(10) << c_Name << "|"
			<< left << setw(25) << (c_Desc ? c_Desc : "") << "|"
			<< left << setw(12) << taxed << "|";

		if (c_isDailySpecial) {
			cout << right << setw(13) << (taxed - g_dailydiscount);
		}
		cout << '\n';
	}

	void FoodOrder::dma(char*& dst, const string& src) {
		delete[] dst;
		dst = new char[src.size() + 1];
		memcpy(dst, src.c_str(), src.size() + 1);
	}

}
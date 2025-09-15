#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>
#include <string>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {

	class FoodOrder {
		char c_Name[10]{};
		char* c_Desc{};
		double c_Price{};
		bool c_isDailySpecial{};

	public:
		// Default constructor
		FoodOrder() = default;
		
		// Destructor
		~FoodOrder();
		
		// Copy constructor
		FoodOrder(const FoodOrder& other);

		// Copy assignment operator
		FoodOrder& operator=(const FoodOrder& other);

		void read(std::istream& in);
		void display() const;

		// Helper for DMA
		void dma(char*& dst, const std::string& src);
	};
}

#endif
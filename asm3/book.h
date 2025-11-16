/***********************************************************************
// OOP345 Assignment 3
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 14, 2025
************************************************************************
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>
#include "mediaItem.h"

namespace seneca {

    class Book : public MediaItem {

        std::string m_author{};
        std::string m_country{};
        double m_price{};

        Book(const std::string& title, const std::string& summary, unsigned short year,
            const std::string& author, const std::string& country, double price);

        static std::string extractToken(std::string& str, char delimiter);

    public:

        void display(std::ostream& out) const override;

        static Book* createItem(const std::string& strBook);

    };
}
#endif
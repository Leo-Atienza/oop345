/***********************************************************************
// OOP345 Assignment 3
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 7, 2025
************************************************************************
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iosfwd>
#include "mediaItem.h"
#include "settings.h"

namespace seneca {

    class Book : public MediaItem {
        
        std::string m_author{};
        std::string m_country{};
        double m_price{};

        Book(const std::string& author, const std::string& title, const std::string& country, unsigned short year,
            double price, const std::string& summary);

        Book() = delete;

    public:
        
        static Book* createItem(const std::string& strBook);
        void display(std::ostream& out) const override;

    };
}
#endif
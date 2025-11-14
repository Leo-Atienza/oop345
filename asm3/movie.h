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
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iosfwd>
#include "mediaItem.h"
#include "settings.h"

namespace seneca {

    class Movie : public MediaItem {

        Movie(const std::string& title, unsigned short year, const std::string& summary);

        Movie() = delete;

    public:

        static Movie* createItem(const std::string& strMovie);
        void display(std::ostream& out) const override;
    };
}
#endif
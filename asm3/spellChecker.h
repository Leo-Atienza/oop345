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
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>

namespace seneca {

    class SpellChecker {

        static const size_t MAX_WORDS = 6;

        std::string m_badWords[MAX_WORDS]{};
        std::string m_goodWords[MAX_WORDS]{};
        size_t m_replacementCount[MAX_WORDS]{};

        void loadSpellingFile(const char* filename);

    public:

        SpellChecker(const char* filename);

        void operator()(std::string& text);

        void showStatistics(std::ostream& out) const;

    };
}
#endif
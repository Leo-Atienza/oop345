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
#include "spellChecker.h"
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
namespace seneca {

    void SpellChecker::loadSpellingFile(const char* filename) {

        ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }

        string line;
        size_t index = 0;

        while (getline(file, line) && index < MAX_WORDS) {

            istringstream iss(line);
            iss >> m_badWords[index] >> m_goodWords[index];

            if (!m_badWords[index].empty() && !m_goodWords[index].empty()) {
                m_replacementCount[index] = 0;
                ++index;
            }
        }
    }

    SpellChecker::SpellChecker(const char* filename) {

        for (size_t i = 0; i < MAX_WORDS; ++i) {
            m_replacementCount[i] = 0;
        }

        loadSpellingFile(filename);
    }

    void SpellChecker::operator()(string& text) {

        for (size_t i = 0; i < MAX_WORDS; ++i) {

            if (!m_badWords[i].empty()) {

                size_t pos = 0;

                while ((pos = text.find(m_badWords[i], pos)) != string::npos) {

                    text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                    pos += m_goodWords[i].length();
                    ++m_replacementCount[i];
                }
            }
        }
    }

    void SpellChecker::showStatistics(ostream& out) const {

        out << "Spellchecker Statistics" << endl;

        for (size_t i = 0; i < MAX_WORDS; ++i) {

            if (!m_badWords[i].empty()) {
                out << left << setw(15) << m_badWords[i]
                    << ": " << m_replacementCount[i] << " replacements" << endl;
            }
        }
    }
}
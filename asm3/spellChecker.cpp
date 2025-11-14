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
#include "spellChecker.h"
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
namespace seneca {

    SpellChecker::SpellChecker(const char* filename) {
        
        ifstream fin(filename);
        
        if (!fin) {
            throw string("Bad file name!");
        }
        
        for (int i = 0; i < 6; ++i) {
            m_badWords[i].clear();
            m_goodWords[i].clear();
            m_counts[i] = 0;
        }
        
        string line;
        int idx = 0;
        
        while (idx < 6 && getline(fin, line)) {
            
            istringstream iss(line);
            string bad, good;
            
            if (iss >> bad >> good) {
                m_badWords[idx] = bad;
                m_goodWords[idx] = good;
                ++idx;
            }
        }
    }

    void SpellChecker::operator()(string& text) {
        
        for (int i = 0; i < 6; ++i) {
            
            const string& from = m_badWords[i];
            const string& to = m_goodWords[i];
            
            if (from.empty()) continue;
            size_t pos = 0;
            
            while ((pos = text.find(from, pos)) != string::npos) {
                text.replace(pos, from.size(), to);
                pos += to.size();
                ++m_counts[i];
            }
        }
    }


    void SpellChecker::showStatistics(std::ostream& out) const {
        
        out << "Spellchecker Statistics\n";
        
        for (int i = 0; i < 6; ++i) {
            if (!m_badWords[i].empty()) {
                
                out << left << setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements\n";
            }
        }
        out << right; 
    }
}
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
#include "movie.h"
#include <iomanip>
#include <stdexcept>

using namespace std;
namespace seneca {

    Movie::Movie(const std::string& title, unsigned short year, const std::string& summary) {

        setTitle(title);
        setYear(year);
        setSummary(summary);
    }

    // Had help from chatgpt
    Movie* Movie::createItem(const std::string& strMovie) {
        
        Movie* result{};

        string rec = strMovie;
        MediaItem::trim(rec);
        
        if (rec.empty() || rec[0] == '#') {
            throw "Not a valid movie.";
        }

        string title, yearStr, summary;
        size_t start = 0, pos = rec.find(',');

        auto take = [&](std::string& out) {

            string tok = rec.substr(start, (pos == string::npos ? rec.size() : pos) - start);
            MediaItem::trim(tok);
            out = tok;
            start = (pos == string::npos) ? rec.size() : pos + 1;
            pos = rec.find(',', start);
        };

        take(title);
        take(yearStr);
        {
            string tok = rec.substr(start);
            MediaItem::trim(tok);
            summary = tok;
        }

        if (title.empty() || yearStr.empty() || summary.empty()) {
            throw "Not a valid movie.";
        }

        unsigned short year{};

        try { 
            year = static_cast<unsigned short>(std::stoi(yearStr)); 
        }
        catch (...) { 
            throw "Not a valid movie."; 
        }

        result = new Movie(title, year, summary);
        return result;
    }

    // Had help from chatgpt
    void Movie::display(ostream& out) const {

        if (g_settings.m_tableView) {
            out << "M | " << left << setfill('.') << setw(50) << getTitle() << " | "
                << right << setfill(' ') << setw(4) << getYear() << " | " << left;

            if (g_settings.m_maxSummaryWidth > -1) {
                
                const auto lim = static_cast<size_t>(g_settings.m_maxSummaryWidth);

                if (getSummary().size() <= lim) out << getSummary();
                else out << getSummary().substr(0, lim - 3) << "...";
            }
            else {
                out << getSummary();
            }
            out << '\n';
        }
        else {

            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "]\n";
            out << setw(getTitle().size() + 7) << setfill('-') << "" << '\n';
            setfill(' ');
            
            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, static_cast<size_t>(g_settings.m_maxSummaryWidth)) << '\n';
                pos += static_cast<size_t>(g_settings.m_maxSummaryWidth);
            }
            
            out << setw(getTitle().size() + 7) << setfill('-') << "" << setfill(' ') << '\n';
        }
    }
}
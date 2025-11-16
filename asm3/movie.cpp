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
#include "movie.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

using namespace std;
namespace seneca {

    Movie::Movie(const string& title, const string& summary, unsigned short year)
        : MediaItem(title, summary, year) {
    }

    void Movie::parseMovieLine(const string& line, string& title,
        unsigned short& year, string& summary) {

        string temp = line;

        size_t pos1 = temp.find(',');
        if (pos1 != string::npos) {
            title = temp.substr(0, pos1);
            temp.erase(0, pos1 + 1);

            size_t pos2 = temp.find(',');
            if (pos2 != string::npos) {
                string yearStr = temp.substr(0, pos2);
                trim(yearStr);
                year = static_cast<unsigned short>(stoi(yearStr));

                summary = temp.substr(pos2 + 1);
            }
        }

        trim(title);
        trim(summary);
    }

    void Movie::display(ostream& out) const {

        if (g_settings.m_tableView) {
            out << "M | ";
            out << left << setfill('.');
            out << setw(50) << this->getTitle() << " | ";
            out << right << setfill(' ');
            out << setw(9) << this->getYear() << " | ";
            out << left;

            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();

            out << endl;
        }
        else {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << setw(this->getTitle().size() + 7) << setfill('-') << "" << '\n';

            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            out << setw(this->getTitle().size() + 7) << setfill('-') << ""
                << setfill(' ') << '\n';
        }
    }

    Movie* Movie::createItem(const string& strMovie) {

        if (strMovie.empty() || strMovie[0] == '#') {
            throw "Not a valid movie.";
        }

        string title, summary;
        unsigned short year = 0;

        parseMovieLine(strMovie, title, year, summary);

        return new Movie(title, summary, year);
    }
}
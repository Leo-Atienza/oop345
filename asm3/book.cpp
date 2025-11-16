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
#include "book.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

using namespace std;
namespace seneca {

    Book::Book(const string& title, const string& summary, unsigned short year,
        const string& author, const string& country, double price)
        : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {
    }

    string Book::extractToken(string& str, char delimiter) {

        size_t pos = str.find(delimiter);
        string token;

        if (pos != string::npos) {
            token = str.substr(0, pos);
            str.erase(0, pos + 1);
        }
        else {
            token = str;
            str.clear();
        }

        trim(token);
        return token;
    }

    void Book::display(ostream& out) const {

        if (g_settings.m_tableView) {
            out << "B | ";
            out << left << setfill('.');
            out << setw(50) << this->getTitle() << " | ";
            out << right << setfill(' ');
            out << setw(2) << this->m_country << " | ";
            out << setw(4) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << setw(this->getTitle().size() + 7) << setfill('-') << "" << '\n';

            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            out << setw(this->getTitle().size() + 7) << setfill('-') << ""
                << setfill(' ') << '\n';
        }
    }

    Book* Book::createItem(const string& strBook) {

        if (strBook.empty() || strBook[0] == '#') {
            throw "Not a valid book.";
        }

        string line = strBook;

        string author = extractToken(line, ',');
        string title = extractToken(line, ',');
        string country = extractToken(line, ',');
        string priceStr = extractToken(line, ',');
        string yearStr = extractToken(line, ',');
        string summary = line;
        trim(summary);

        double price = stod(priceStr);
        unsigned short year = static_cast<unsigned short>(stoi(yearStr));

        return new Book(title, summary, year, author, country, price);
    }
}
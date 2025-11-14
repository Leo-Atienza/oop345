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

#include "book.h"
#include <iomanip>
#include <stdexcept>

using namespace std;
namespace seneca {

    Book::Book(const std::string& author, const std::string& title, const std::string& country, unsigned short year, double price, const std::string& summary) 
        : m_author(author), m_country(country), m_price(price)
    {
        setTitle(title);
        setYear(year);
        setSummary(summary);
    }
    
    // had help from chatgpt
    Book* Book::createItem(const std::string& strBook) {

        Book* result{};

        string rec = strBook;
        MediaItem::trim(rec);
        
        if (rec.empty() || rec[0] == '#') {
            throw "Not a valid book.";
        }

        string author, title, country, priceStr, yearStr, summary;
        size_t start = 0, pos = rec.find(',');

        auto take = [&](std::string& out) {
            
            string tok = rec.substr(start, (pos == string::npos ? rec.size() : pos) - start);
            MediaItem::trim(tok);
            out = tok;
            start = (pos == string::npos) ? rec.size() : pos + 1;
            pos = rec.find(',', start);
        };

        take(author);
        take(title);
        take(country);
        take(priceStr);
        take(yearStr);

        {
            string tok = rec.substr(start);
            MediaItem::trim(tok);
            summary = tok;
        }

        if (author.empty() || title.empty() || country.empty() || priceStr.empty() || yearStr.empty() || summary.empty()) {
            throw "Not a valid book.";
        }

        double price{};
        unsigned short year{};
        
        try {
            price = stod(priceStr);
            year = static_cast<unsigned short>(std::stoi(yearStr));
        }
        catch (...) {
            throw "Not a valid book.";
        }

        result = new Book(author, title, country, year, price, summary);
        return result;
    }

    // Had help from chatgpt
    void Book::display(ostream& out) const {
        
        if (g_settings.m_tableView) {
            
            out << "B | " << left << setfill('.') << setw(50) << getTitle() << " | "
                << right << setfill(' ') << setw(2) << m_country << " | " << setw(4) << getYear() << " | " << left;

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
            out << getTitle() << " [" << getYear() << "] [" << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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
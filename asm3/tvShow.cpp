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
#include "tvShow.h"
#include "settings.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;
namespace seneca {

    TvShow::TvShow(const string& id, const string& title, const string& summary, unsigned short year) : MediaItem(title, summary, year), m_id(id) {
        // nothing inside
    }

    void TvShow::display(ostream& out) const {

        if (g_settings.m_tableView) {
            out << "S | ";
            out << left << setfill('.');
            out << setw(50) << this->getTitle() << " | ";
            out << right << setfill(' ');
            out << setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << setw(this->getTitle().size() + 7) << setfill('-') << "" << '\n';

            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            for (auto& item : m_episodes) {
                out << setfill('0') << right;
                out << "    " << 'S' << setw(2) << item.m_season
                    << 'E' << setw(2) << item.m_numberInSeason << ' ';

                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size()) {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << setw(this->getTitle().size() + 7) << setfill('-') << ""
                << setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const string& strShow) {

        if (strShow.empty() || strShow[0] == '#') {
            throw "Not a valid show.";
        }

        string line = strShow;

        size_t pos = line.find(',');
        string id = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(id);

        pos = line.find(',');
        string title = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(title);

        pos = line.find(',');
        string yearStr = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(yearStr);
        unsigned short year = static_cast<unsigned short>(stoi(yearStr));

        string summary = line;
        trim(summary);

        return new TvShow(id, title, summary, year);
    }

    double TvShow::getEpisodeAverageLength() const {

        if (m_episodes.empty()) {
            return 0.0;
        }

        double totalLength = accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double sum, const TvEpisode& ep) -> double {
                return sum + static_cast<double>(ep.m_length);
            });

        return totalLength / m_episodes.size();
    }

    list<string> TvShow::getLongEpisodes() const {

        list<string> longEpisodes;

        for_each(m_episodes.begin(), m_episodes.end(),
            [&longEpisodes](const TvEpisode& ep) -> void {
                if (ep.m_length >= 3600) {
                    longEpisodes.push_back(ep.m_title.empty() ?
                        "Episode " + to_string(ep.m_numberOverall) : ep.m_title);
                }
            });

        return longEpisodes;
    }
}
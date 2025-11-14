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
#include "tvShow.h"
#include "collection.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <stdexcept>

using namespace std;
namespace seneca {

    TvShow::TvShow(unsigned int id, const std::string& title, unsigned short year, const std::string& summary) : m_id(id) {
        setTitle(title);
        setYear(year);
        setSummary(summary);
    }

    // had help from chatgpt (im stuggling)
    TvShow* TvShow::createItem(const std::string& strShow) {
        
        TvShow* result{};

        string rec = strShow;
        MediaItem::trim(rec);
        
        if (rec.empty() || rec[0] == '#') {
            throw "Not a valid show.";
        }

        string idStr, title, yearStr, summary;
        size_t start = 0, pos = rec.find(',');

        auto take = [&](string& out) {

            string tok = rec.substr(start, (pos == string::npos ? rec.size() : pos) - start);
            MediaItem::trim(tok);
            out = tok;
            start = (pos == string::npos) ? rec.size() : pos + 1;
            pos = rec.find(',', start);
        };

        take(idStr);
        take(title);
        take(yearStr);
        {
            string tok = rec.substr(start);
            MediaItem::trim(tok);
            summary = tok;
        }

        if (idStr.empty() || title.empty() || yearStr.empty() || summary.empty()) {
            throw "Not a valid show.";
        }

        unsigned int id{};
        unsigned short year{};
        try {
            id = static_cast<unsigned int>(stoul(idStr));
            year = static_cast<unsigned short>(stoi(yearStr));
        }
        catch (...) {
            throw "Not a valid show.";
        }

        result = new TvShow(id, title, year, summary);
        return result;
    }

    // Had help from chatgpt (im stuggling)
    void TvShow::addEpisode(Collection& col, const string& strEpisode) {

        string rec = strEpisode;
        MediaItem::trim(rec);
        
        if (rec.empty() || rec[0] == '#') {
            throw "Not a valid episode.";
        }

        string idStr, numOverallStr, seasonStr, numInSeasonStr, airDate, lengthStr, title, summary;
        size_t start = 0, pos = rec.find(',');

        auto take = [&](string& out) {
            string tok = rec.substr(start, (pos == string::npos ? rec.size() : pos) - start);
            MediaItem::trim(tok);
            out = tok;
            start = (pos == string::npos) ? rec.size() : pos + 1;
            pos = rec.find(',', start);
        };

        take(idStr);
        take(numOverallStr);
        take(seasonStr);
        take(numInSeasonStr);
        take(airDate);
        take(lengthStr);
        {
            string tok = rec.substr(start, (pos == string::npos ? rec.size() : pos) - start);
            MediaItem::trim(tok);
            title = tok;
            start = (pos == string::npos) ? rec.size() : pos + 1;
        }
        {
            string tok = rec.substr(start);
            MediaItem::trim(tok);
            summary = tok;
        }

        if (idStr.empty() || numOverallStr.empty() || numInSeasonStr.empty()
            || airDate.empty() || lengthStr.empty() || title.empty() || summary.empty()) {
            throw "Not a valid episode.";
        }

        unsigned int showId{}, length{};
        unsigned short overall{}, season{}, inSeason{};
        try {
            showId = static_cast<unsigned int>(std::stoul(idStr));
            overall = static_cast<unsigned short>(std::stoi(numOverallStr));
            season = seasonStr.empty() ? static_cast<unsigned short>(1)
                : static_cast<unsigned short>(std::stoi(seasonStr));
            inSeason = static_cast<unsigned short>(std::stoi(numInSeasonStr));
            length = static_cast<unsigned int>(std::stoul(lengthStr));
        }
        catch (...) {
            throw "Not a valid episode.";
        }

        for (size_t i = 0; i < col.size(); ++i) {
            auto* base = col[i];
            auto* show = dynamic_cast<TvShow*>(base);
            if (show && show->m_id == showId) {
                TvEpisode ep{};
                ep.m_numberOverall = overall;
                ep.m_season = season == 0 ? 1 : season;
                ep.m_numberInSeason = inSeason;
                ep.m_airDate = airDate;
                ep.m_length = length;
                ep.m_title = title;
                ep.m_summary = summary;
                show->m_episodes.push_back(ep);
                break;
            }
        }
    }

    unsigned int TvShow::getEpisodeAverageLength() const {
        
        unsigned int avg = 0;
        
        if (!m_episodes.empty()) {
            unsigned long long sum = 0;
            for (const auto& e : m_episodes) sum += e.m_length;
            avg = static_cast<unsigned int>(sum / m_episodes.size());
        }
        return avg;
    }

    list<string> TvShow::getLongEpisodes() const {
        
        list<string> out;
        
        for (const auto& e : m_episodes) {
            if (e.m_length >= 3600u) out.push_back(e.m_title);
        }
        return out;
    }
}
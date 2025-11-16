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
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "mediaItem.h"

namespace seneca {

    class TvShow;

    struct TvEpisode {
       
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};

    };

    class TvShow : public MediaItem {

        std::string m_id{};
        std::vector<TvEpisode> m_episodes{};

        TvShow(const std::string& id, const std::string& title,
            const std::string& summary, unsigned short year);

        template<typename T>
        static TvShow* findShowById(T& collection, const std::string& id);

    public:

        const std::string& getId() const { return m_id; }

        void display(std::ostream& out) const override;

        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode);

        void addEpisode(const TvEpisode& episode) { m_episodes.push_back(episode); }

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

    };

    template<typename T>
    TvShow* TvShow::findShowById(T& collection, const std::string& id) {

        for (size_t i = 0; i < collection.size(); ++i) {
            
            TvShow* show = dynamic_cast<TvShow*>(collection[i]);
            
            if (show && show->getId() == id) {
                return show;
            }
        }
        return nullptr;
    }

    template<typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {

        if (strEpisode.empty() || strEpisode[0] == '#') {
            throw "Not a valid episode.";
        }

        std::string line = strEpisode;
        TvEpisode episode{};

        size_t pos = line.find(',');
        std::string showId = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(showId);

        pos = line.find(',');
        episode.m_numberOverall = static_cast<unsigned short>(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);

        pos = line.find(',');
        std::string seasonStr = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(seasonStr);
        episode.m_season = seasonStr.empty() ? 1 : static_cast<unsigned short>(std::stoi(seasonStr));

        pos = line.find(',');
        episode.m_numberInSeason = static_cast<unsigned short>(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);

        pos = line.find(',');
        episode.m_airDate = line.substr(0, pos);
        line.erase(0, pos + 1);
        trim(episode.m_airDate);

        pos = line.find(',');
        episode.m_length = static_cast<unsigned int>(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);

        pos = line.find(',');
        if (pos != std::string::npos) {
            episode.m_title = line.substr(0, pos);
            line.erase(0, pos + 1);
            trim(episode.m_title);

            episode.m_summary = line;
            trim(episode.m_summary);
        }
        else {
            episode.m_title = line;
            trim(episode.m_title);
        }

        TvShow* show = findShowById(col, showId);
        if (show) {
            episode.m_show = show;
            show->addEpisode(episode);
        }
    }
}
#endif
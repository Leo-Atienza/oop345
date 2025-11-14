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
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <string>
#include <vector>
#include <list>
#include <iosfwd>
#include "mediaItem.h"
#include "settings.h"

namespace seneca {

    struct TvEpisode {
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class Collection;

    class TvShow : public MediaItem {
        
        unsigned int m_id{};
        std::vector<TvEpisode>  m_episodes{};

        TvShow(unsigned int id, const std::string& title, unsigned short year, const std::string& summary);

        TvShow() = delete;

    public:

        static TvShow* createItem(const std::string& strShow);
        static void addEpisode(Collection& col, const std::string& strEpisode);

        void display(std::ostream& out) const override;

        unsigned int getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

        unsigned int getId() const { return m_id; }
        const std::vector<TvEpisode>& episodes() const { return m_episodes; }
    };
}
#endif
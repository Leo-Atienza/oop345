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
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "mediaItem.h"

namespace seneca {

    class Collection {

        std::string m_name{};
        std::vector<MediaItem*> m_items{};
        void (*m_observer)(const Collection&, const MediaItem&) = nullptr;

        template<typename Predicate>
        MediaItem* findItem(Predicate pred) const;

    public:

        Collection(const std::string& name);

        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;

        ~Collection();

        const std::string& name() const { return m_name; }
        size_t size() const { return m_items.size(); }
        
        void setObserver(void (*observer)(const Collection&, const MediaItem&));

        Collection& operator+=(MediaItem* item);

        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;

        void removeQuotes();
        void sort(const std::string& field);

        friend std::ostream& operator<<(std::ostream& out, const Collection& col);

    };
    
    template<typename Predicate>
    MediaItem* Collection::findItem(Predicate pred) const {

        auto it = std::find_if(m_items.begin(), m_items.end(), pred);
        return (it != m_items.end()) ? *it : nullptr;
    }

    std::ostream& operator<<(std::ostream& out, const Collection& col);

}
#endif
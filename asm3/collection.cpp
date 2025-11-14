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
#include "collection.h"
#include "mediaItem.h"
#include <algorithm>
#include <stdexcept>

using namespace std;
namespace seneca {

    Collection::~Collection() {
        
        for (auto* p : m_items) {
            delete p;
        }
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) {
        
        if (item) {

            auto it = std::find_if(m_items.begin(), m_items.end(), [](const MediaItem* m) {
                return m != nullptr;
            });
            (void)it;

            bool exists = std::any_of(m_items.begin(), m_items.end(), [t = item->getTitle()](const MediaItem* m) {
                return m && m->getTitle() == t;
            });

            if (exists) {
                delete item;
            }
            else {
                m_items.push_back(item);
                if (m_observer) m_observer(*this, *item);
            }
        }
        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {
        
        if (idx >= m_items.size()) {
            throw out_of_range( string("Bad index [") + to_string(idx) + 
                "]. Collection has [" + to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }


    MediaItem* Collection::operator[](const std::string& title) const {

        auto it = std::find_if(m_items.begin(), m_items.end(), [title](const MediaItem* m) {
            return m && m->getTitle() == title;
        });

        return it == m_items.end() ? nullptr : *it;
    }


    void Collection::removeQuotes() {
        
        for_each(m_items.begin(), m_items.end(), [](MediaItem* m) {
            if (!m) return;
            
            auto t = m->getTitle();
            auto s = m->getSummary();
            
            if (t.size() >= 2 && t.front() == '"' && t.back() == '"')
                t = t.substr(1, t.size() - 2);

            if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
                s = s.substr(1, s.size() - 2);
            
            m->setTitle(t);
            m->setSummary(s);
        });
    }

    void Collection::sort(const string& field) {

        if (field == "year") {
            std::sort(m_items.begin(), m_items.end(), [](const MediaItem* a, const MediaItem* b) {
                return a->getYear() < b->getYear();
            });
        }

        else {
            std::sort(m_items.begin(), m_items.end(), [](const MediaItem* a, const MediaItem* b) {
                return a->getTitle() < b->getTitle();
            });
        }
    }

    ostream& operator<<(ostream& out, const Collection& c) {
        
        for (size_t i = 0; i < c.m_items.size(); ++i) {
            out << *c.m_items[i];
        }
        return out;
    }
}
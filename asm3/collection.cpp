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
#include "collection.h"
#include <algorithm>
#include <stdexcept>

using namespace std;
namespace seneca {

    Collection::Collection(const string& name) : m_name(name) {
    }

    Collection::~Collection() {

        for (auto item : m_items) {
            delete item;
        }
        m_items.clear();
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) {

        if (item != nullptr) {

            bool exists = any_of(m_items.begin(), m_items.end(),
                [item](const MediaItem* existing) {
                    return existing->getTitle() == item->getTitle();
                });

            if (exists) {
                delete item;
            }
            else {
                m_items.push_back(item);

                if (m_observer) {
                    m_observer(*this, *item);
                }
            }
        }

        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {

        if (idx >= m_items.size()) {
            string message = "Bad index [" + to_string(idx) + "]. Collection has ["
                + to_string(m_items.size()) + "] items.";
            throw out_of_range(message);
        }

        return m_items[idx];
    }

    MediaItem* Collection::operator[](const string& title) const {

        auto it = find_if(m_items.begin(), m_items.end(),
            [title](const MediaItem* item) {
                return item->getTitle() == title;
            });

        return (it != m_items.end()) ? *it : nullptr;
    }

    void Collection::removeQuotes() {

        auto removeQuotesFromString = [](string& str) {

            if (!str.empty() && str.front() == '"') {
                str.erase(0, 1);
            }

            if (!str.empty() && str.back() == '"') {
                str.pop_back();
            }
        };

        for_each(m_items.begin(), m_items.end(),
            [removeQuotesFromString](MediaItem* item) {
                string title = item->getTitle();
                string summary = item->getSummary();

                removeQuotesFromString(title);
                removeQuotesFromString(summary);

                item->setTitle(title);
                item->setSummary(summary);
            });
    }

    void Collection::sort(const string& field) {

        if (field == "title") {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) {
                    return a->getTitle() < b->getTitle();
                });
        }
        
        else if (field == "year") {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) {
                    return a->getYear() < b->getYear();
                });
        }
        
        else if (field == "summary") {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) {
                    return a->getSummary() < b->getSummary();
                });
        }
    }

    ostream& operator<<(ostream& out, const Collection& col) {

        for (const auto& item : col.m_items) {
            out << *item;
        }

        return out;
    }
}
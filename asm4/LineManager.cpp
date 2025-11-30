/***********************************************************************
// OOP345 Assignment 4
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 26, 2025
************************************************************************
//I declare that this submission is the result of my own work and I copied the code that my professor provided to complete my assignments and past assignments.
//This submitted piece of work has been shared by making use of ai to help me debug and create helper functions.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "LineManager.h"
#include "Utilities.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>


namespace seneca {

    // Helper to find station by name
    Workstation* LineManager::findStation(const std::string& name,

        const std::vector<Workstation*>& stations) const {
        auto it = std::find_if(stations.begin(), stations.end(),
            [&name](const Workstation* ws) {
                return ws->getItemName() == name;
            });

        return (it != stations.end()) ? *it : nullptr;
    }

    LineManager::LineManager(const std::string& file,

        const std::vector<Workstation*>& stations) {

        std::ifstream fin(file);
        if (!fin) {
            throw std::runtime_error("Unable to open [" + file + "] file.");
        }

        Utilities util;
        util.setDelimiter('|');

        m_activeLine = stations;

        std::vector<Workstation*> nextStations;

        std::string record;

        while (std::getline(fin, record)) {

            size_t pos = 0;
            bool more = true;

            std::string currentName = util.extractToken(record, pos, more);

            Workstation* current = findStation(currentName, stations);

            if (current != nullptr) {

                if (more) {
                    std::string nextName = util.extractToken(record, pos, more);
                    Workstation* next = findStation(nextName, stations);

                    if (next != nullptr) {
                        current->setNextStation(next);
                        nextStations.push_back(next);
                    }
                }
            }
        }

        fin.close();

        auto first = std::find_if(stations.begin(), stations.end(), [&nextStations](const Workstation* ws) {
            return std::find(nextStations.begin(),
                nextStations.end(), ws) == nextStations.end();
            });

        if (first != stations.end()) {
            m_firstStation = *first;
        }
        else {
            throw std::runtime_error("Unable to determine first station.");
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {

        std::vector<Workstation*> reordered;

        reordered.reserve(m_activeLine.size());

        Workstation* current = m_firstStation;

        while (current != nullptr) {

            reordered.push_back(current);
            current = current->getNextStation();
        }

        m_activeLine = std::move(reordered);
    }

    bool LineManager::run(std::ostream& os) {

        static size_t iteration = 0;
        ++iteration;

        os << "Line Manager Iteration: " << iteration << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* ws) { ws->fill(os); });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws) { ws->attemptToMoveOrder(); });

        return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
    }

    void LineManager::display(std::ostream& os) const {

        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&os](const Workstation* ws) { ws->display(os); });
    }
}
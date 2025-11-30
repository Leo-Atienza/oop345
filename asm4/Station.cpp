/***********************************************************************
// OOP345 Assignment 4
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 26, 2025
************************************************************************
// This is my own work but I copied some of the code I made from Assignment 3 for the display function and I also made use of my professor's code.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "Station.h"
#include "Utilities.h"
#include <iomanip>


namespace seneca {

    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& record) {

        m_id = ++id_generator;

        Utilities util;
        size_t pos = 0;
        bool more = true;

        m_itemName = util.extractToken(record, pos, more);

        if (more) {
            m_serialNumber = std::stoi(util.extractToken(record, pos, more));
        }

        if (more) {
            m_quantity = std::stoi(util.extractToken(record, pos, more));
        }

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }

        if (more) {
            m_description = util.extractToken(record, pos, more);
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {

        if (m_quantity > 0) {
            m_quantity--;
        }
    }

    void Station::display(std::ostream& os, bool full) const {

        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
        os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | ";
        os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | ";
            os << m_description;
        }

        os << std::endl;
    }
}
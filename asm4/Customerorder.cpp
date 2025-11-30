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
////////////////////////////////////////////////////////////////
***********************************************************************/
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <stdexcept>


namespace seneca {


    size_t CustomerOrder::m_widthField = 0;

    // Helper (to make deallocation easier)
    void CustomerOrder::deallocateItems() {

        if (m_lstItem != nullptr) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }
            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
        m_cntItem = 0;
    }

    CustomerOrder::CustomerOrder(const std::string& record) {

        Utilities util;
        size_t pos = 0;
        bool more = true;


        m_name = util.extractToken(record, pos, more);


        if (more) {
            m_product = util.extractToken(record, pos, more);
        }


        size_t temp_pos = pos;
        size_t item_count = 0;
        bool temp_more = more;

        while (temp_more) {

            util.extractToken(record, temp_pos, temp_more);
            item_count++;
        }


        m_cntItem = item_count;
        m_lstItem = new Item * [m_cntItem];


        for (size_t i = 0; i < m_cntItem; ++i) {
            std::string itemName = util.extractToken(record, pos, more);
            m_lstItem[i] = new Item(itemName);
        }


        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::runtime_error("----> ERROR: Cannot make copies.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : m_name(std::move(other.m_name)), m_product(std::move(other.m_product)), m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {

        other.m_lstItem = nullptr;
        other.m_cntItem = 0;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {

        if (this != &other) {

            deallocateItems();

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        deallocateItems();
    }

    bool CustomerOrder::isOrderFilled() const {

        bool filled = true;

        for (size_t i = 0; i < m_cntItem && filled; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                filled = false;
            }
        }

        return filled;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {

        bool result = true;

        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName) {
                if (!m_lstItem[i]->m_isFilled) {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {

        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == station.getItemName() &&
                !m_lstItem[i]->m_isFilled) {

                if (station.getQuantity() > 0) {

                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
                else {

                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {

        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; ++i) {

            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";

            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";

            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}
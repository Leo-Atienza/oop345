/***********************************************************************
// OOP345 Assignment 4
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 26, 2025
************************************************************************
// This is my own work, however, I did get help from chatgpt to optimize these helper functions.
// I made this to make everything easier.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "Utilities.h"
#include <algorithm>
#include <stdexcept>


namespace seneca {

    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    // Helper 1
    static std::string trimString(const std::string& str) {

        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");

        if (start == std::string::npos) {
            return "";
        }
        return str.substr(start, end - start + 1);
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

        if (str[next_pos] == m_delimiter) {
            more = false;
            throw std::invalid_argument("ERROR: No token.");
        }


        size_t pos = str.find(m_delimiter, next_pos);

        std::string token;

        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }

        token = trimString(token);

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
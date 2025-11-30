/***********************************************************************
// OOP345 Assignment 4
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: November 26, 2025
************************************************************************
// This is my own work, however, I did get help from chatgpt to optimize these helper functions. 
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {
    
    class Utilities {
        
        size_t m_widthField{ 1 };
        
        // shared delimiter
        static char m_delimiter;

    public:

        void setFieldWidth(size_t newWidth);

        size_t getFieldWidth() const;

        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        static void setDelimiter(char newDelimiter);
        
        static char getDelimiter();
    };
}
#endif
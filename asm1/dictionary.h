/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
#include <cstddef>

namespace seneca {

	enum class PartOfSpeech
	{
		Unknown,
		Noun,
		Pronoun,
		Adjective,
		Adverb,
		Verb,
		Preposition,
		Conjunction,
		Interjection,
	};

	struct Word
	{
		std::string m_word{};
		std::string m_definition{};
		PartOfSpeech m_pos = PartOfSpeech::Unknown;
	};

	class Dictionary {

		Word* m_words{ nullptr };
		std::size_t m_size{ 0 };

		static PartOfSpeech mapPos(const std::string& pos);
		static std::string posToString(PartOfSpeech p);
		static void trim(std::string& s);
		void loadFromFile(const char* filename);

	public:

		// Default Constructor
		Dictionary() = default;

		explicit Dictionary(const char* filename) { 
			
			loadFromFile(filename); 

		}

		// Destructor
		~Dictionary() {
			delete[] m_words;
		}

		// Copy Constructor
		Dictionary(const Dictionary& other);

		// Copy Assignment Operator
		Dictionary& operator=(const Dictionary& other);

		// 
		Dictionary(Dictionary&& other) noexcept;

		//
		Dictionary& operator=(Dictionary&& other) noexcept;

		void searchWord(const char* word) const;

	};
}

#endif
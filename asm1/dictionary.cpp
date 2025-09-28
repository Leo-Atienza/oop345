/***********************************************************************
// OOP345 Assignment 1
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: September 20, 2025
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <iostream>

using namespace std;
namespace seneca {

	static string lower(string s) {
		
		for (char& c : s) {
			if (c >= 'A' && c <= 'Z') {
				c = char(c - 'A' + 'a');
			}
		}
		return s;
	}

	void Dictionary::trim(string& s) {
		
		size_t b = 0;
		size_t e = s.size();

		while (b < e && (unsigned char)s[b] <= ' ') ++b;
		while (e > b && (unsigned char)s[e - 1] <= ' ') --e;
		s.assign(s.begin() + b, s.begin() + e);
	}

	PartOfSpeech Dictionary::mapPos(const string& p) {
		
		string charac = lower(p);
		PartOfSpeech pos = PartOfSpeech::Unknown;

		if (charac == "n." || charac == "n. pl.") {
			pos = PartOfSpeech::Noun;
		}

		else if (charac == "adv.") {
			pos = PartOfSpeech::Adverb;
		}

		else if (charac == "a.") {
			pos = PartOfSpeech::Adjective;
		}
		
		else if (charac == "v." || charac == "v. i." || charac == "v. t." || charac == "v. t. & i.") {
			pos = PartOfSpeech::Verb;
		}

		else if (charac == "prep.") {
			pos = PartOfSpeech::Preposition;
		}
		
		else if (charac == "pron.") {
			pos = PartOfSpeech::Pronoun;
		}
		
		else if (charac == "conj.") {
			pos = PartOfSpeech::Conjunction;
		}
		
		else if (charac == "interj.") {
			pos = PartOfSpeech::Interjection;
		}
		return pos;
	}

	string Dictionary::posToString(PartOfSpeech p) {
		
		static const char* sph[] = {
			"unknown","noun","pronoun","adjective","adverb",
			"verb","preposition","conjunction","interjection"
		};
		
		int num = static_cast<int>(p);
		int name = static_cast<int>(sizeof(sph) / sizeof(sph[0]));
		
		string out = "unknown";
		if (num >= 0 && num < name) out = sph[num];
		
		return out; 
	}


	// Had help from chatgpt 
	// I'm sorry, This is giving me brain damage
	void Dictionary::loadFromFile(const char* filename)
	{
		delete[] m_words;
		m_words = nullptr;
		m_size = 0;

		bool ok = (filename != nullptr);
		ifstream fin;
		if (ok) { fin.open(filename); ok = static_cast<bool>(fin); }

		size_t count = 0;
		string line;

		if (ok) {
			while (getline(fin, line)) if (!line.empty()) ++count;
			fin.clear(); fin.seekg(0);
			ok = (count > 0);
		}

		if (ok) {
			m_words = new Word[count];
			size_t idx = 0;

			while (idx < count && getline(fin, line)) {
				
				if (line.empty()) continue;

				size_t c1 = line.find(',');
				size_t c2 = (c1 == std::string::npos) ? string::npos
					: line.find(',', c1 + 1);

				string w = (c1 == string::npos) ? line : line.substr(0, c1);
				string ps = (c1 != string::npos && c2 != string::npos)
					? line.substr(c1 + 1, c2 - c1 - 1) : "";
				string df = (c2 != string::npos)
					? line.substr(c2 + 1)
					: ((c1 != std::string::npos) ? line.substr(c1 + 1) : "");

				trim(w); trim(ps); trim(df);

				m_words[idx].m_word = w;
				m_words[idx].m_definition = df;
				m_words[idx].m_pos = mapPos(ps);

				++idx;
			}
			m_size = idx;
		}
	}

	Dictionary::Dictionary(const Dictionary& other) {
		
		if (other.m_size) {
			m_words = new Word[other.m_size];
			
			for (size_t i = 0; i < other.m_size; ++i) {
				m_words[i] = other.m_words[i];
			}

			m_size = other.m_size;
		}
	}

	Dictionary& Dictionary::operator=(const Dictionary& other) {

		if (this != &other) {
			Word* extr = nullptr;
			if (other.m_size) {
				extr = new Word[other.m_size];
				for (size_t i = 0; i < other.m_size; ++i) {
					extr[i] = other.m_words[i];
				}
			}
			delete[] m_words;
			m_words = extr;
			m_size = other.m_size;
		}
		return *this;
	}

	Dictionary::Dictionary(Dictionary&& other) noexcept : m_words(other.m_words), m_size(other.m_size) {
		other.m_words = nullptr;
		other.m_size = 0;
	}

	Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
		
		if (this != &other) {
			delete[] m_words;
			m_words = other.m_words;
			m_size = other.m_size;

			other.m_words = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	// Had help from chatgpt
	void Dictionary::searchWord(const char* word) const {
		
		string target = word ? string(word) : string{};
		bool fnd = false;

		size_t printed = 0;
		for (size_t i = 0; i < m_size; ++i) {
			if (m_words[i].m_word == target) {
				if (printed == 0) {
					cout << m_words[i].m_word << " - ";
				}
				else {
					cout << std::string(m_words[i].m_word.size(), ' ') << " - ";
				}
				if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
					cout << '(' << posToString(m_words[i].m_pos) << ") ";
				}
				cout << m_words[i].m_definition << '\n';

				++printed;
				fnd = true;
				if (!g_settings.m_show_all) break;
			}
		}
		if (!fnd) {
			cout << "Word '" << target << "' was not found in the dictionary.\n";
		}
	}
}
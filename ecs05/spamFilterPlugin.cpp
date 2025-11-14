#include "spamFilterPlugin.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;
namespace seneca {

	SpamFilterPlugin::SpamFilterPlugin(const char* filename) {

		ifstream fin(filename);
		
		if (!fin.is_open()) {
			throw std::runtime_error("Cannot open spam filter file.");
		}

		string line;
		
		while (getline(fin, line)) {
			if (!line.empty() && m_keyCount < MAX_KEYS) {
				m_keys[m_keyCount++] = line;
			}
		}
	}

	void SpamFilterPlugin::operator()(Message& msg) {
		
		bool flag = false;
		
		for (size_t i = 0; i < m_keyCount && !flag; ++i) {
			
			const string& k = m_keys[i];
			if (!k.empty() && msg.m_subject.find(k) != string::npos) {
				msg.m_subject = string("[SPAM] ") + msg.m_subject;
				++m_spamCount;
				flag = true;
			}
		}	
	}

	void SpamFilterPlugin::showStats() const {
		
		cout << "[Spam Filter Plugin] identified " << m_spamCount << " spam messages.\n";

	}
}
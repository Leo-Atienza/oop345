#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include <string>
#include <cstddef>
#include "plugin.h"
#include "message.h"

namespace seneca {

	class SpamFilterPlugin : public Plugin {

		static constexpr size_t MAX_KEYS = 128;
		std::string m_keys[MAX_KEYS]{};
		std::size_t m_keyCount{};
		std::size_t m_spamCount{};

	public:
		explicit SpamFilterPlugin(const char* filename);
		void operator() (Message& msg) override;
		void showStats() const override;

	};
}

#endif
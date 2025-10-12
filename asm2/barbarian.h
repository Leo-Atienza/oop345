/***********************************************************************
// OOP345 Assignment 2
//
// Name: Leo Atienza
// I.D. 121941249
// Email: ljaatienza@myseneca.ca
// Date: Oct 10, 2025
************************************************************************
//I declare that this submission is mostly the result of my own work and I copied the code that my professor provided to complete my assignments and also asked chatgpt for help with 1 function.
//This submitted piece of work has been shared with chatgpt.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "characterTpl.h"

namespace seneca {

	template<typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T> {

		int m_baseDefense{};
		int m_baseAttack{};
		Ability_t m_ability{};
		Weapon_t m_weapon[2]{};

	public:

		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
			: CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {

			m_weapon[0] = primaryWeapon;
			m_weapon[1] = secondaryWeapon;

		}

		int getAttackAmnt() const override { // Had help from chatgpt

			double total = static_cast<double>(m_baseAttack)
				+ static_cast<double>(m_weapon[0]) / 2.0
				+ static_cast<double>(m_weapon[1]) / 2.0;

			return static_cast<int>(total);
		}

		int getDefenseAmnt() const override {
			return m_baseDefense;
		}

		Character* clone() const override {
			return new Barbarian(*this);
		}

		void attack(Character* enemy) override {
			
			std:: cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
			m_ability.useAbility(this);
			int dmg = getAttackAmnt();
			m_ability.transformDamageDealt(dmg);
			std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
			enemy->takeDamage(dmg);

		}

		void takeDamage(int dmg) override {

			std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

			int reduced = dmg - m_baseDefense;
			if (reduced < 0) {
				reduced = 0;
			}

			m_ability.transformDamageReceived(reduced);
			CharacterTpl<T>::takeDamage(reduced);
		}
	};
}

#endif
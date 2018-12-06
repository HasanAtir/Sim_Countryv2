#pragma once
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

bool player_wins_war(int& player_pop, int& player_land, int& player_infmili,int&player_airmili, int& neighbour_pop,
                     int& neighbour_infmili, int& neighbour_airmili);
bool win_war_Skirmish(int& population, int& land, int& military, int& money,
                       int& city, int& ucs, int& e_af, int& e_inf, int& ospy, int& check); //stub. Must be replaced!!!
int d100_Random_Roll();
int d50_Random_Roll();
int d10_Random_Roll();
int d4_Random_Roll();
void player_Surrender(int& pop, int& land, int& inf_military, int& air_military, int& money);
void neighbour_Name_Allocation(std::string& nname, std::string& sname, std::string& wname, std::string& ename);
void name_Index_Allocate(int& a, int& b, int& c, int& d);
bool war_Room (int &air_player, int &infantry_player,  int &land, int& population, int& air_computer,
               int& infantry_computer, std::string& name, int &year, int& money, int& city, int& m_factory, int& check);
std::string toUpper (std::string &str);
void sentinelFunction(int from, int to, int& choice);
void starvationFactor(int& population, int food_stores);
int spy (int &ospy, int &cspy);
void enemyspyattack(int &s_chance, std::string& e_s_country, int& cspy, int& af, int& inf );
void player_attack_spy(std::string &n_name,std::string &s_name,  std::string &e_name,
                        std::string &w_name,   int &ospy, int &undercoverspy , int&ucs_north, int& ucs_south,
                        int& ucs_east, int& ucs_west, int& n_af, int& n_inf , int& s_af, int& s_inf, int& e_af, int& e_inf ,int& w_af, int& w_inf );
bool happiness_loss (int &happy);
void instructions (std::string& name);
void cities(int &money);
void country_war_room (int &air_player, int &infantry_player,  int &land, int& population, int& air_computer,
               int& infantry_computer, std::string& name, int &year, int& n_af, int& n_inf, int& s_af, int& s_inf,
               int& e_af, int& e_inf, int& w_af, int& w_inf,std::string &n_name,std::string &s_name,  std::string &e_name,
                        std::string &w_name);


// protest( miltary, commerce, happiness, population)
// Genocide, 50% pop loss, with 20% happiness increase
// 25% miltary increase
// commerce drop by 10% as long as happiness < 40 && > 20

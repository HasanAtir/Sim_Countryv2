#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include "sim_countryfuncs.h"

//using namespace N;
using namespace std;


void starvationFactor(int& population, int food_stores)
{
    population = population*0.50;
}

int d100_Random_Roll()
{
    srand(time(0));
    int random = rand();
    int output = random%100;
    return output;
}

int d10_Random_Roll()
{
    srand(time(0));
    int random = rand();
    int output = random%10;
    return output;
}

int d4_Random_Roll() // For enemy country selection
{
    srand(time(0));
    int random = rand();
    int output = random%4;
    return output;
}


bool win_war_Skirmish(int& population, int& land, int& military)
{
    int chance = d100_Random_Roll();
    double win_pop = 0.90, win_land = 1.15, win_mil = 0.85;
    double loss_pop= 0.75, loss_land= 0.90, loss_mil= 0.70;
    //If lose= -25% pop, -10% land, -30%military
    //If win= -10%pop, +15%land, -15% military
    //weight = military based
    if(chance>50)
    {
        population  = population* win_pop;
        land        = land      * win_land;
        military    = military  * win_mil;
        return true;
    }
    else if(chance<51)
    {
        population  =population * loss_pop;
        land        =land       * loss_land;
        military    =military   * loss_mil;
        return false;
    }
}

/**Definite(?) version of the skirmish function which also takes into account the AI's stats
 * @@PARAM: player's population, military, and land; AI's population, and military
 * @Return: Boolean value indicating whether Player has won the war or not and edits parameters through reference*/
bool player_wins_war(int& player_pop, int& player_land, int& player_infmili,int&player_airmili, int& neighbour_pop,
                     int& neighbour_infmili, int& neighbour_airmili)
{
    int chance = d100_Random_Roll();
    //Affect multipliers
    double win_pop = 0.90, win_land = 1.15, win_mil = 0.85;
    double loss_pop= 0.75, loss_land= 0.90, loss_mil= 0.70;

    if(chance>50)   //Player has won the war
    {
        player_pop      =player_pop         *win_pop;
        player_land     =player_land        *win_land;
        player_infmili     =player_infmili  *win_mil;
        player_airmili  =player_airmili     *win_mil;
        neighbour_pop   =neighbour_pop      *loss_pop;
        neighbour_infmili  =neighbour_infmili     *loss_mil;
        neighbour_airmili = neighbour_airmili   *loss_mil;
        return true;
    }
    else        //Player has lost the war
    {
        player_pop      =player_pop         *loss_pop;
        player_land     =player_land        *loss_land;
        player_infmili     =player_infmili  *loss_mil;
        player_airmili  =player_airmili     *loss_mil;
        neighbour_pop   =neighbour_pop      *win_pop;
        neighbour_infmili  =neighbour_infmili     *win_pop;
        neighbour_airmili = neighbour_airmili   *win_pop;
        return false;
        //Note AI's land is not included because it is inherently inconsequential
    }
}

void player_Surrender(int& pop, int& land, int& inf_military, int& air_military)
{
    //Results if the player surrenders after AI initiates skirmish
    double poploss = 0.95, landloss=0.80, milloss=0.80;
    pop = pop*poploss;
    land = land*landloss;
    inf_military = inf_military*milloss;
    air_military = air_military*milloss;
}

void neighbour_Name_Allocation(string& nname, string& sname, string& wname, string& ename)
{
    string line;
    string name_array[297];
    ifstream namefile("country_name_list_297.txt");//Text file with names
    if (namefile.is_open()) //Assigns country name to array indexes
    {
        int i = 0;
        while(getline(namefile,line))
        {
            name_array[i]=line;
            i++;
        }
        namefile.close();
    }
    else
    {
        cerr<<"ERROR OPENING NAME FILE\n\n";
    }
    //cout<<name_array[2]<<endl<<name_array[150]<<endl<<name_array[296]<<endl; //Testing stub
    int n1, n2, n3, n4;
    name_Index_Allocate(n1, n2, n3, n4);
    nname = name_array[n1];
    sname = name_array[n2];
    wname = name_array[n3];
    ename = name_array[n4];
}

void name_Index_Allocate(int& a, int& b, int& c, int& d)
{
    bool is_different = false;
    srand(time(0));
    while(!is_different) //Loop that generates 4 different random integers
    {
        a = rand()%297;
        b = rand()%297;
        c = rand()%297;
        d = rand()%297;

        if( a!=b && a!=c && a!=d &&
            b!=a && b!=c && b!=d &&
            c!=a && c!=b && c!=d &&
            d!=a && d!=b && d!=c)
        {
            is_different = true;
        }

    }

}

bool war_Room (int &air_player, int &infantry_player,  int &land, int& population, int& air_computer,
               int& infantry_computer, string &name, int &year)
{

    int hp_enemy = 10;
    int hp_player = 10;
    int total_player = air_player+infantry_player;
    int total_computer = air_computer+infantry_computer;
    float const WIN_INF = 0.9; // Win Infantry multiplier
    float const LOSE_INF = 0.75; // Loss Infantry multiplier
    int const afplayer =  air_player, ifplayer = infantry_player;
    float const WIN_AF= 0.99;
    float const LOSE_AF= 0.93;
    float const land_gain = 1.15; // %ge increase
    float const land_loss = 0.90; // %ge decrese
    float const win_land= 0.15; // Isolated increase
    float const lose_land = 0.10; // isolated decrease
    int turns=1;


    cout << "WELCOME TO THE WAR ROOM" << endl;
    cout << "AIRFORCE = JETS. ANTI PLANE GUNS EXIST EXCLUSIVE OF AIRFORCE AND CANNOT BE DESTROYED" << endl;
    cout << "INFANTRY = FOOTSOLDIERS. TANKS EXIST EXCLUSIVE OF INFANTRY AND CANNOT BE DESTROYED" << endl;
    cout << "KEEP A LOOK OUT FOR ENEMY INTEL. IT MAY JUST SWAY THE TIDE OF WAR. GOOD LUCK " << toUpper(name) << "!" << endl;
    cout << "MAY THE BEST COUNTRY WIN" << endl;



    do{
        int chance = d10_Random_Roll(); // Chance of you winning
        int chance_intel= d10_Random_Roll(); // Chance of receiving intel
        turns++;

        cout<< "Player HP: " << hp_player << endl;
        cout<< "Enemy HP: " << hp_enemy << endl;
        cout<< "Your Airforce: " << air_player << endl;
        cout << "Your Infantry: " << infantry_player << endl;
        // Chance of getting intel
        {
            if( chance_intel <=5)
            {
                cout << "You just received Enemy Intel!" << endl;
                cout << "Enemy Airforce: " <<air_computer << endl;;
                cout << "Enemy Infantry: "<<infantry_computer << endl;
            }
            else
            {
                cout << "No enemy intel." << endl; ;
            }
        }
        cout << "Do you choose to attack with infantry or air force or both? \n" ;
        cout << "1: Air force \n" ;
        cout << "2: Infantry \n" ;
        cout<< "3: Both \n" << endl;
        int choice;

        sentinelFunction(1, 3, choice);
        // Game interaction
        {

            if (choice == 1)
            {

                {if (air_player > air_computer){
                        {if ( chance >= 4)
                            {
                                cout << "You win the battle"<< endl;
                                hp_enemy--;
                                air_computer = air_computer*LOSE_AF;
                                air_player = air_player*WIN_AF;
                                land = land * land_gain;
                                cout << "You now have " << land << " land"<< endl;
                            }
                            else
                            {
                                cout << "You lost the battle"<< endl;
                                hp_player--;
                                air_computer = air_computer*WIN_AF;
                                air_player = air_player*LOSE_AF;
                                land = land * land_loss;
                                cout << "You now have " << land << " land"<< endl;
                            }}

                    }
                    else if (air_player < air_computer)
                    {if (chance < 4)
                        {
                            cout << "You win the battle"<< endl;
                            hp_enemy--;
                            air_computer = air_computer*LOSE_AF;
                            air_player = air_player*WIN_AF;
                            land = land * land_gain;
                            cout << "You now have " << land << " land"<< endl;
                        }
                        else
                        {
                            cout << "You lost the battle" << endl;
                            hp_player--;
                            air_computer = air_computer*WIN_AF;
                            air_player = air_player*LOSE_AF;
                            land = land * land_loss;
                            cout << "You now have " << land << " land"<< endl;
                        }}
                    else
                    {if (chance < 5)
                        {
                            cout << "You win the battle" << endl;
                            hp_enemy--;
                            air_computer = air_computer*LOSE_AF;
                            air_player = air_player*WIN_AF;
                            land = land *land_gain;
                            cout << "You now have " << land << " land"<< endl;
                        }
                        else
                        {
                            cout << "You lose the battle" << endl;
                            hp_player--;
                            air_computer = air_computer*WIN_AF;
                            air_player = air_player*LOSE_AF;
                            land = land * land_loss;
                            cout << "You now have " << land << " land"<< endl;
                        }}}
            }
            else if (choice == 2)
            {
                if (infantry_player > infantry_computer)
                {if ( chance >= 4)
                    {cout << "You win the battle"<< endl;
                        hp_enemy--;
                        infantry_computer = infantry_computer*LOSE_INF;
                        infantry_player = infantry_player*WIN_INF;
                        land = land * land_gain;
                        cout << "You now have " << land << " land"<< endl;
                    }
                    else
                    {
                        cout << "You lost the battle"<< endl;
                        hp_player--;
                        infantry_computer = infantry_computer*WIN_INF;
                        infantry_player = infantry_player*LOSE_INF;
                        land = land *land_loss;
                        cout << "You now have " << land << " land"<< endl;
                    }}
                else if (infantry_player < infantry_computer)
                {if (chance < 4)
                    {
                        cout << "You win the battle"<< endl;
                        hp_enemy--;
                        infantry_computer = infantry_computer*LOSE_INF;
                        infantry_player = infantry_player*WIN_INF;
                        land = land *land_gain;
                        cout << "You now have " << land << " land"<< endl;
                    }
                    else
                    {
                        cout << "You lost the battle" << endl;
                        hp_player--;
                        infantry_computer = infantry_computer*WIN_INF;
                        infantry_player = infantry_player*LOSE_INF;
                        land = land * land_loss;
                        cout << "You now have " << land << " land"<< endl;
                    }}
                else
                {if (chance < 5)
                    {
                        cout << "You win the battle" << endl;
                        hp_enemy--;
                        infantry_computer = infantry_computer*LOSE_INF;
                        infantry_player = infantry_player*WIN_INF;
                        land = land * land_gain;
                        cout << "You now have " << land << " land"<< endl;
                    }
                    else
                    {
                        cout << "You lose the battle" << endl;
                        hp_player--;
                        infantry_computer = infantry_computer*WIN_INF;
                        infantry_player = infantry_player*LOSE_INF;
                        land = land * land_loss;
                        cout << "You now have " << land << " land"<< endl;
                    }}
            }
            else if (choice == 3)
            {
                {if (total_player > total_computer)
                    {if ( chance >= 4)
                        {
                            cout << "You win the battle"<< endl;
                            hp_enemy--;
                            infantry_computer = infantry_computer*LOSE_INF;
                            infantry_player = infantry_player*WIN_INF;
                            air_computer = air_computer*LOSE_AF;
                            air_player = air_player*WIN_AF;
                            land = land * land_gain;
                            cout << "You now have " << land << " land"<< endl;
                        }
                        else
                        {
                            cout << "You lost the battle"<< endl;
                            hp_player--;
                            infantry_computer = infantry_computer*WIN_INF;
                            infantry_player = infantry_player*LOSE_INF;
                            air_computer = air_computer*WIN_AF;
                            air_player = air_player*LOSE_AF;
                            land = land * land_loss;
                            cout << "You now have " << land << " land"<< endl;
                        }}
                    else if (total_player < total_computer)
                    {if (chance < 4)
                        {
                            cout << "You win the battle"<< endl;
                            hp_enemy--;
                            infantry_computer = infantry_computer*LOSE_INF;
                            infantry_player = infantry_player*WIN_INF;
                            air_computer = air_computer*LOSE_AF;
                            air_player = air_player*WIN_AF;
                            land = land * land_gain;
                            cout << "You now have " << land << " land"<< endl;
                        }
                        else
                        {
                            cout << "You lost the battle" << endl;
                            hp_player--;
                            infantry_computer = infantry_computer*WIN_INF;
                            infantry_player = infantry_player*LOSE_INF;
                            air_computer = air_computer*WIN_AF;
                            air_player = air_player*LOSE_AF;
                            land = land * land_loss;
                            cout << "You now have " << land << " land"<< endl;
                        }}
                    else
                    {if (chance < 5)
                        {
                            cout << "You win the battle" << endl;
                            hp_enemy--;
                            infantry_computer = infantry_computer*LOSE_INF;
                            infantry_player = infantry_player*WIN_INF;
                            air_computer = air_computer*LOSE_AF;
                            air_player = air_player*WIN_AF;
                            land = land * land_gain;
                            cout << "You now have " << land << " land" << endl;;
                        }
                        else
                        {
                            cout << "You lose the battle" << endl;
                            hp_player--;
                            infantry_computer = infantry_computer*WIN_INF;
                            infantry_player = infantry_player*LOSE_INF;
                            air_computer = air_computer*WIN_AF;
                            air_player = air_player*LOSE_AF;
                            land = land * land_loss;
                            cout << "You now have " << land << " land"<< endl;;
                        }}}
            }
        }
    }
    while(hp_player!=0 && hp_enemy!=0);

    int year_passed = turns/10;
    year = year + year_passed;

    if (hp_enemy==0 && hp_player > 0)
    {
        land = land *1.25;
        int updated_af = afplayer * 0.8;
        int updated_if = ifplayer *0.75;
        int af_pop_lost = afplayer *0.2;
        int inf_pop_lost = ifplayer *0.25;
        cout << "YOU WON THE WAR!" << endl;
        cout << "Since you won, you gain resources as reparations." << endl;;
        cout << "Total land is now  : " << land << " acres" << endl;
        cout << "Air force is now   : " << updated_af << endl;
        cout << "Infantry is now    : " << updated_if << endl;
        population = population - af_pop_lost - inf_pop_lost;
        cout << "Population is now  : " << population << endl;
        air_player = updated_af;
        infantry_player = updated_if;
        cout << "The war lasted " << year_passed << " year(s)!" << endl;

        return true;
    }
    else if (hp_enemy >0 && hp_player==0)
    {
        land = land *0.7;
        int updated_af= afplayer * 0.30; // No. of people remaining in AF
        int updated_if= ifplayer * 0.25; // No. of people remaining in inf
        int af_pop_lost = afplayer *0.7; // No. of people lost from AF
        int inf_pop_lost = ifplayer *0.75; // No. of people lost from inf
        cout << "YOU LOST THE WAR!" << endl;
        cout << "Since you lost, you lose resources as reparations." << endl;;
        cout << "Total land is now  : " << land << " acres" << endl;
        cout << "Air force is now   : " << updated_af << endl;
        cout << "Infantry is now    : " << updated_if << endl;
        population = population - af_pop_lost - inf_pop_lost;
        cout << "Population is now  : " << population << endl;
        air_player = updated_af;
        infantry_player = updated_if;
        cout << "The war lasted " << year_passed << " year(s)!" << endl;

        return false;
    }

}


void sentinelFunction(int from, int to, int& choice)
{
    string dummy;
    bool validinput = false;
    cout<<"Enter your choice\n";
    while(!validinput) {
        cin >> choice;
        if (cin.fail()) {
            cout << "invalid input detected cinfail" << endl;
            validinput = false;
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
        } else if (choice > to || choice < from) {
            cout << "Invalid input detected out of range" << endl;
            cin.clear();
            continue;
        } else {
            cout << "You have selected: " << choice << endl;
            validinput=true;
        }
    }
}

string toUpper(string &str) // Needs to be implemented
{
    int a;
    string c;
    string d = "";

    for(int i=0; i < str.length() ; i++)
    {
        a = int (str[i]);
        if (a < 90)
        {
            char c = char (a);
            d = d + c;
            continue;
        }
        else
        {int b = a-32;
        char c = char (b);
        d= d+c;}
    }
    return d;
}

int spy(int &ospy, int& cspy)
{
    cout << "Do you want to train \n"
            "1 : Spy (Will infiltrate other countries) \n"
            "2 : Counter Spy (Will defend against enemy spies) \n";
    int choice;
    sentinelFunction(1, 2, choice);
    if (choice == 1)
    {
        ospy++;
        if (ospy ==1)
        {
            cout << "You now have " << ospy << " spy" << endl;
        }
        else
        {
            cout << "You now have " << ospy << " spies" << endl;
        }

    }
    else
    {
        cspy++;
        if (cspy ==1)
        {
            cout << "You now have " << cspy << " counter spy" << endl;
        }
        else
        {
            cout << "You now have " << cspy << " counter spies" << endl;
        }
    }

}

void enemyspyattack(int &s_chance, string& e_s_country, int& cspy, int& af, int& inf )
{
    float const afloss = 0.05, infloss = 0.1;
    int def_chance = d100_Random_Roll();
    if (s_chance < 61) // 60% chance of spy attack
    {
        if (def_chance < 61 && cspy > 0 )
        {
            cout << "You were attacked by " << e_s_country<< "'s spy but your Counter Spy defeated the " << e_s_country << " spy!" << endl;
        }
        else if (cspy < 1)
        {
            cout << e_s_country << "'s spy has attacked our barracks, poisoning our infantry and airforce! \n";

            inf = inf - (inf * infloss);
            af = af - (af*afloss);


            cout << "Your current Airforce count is now: " << af << endl;
            cout << "Your current Infantry count is now: " << inf << endl;
        }
        else if (cspy > 0 && def_chance > 61 )
        {
            cout << e_s_country << "'s spy has killed your counter spy \n";
            cout << e_s_country << "'s spy has attacked our barracks, poisoning our infantry and airforce! \n";


            inf = inf - (inf * infloss);
            af = af - (af*afloss);
            cspy--;


            cout << "Your current Airforce count is now: " << af << endl;
            cout << "Your current Infantry count is now: " << inf << endl;
        }
    }


}

void player_attack_spy(string &n_name, string &s_name, string &e_name, string &w_name,  int &ospy, int &undercoverspy)

{

    cout << "Who do you wish to send your spy to?" << endl;
    cout << "1: " << n_name << endl;
    cout << "2: " << s_name << endl;
    cout << "3: " << w_name << endl;
    cout << "4: " << e_name<< endl;
    int input;
    sentinelFunction(1,4, input);
    int p_s_chance = d100_Random_Roll(); // Player spy odds
    int e_s_chance = d100_Random_Roll(); // Enemy spy odds

    if (input == 1)
    {
        if (p_s_chance > 60)
        {
            cout << "Your Spy has successfully infiltrated " << n_name
            << " HQ! You will receive Intel on them before the next battle!" << endl;
            undercoverspy++;
            ospy--;

        }
        else
        {
            cout << " Your spy has been caught by " << n_name << " ." << endl;
            ospy--;
        }

    }
    else if (input == 2)
    {
        if (p_s_chance > 60)
        {
            cout << "Your Spy has successfully infiltrated " << s_name
            << " HQ! You will receive Intel on them before the next battle!" << endl;
            undercoverspy++;
            ospy--;
        }
        else
        {
            cout << " Your spy has been caught by " << s_name << " ." << endl;
            ospy--;
        }

    }
     else if (input == 3)
    {
        if (p_s_chance > 60)
        {
            cout << "Your Spy has successfully infiltrated " << w_name
            << " HQ! You will receive Intel on them before the next battle!" << endl;
            undercoverspy ++;
            ospy--;
        }
        else
        {
            cout << " Your spy has been caught by " << w_name << " ." << endl;
            ospy--;
        }

    }
     else if (input == 4)
    {
        if (p_s_chance > 60)
        {
            cout << "Your Spy has successfully infiltrated " << e_name
            << " HQ! You will receive Intel on them before the next battle!" << endl;
            undercoverspy++;
            ospy--;
        }
        else
        {
            cout << " Your spy has been caught by " << e_name << " ." << endl;
            ospy--;
        }

    }
}
bool happiness_loss(int &happy)
{
    if (happy > 40 )
    {
        return false;
    }
    else
        return true;

}

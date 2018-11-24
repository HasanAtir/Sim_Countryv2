#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
//Workdate/time 6:30 pm, 19-Nov-2018

using namespace std;
/*Options that should be available:
 *
 * 1) Go to war
 * 1a)with who?
 *
 * 2) Build military factory
 *
 * 3) Refocus military
 *
 * 4) random invention (Time span = 10years)
 *
 *  Starting work on neigbhours
 *
 *
 *
 * */
/**To do list:
 * 1) Fix random name generator array
 * 2) Add description of the game(low prior)
 * 3) Implement war room
 *
 * */

//Function prototypes. Called now to prevent 'not declared' errors.
bool player_wins_war(int& player_pop, int& player_land, int& player_infmili,int&player_airmili, int& neighbour_pop,
                     int& neighbour_infmili, int& neighbour_airmili);
bool win_war_Skirmish(int& population, int& land, int& military); //stub. Must be replaced!!!
int d100_Random_Roll();
int d10_Random_Roll();
void player_Surrender(int& pop, int& land, int& inf_military, int& air_military);
void neighbour_Name_Allocation(string& nname, string& sname, string& wname, string& ename);
void name_Index_Allocate(int& a, int& b, int& c, int& d);
bool war_Room (int &air_player, int &infantry_player,  int &land, int& population, int& air_computer,
               int& infantry_computer, string& name, int &year);
string toUpper (string &str);
void sentinelFunction(int from, int to, int& choice);



void starvationFactor(int& population, int food_stores)
{
    population = population*0.50;
}

int main()
{
    //initial conditions;

    int population, air_military, infantry_military, commerce, military_factory, land, food, happiness_factor;
    population = 100000;
    air_military = 100;
    infantry_military = 1000;
    commerce = 10000000;
    land = 1000;
    food = land*1000;
    military_factory=1;
    happiness_factor = 100; // Happiness Level
    int year = 1921;
    int food_stores=food;
    double gdp;
    int number_of_wars=0;
    int number_of_wars_won=0;
    int remaining_construction_time = 0;

    double pop_grow, comm_grow, mili_grow, gdp_grow, food_grow;

    //bools
    bool game_over = false;
    bool building_factory = false;

    //temp variable
    int next_year_option;

    string north_name, south_name, east_name, west_name, player_name;
    neighbour_Name_Allocation(north_name, south_name, west_name, east_name);



    //Neighbour land values are inconsequential
    //Northern neighbour. Will be used as prototype for all other neighbours
    int north_id=1;
    int north_population=100000;
    int north_infantry_military=10000;
    int north_air_military=1000;
    int north_commerce=10000000;
    int north_gdp;
    int north_military_factory=1;
    int north_land=1000;
    //growth
    double north_population_growth = 1.05;
    double north_commerce_growth = 1.15;
    double north_military_growth = military_factory*25;

    //Other neighbours
    int south_id=2;
    int east_id =3;
    int west_id =4;

    cout << "Welcome to Sim Country player. Please enter your name: ";
    cin >> player_name;

    while(!game_over)
    {
        //resetting AI values
        int north_land = 1000;
        //growth factors:
        gdp = (commerce)/population;


        cout << player_name << " these are your current country stats" << endl;

        //output
        cout<<"CURRENT YEAR:                "<<year<<endl<<endl;
        cout<<"Current population:          "<<population<<endl;
        cout<<"Current food stocks:         "<<food_stores<<endl;
        cout<<"Current owned land:          "<<land<<endl;
        cout<<"Current Military might:      "<<air_military+infantry_military<<endl;
        cout<<"Current Military factories   "<<military_factory;
        if(building_factory){cout<<"(1)"<<endl;}
        else {cout<<endl;}
        cout<<"Current Commercial prowess:  "<<commerce<<endl;
        cout<<"Current GDP/Capita:          $"<<gdp<<endl;
        cout<<"Total number of wars:        "<<number_of_wars<<endl;
        cout<<"Total wars won:              "<<number_of_wars_won<<endl;
        cout<<"Happiness Level of Population: "<< happiness_factor<<"%"<<endl;




        //growth
        pop_grow = 1+ ((double)food/population)/100;
        cout<<pop_grow<<endl;
        food_grow = land*1000;
        mili_grow = military_factory*25;

        food_stores = (food_stores - population) + (food_grow);
        population = population*pop_grow;
        air_military = air_military+mili_grow;
        infantry_military = infantry_military+(2*mili_grow);
        cout<<"\nPopulation growth: "<<pop_grow<<endl;

        if(food_stores<0)
        {
            food_stores = 0;
            starvationFactor(population,food_stores);   //Decreases population rapidly if food_stores are depleted

        }

        //game time BASIC OPTIONS. Persistent for now, plans to be randomised
        cout<<"1) Go to war (skirmish)\n"
              "2) Build military factory\n"
              "3) Random invention\n"
              "4) quit simulation\n"
              "5) Go to all out war\n";  ///Needs to be implemented
        sentinelFunction(1, 5, next_year_option);

        if(next_year_option==1)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            number_of_wars++;
            bool war_win = win_war_Skirmish(population, land, infantry_military);
            if(war_win)
            {
                cout<<"You have won the war!\n\n";
                number_of_wars_won++;
                // Happiness Effects
                if (happiness_factor < 100)
                    happiness_factor = happiness_factor +10;
                else
                    happiness_factor;
            }
            else
            {
                cout<<"You have lost the war!\n\n";
                happiness_factor = happiness_factor -10;
            }
        }
        else if(next_year_option==2)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            building_factory = true;        //Boolean that starts construction of factory
            remaining_construction_time = 3;//Estimated time until factory finishes construction
        }
        else if(next_year_option==4)
        {
            game_over = true;
        }
        else if (next_year_option==5)
        {
            number_of_wars++;
            bool war_win = war_Room(air_military,infantry_military,land,population,north_air_military,
                                    north_infantry_military,player_name, year);
            if(war_win)
            {

                number_of_wars_won++;
                // Happiness Effects
                if (happiness_factor < 100)
                    happiness_factor = happiness_factor +10;
                else
                    happiness_factor;
            }
            else
            {

                happiness_factor = happiness_factor -10;
            }
        }

        //Military factory construction time counter
        if(building_factory)
        {
            if(remaining_construction_time>0)
            {
                remaining_construction_time--;
            }

            if(remaining_construction_time == 0)
            {
                cout<<"\n -MILITARY FACTORY BUILT- \n";
                building_factory = false;
                military_factory++;
            }
        }

        //Neighbour 1 simulation
        north_population=north_population*north_population_growth;
        north_infantry_military = north_infantry_military + (2*north_military_growth);
        north_air_military = north_air_military + north_military_growth;
        north_commerce=north_commerce*north_commerce_growth;
        gdp = north_commerce/north_population;
        /*available options that should be available
         * 1) war
         * 2) build military factory
         * 3) do nothing
         * 4)
         * */
        int north_random_options = d10_Random_Roll();

        if(north_random_options==1)
            //Northern neighbour declares skirmish war on player
        {   bool player_defends = false;
            cout<<"\n"<<north_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            cin>>player_defends;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population, land, infantry_military, air_military, north_population, north_infantry_military, north_air_military);
                //Calls the war boolean function if player chooses to defend.
                if(player_victory)
                {
                    cout<<"You have won the war!\n\n";
                    number_of_wars_won++;
                    // Happiness Effects
                    if (happiness_factor < 100)
                    {
                        happiness_factor = happiness_factor +10;
                    }
                    else
                    {
                        happiness_factor;
                    }
                }
                else
                {
                    cout<<"You have lost the war!\n\n";
                    happiness_factor = happiness_factor -10;
                }
            }
            else
            {
                cout<<"You surrendered\n";
                player_Surrender(population, land, infantry_military, air_military);   //Calls the surrender function if Player decides not to defend
                happiness_factor = happiness_factor - 10;

            }
        }




        //Added for testing purposes. Needs to be removed.
        cout<<north_name<<endl<<south_name<<endl<<west_name<<endl<<east_name<<endl;
    }
}

//Diceroll functions
/** Random roll program to generate a value between 0 and 100
 * @@Param = null
 * @Return = [0,100]*/
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

//Following function needs to be REMOVED>>>
/**Function used to simulate skirmishes using chance.
 * TO BE ADDED: Slight weighted bias with populations and militar
 * @@Param population, land, and military
 * @return weither skirmish was won or not. Can then be used to output conditional messages in main()*/
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


#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Windows.h"
#include "sim_countryfuncs.cpp"
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



int main()
{


    //initial conditions;

    int population, air_military, infantry_military, commerce, military_factory, land, food,
            happiness_factor, ospy, cspy, undercover_spy, ucs_north, ucs_south, ucs_east, ucs_west, city;
    population = 100000;
    air_military = 100;
    infantry_military = 1000;
    commerce = 10000000;
    land = 1000;
    food = land*1000;
    military_factory=1;
    happiness_factor = 100; // Happiness Level
    ospy = 0; // Offensive Spy
    cspy = 0; // Counter Spy
    undercover_spy =0;
    ucs_north = 0;
    ucs_south = 0;
    ucs_east = 0;
    ucs_west = 0;
    city = 1;

    int year = 1921;
    int food_stores=food;
    double gdp;
    int number_of_wars=0;
    int number_of_wars_won=0;
    int remaining_construction_time = 0;
    int remaining_time_city_construction = 0;



    double pop_grow, comm_grow, mili_grow, gdp_grow, food_grow;

    //bools
    bool game_over = false;
    bool building_factory = false;
    bool building_city = false;

    //temp variable
    int next_year_option;

    string north_name, south_name, east_name, west_name, player_name;
    neighbour_Name_Allocation(north_name, south_name, west_name, east_name);
    string enemy_names [4] = {north_name, south_name, west_name, east_name}; // Array with enemy country names






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

    srand(time(0)); // RANDOM INTIALISATION


    int turn_count =0; // Helps count to five turns, at which happiness automatically increases by 10.
    cout << "Welcome to Sim Country player. Please enter your name: ";
    getline(cin, player_name);

    instructions(player_name);
    system("pause");

    while(!game_over)
    {



        cout << d100_Random_Roll() << endl;

        //resetting AI values
        int north_land = 1000;
        //growth factors:
        gdp = (commerce)/population;


        cout << player_name << " these are your current country stats" << endl;

        //output
        cout<<"CURRENT YEAR:                         "<<year<<endl<<endl;
        cout<<"Current population:                   "<<population<<endl;
        cout<<"Current food stocks:                  "<<food_stores<<endl;
        cout<<"Current owned land:                   "<<land<<endl;
        cout<<"Current Military might:               "<<air_military+infantry_military<<endl;
        cout<<"Current Military factories            "<<military_factory;
        if(building_factory){cout<<"(1)"<<endl;}
        else {cout<<endl;}
        cout<<"City Count:                           "<< city;
        if(building_city){cout <<"(1)"<<endl;}
        else {cout<<endl;}
        cout<<"Current Commercial prowess:           "<<commerce<<endl;
        cout<<"Current GDP/Capita:                   $"<<gdp<<endl;
        cout<<"Current Available Spy Count:          " << ospy << endl;
        cout<<"Current Available Counter Spy Count:  " << cspy << endl;
        cout<<"Spys who are undercover:              " << undercover_spy << endl;
        cout<<"Total number of wars:                 "<<number_of_wars<<endl;
        cout<<"Total wars won:                       "<<number_of_wars_won<<endl;
        cout<<"Happiness Level of Population:        "<< happiness_factor<<"%"<<endl;




        //growth
        pop_grow = 1+ ((double)food/population)/100;
        cout<<pop_grow<<endl;
        food_grow = land*1000;
        mili_grow = military_factory*25;


        food_stores = (food_stores - population) + (food_grow*city);// Food growth increases with city count
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
        if (ospy == 0)
        {cout<<"1) Go to war (skirmish)\n"
              "2) Build military factory\n"
              "3) Random invention\n"
              "4) Build a city\n"
              "5) Go to all out war\n"
              "6) Train a type of Spy \n"
              "7) quit simulation\n";
        sentinelFunction(1, 7, next_year_option);

                if(next_year_option==1)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            number_of_wars++;
            bool war_win = win_war_Skirmish(population, land, infantry_military, commerce, city/*, north_name, south_name, east_name, west_name */);
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
            commerce = commerce - 5000;
            remaining_construction_time = 3;//Estimated time until factory finishes construction
        }
        else if (next_year_option ==4)
        {
            year++;
            building_city = true;
            commerce = commerce - 15000; // City building takes 15000 units of commerce
            remaining_time_city_construction = 5;
        }

        else if (next_year_option==5)
        {
            number_of_wars++;
            bool war_win = war_Room(air_military,infantry_military,land,population,north_air_military,
                                    north_infantry_military,player_name, year, commerce, city, military_factory);
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
        else if(next_year_option==6)
        {
            year++;
            spy(ospy,cspy);
        }
         else if(next_year_option==7)
        {
            game_over = true;
        }
        }
        else
        {cout<<"1) Go to war (skirmish)\n"
              "2) Build military factory\n"
              "3) Random invention\n"
              "4) Build a city\n"
              "5) Go to all out war\n"
              "6) Train a type of Spy \n"
              "7) Send Spy Undercover \n"
              "8) quit simulation\n";
        sentinelFunction(1, 8, next_year_option);
                        if(next_year_option==1)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            number_of_wars++;
            bool war_win = win_war_Skirmish(population, land, infantry_military, commerce, city/*, north_name, south_name, east_name, west_name*/);
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
            commerce = commerce - 5000;
            remaining_construction_time = 3;//Estimated time until factory finishes construction
        }
         else if (next_year_option ==4)
        {
            year++;
            building_city = true;
            commerce = commerce - 15000; // City building takes 15000 units of commerces
            remaining_time_city_construction = 5;
        }

        else if (next_year_option==5)
        {
            number_of_wars++;
            bool war_win = war_Room(air_military,infantry_military,land,population,north_air_military,
                                    north_infantry_military,player_name, year, commerce, city, military_factory);
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
        else if(next_year_option==6)
        {
            year++;
            spy(ospy,cspy);
        }
        else if (next_year_option==7)
        {
            year++;
            player_attack_spy(north_name, south_name, east_name, west_name,  ospy, undercover_spy);
        }
         else if(next_year_option==8)
        {
            game_over = true;
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
        //City building time counter
        if (building_city)
        {
            if(remaining_time_city_construction>0)
            {
                remaining_time_city_construction--;
            }

            if(remaining_time_city_construction == 0)
            {
                cout<<"\n -CITY BUILT- \n";
                building_city = false;
                city++;
            }
        }

        // Enemy Game stuff
        int e_spyattack = d100_Random_Roll();
        int enemy_name_choice = d4_Random_Roll();
        string attacking_enemy = enemy_names[enemy_name_choice]; // Random Country name given

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
            number_of_wars++;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population, land, infantry_military, air_military,
                                                     north_population, north_infantry_military, north_air_military);
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
                player_Surrender(population, land, infantry_military, air_military, commerce);   //Calls the surrender function if Player decides not to defend
                happiness_factor = happiness_factor - 10;

            }
        }



        enemyspyattack(e_spyattack, attacking_enemy, cspy, air_military, infantry_military);
        turn_count++;
        if(turn_count%5 == 0) // Every 5 turns, Happiness increase!
        {
            if(happiness_factor!=100)
            {
                happiness_factor= happiness_factor+10;
            }

        }
        system("pause");
        if(happiness_factor < 21)
            {
                cout << "Your people are only " << happiness_factor << "% happy!" << endl;
                cout << "Your people have revolted!" << endl;
                cout << "GAME OVER!" << endl;
                game_over= true;

            }


    commerce = commerce + (2000*city) -(500*military_factory); // Every city will add 2000 units of commerce and military factories reduce commerce due to maintenance

    if (city < 1)
    {
        cout << "You have lost all your cities!" << endl;
        cout << "GAME OVER" << endl;
        game_over = true;
    }



    }


}



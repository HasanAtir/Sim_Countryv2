#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Windows.h"
#include "sim_countryfuncs.cpp"
//Workdate/time 6:30 pm, 19-Nov-2018

using namespace std;

int main()
{


    //initial conditions;
    int cumulative_score=0;//Final score to when winning the game
    long commerce;
    int population, air_military, infantry_military, military_factory, land, food,
            happiness_factor, ospy, cspy, undercover_spy, ucs_north, ucs_south, ucs_east, ucs_west,
             city, check, check_war_room, total_mili;
    int const FOOD_MAX = 100000000, CITY_COMMERCE_GAIN = 10000, FACTORY_UPKEEP = 200, LAND_COMMERCE_GAIN = 500; //Max food to prevent stack commerce gain via land and cities, as well as cost of factories
    //winning GDP
    int const GDP_WIN = 650;
    struct Endscore //data type for final score;
    {
        string name;
        int score;
        int wars_won;
        int genocides_committed;
        int land;
    };



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

    //undercover spies in different countries
    ucs_north = 0;
    ucs_south = 0;
    ucs_east = 0;
    ucs_west = 0;
    city = 1;
    check = 0;
    check_war_room = 0;
    total_mili = air_military+ infantry_military;


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
    int north_infantry_military=2000;
    int north_air_military=500;
    int north_commerce=10000000;
    int north_gdp;
    int north_military_factory=1;
    int north_land=1000;
    //growth
    double north_population_growth = 1.05;
    double north_commerce_growth = 1.15;
    double north_military_growth = military_factory*95;

    //Other neighbours
    int south_id=2;
    int south_population=100000;
    int south_infantry_military=2000;
    int south_air_military=500;
    int south_commerce=10000000;
    int south_gdp;
    int south_military_factory=1;
    int south_land=1543;
    //growth
    double south_population_growth = 1.13;
    double south_commerce_growth = 1.22;
    double south_military_growth = military_factory*95;

    int east_id =3;
    int east_population=100000;
    int east_infantry_military=1000;
    int east_air_military=500;
    int east_commerce=10000000;
    int east_gdp;
    int east_military_factory=1;
    int east_land=1543;
    //growth
    double east_population_growth = 1.17;
    double east_commerce_growth = 1.07;
    double east_military_growth = military_factory*95;

    int west_id =4;
    int west_population=100000;
    int west_infantry_military=1000;
    int west_air_military=500;
    int west_commerce=10000000;
    int west_gdp;
    int west_military_factory=1;
    int west_land=1543;
    //growth
    double west_population_growth = 1.09;
    double west_commerce_growth = 1.10;
    double west_military_growth = military_factory*95;

    //win conditions:
    bool game_won_gdp = false;

    //lose conditions:
    bool lost_game_city = false;
    bool lost_game_overthrown = false;
    bool lost_game_gdp = false;
    bool lost_game_quit = false;

    srand(time(0)); // RANDOM INTIALISATION


    int turn_count =0; // Helps count to five turns, at which happiness automatically increases by 10.

    cout << "=======================================================================================\n";
    Sleep(300);
    cout << "|                                                                                     |\n";
    Sleep(275);
    cout << "| @@@@@@  @@, @@%    @@,     @@@@@   @@@@@@  @@%  @@  @@   @@ @@@@@@@ @@@@@@  @@  %@@ |\n";
    Sleep(250);
    cout << "| @@  &@% @@, @@@   %@@,    @@   @@ ,@@  %@@ @@%  @@  @@@  @@   @@    @@  &@@ &@, @@  |\n";
    Sleep(225);
    cout << "| @@      @@, @@@@  @@@,    @@      ,@@  ,@@ @@%  @@  @@@  @@   @@    @@  %@@  @@%@   |\n";
    Sleep(200);
    cout << "|  &@@@@  @@, @@ @.@@%@,    @@      ,@@  ,@@ @@%  @@  @@%@ @@   @@    @@@@@@    @@@   |\n";
    Sleep(175);
    cout << "|     @@@ @@, @@ @@@ %@,    @@      ,@@  ,@@ @@%  @@  @@ @@@@   @@    @@ @@     @@    |\n";
    Sleep(150);
    cout << "| @@  #@@ @@, @@  @@ %@,    @@   @@ ,@@  %@@ @@%  @@  @@  @@@   @@    @@  @@    @@    |\n";
    Sleep(100);
    cout << "| @@@@@@  @@, @@     %@,     @@@@@   @@@@@@   @@@@@   @@   @@   @@    @@  @@@   @@    |\n";
    Sleep(50);
    cout << "|                                                                                     |\n";
    cout << "=======================================================================================\n\n\n";
    cout << "Welcome to Sim Country player. Please enter your name: ";
    getline(cin, player_name);
    //Prints the name of the opponents;
    cout<<"Opponent Countries: \n";
    cout<<"North: "<<north_name<<endl;
    cout<<"South: "<<south_name<<endl;
    cout<<"East : "<<east_name<<endl;
    cout<<"West : "<<west_name<<endl<<endl;


    instructions(player_name, GDP_WIN);
    system("pause");


    while(!game_over)
    {

        //resetting AI values
        //These values were added to help simplify war functions
        north_land = 13000;
        south_land = 13000;
        east_land  = 13000;
        west_land  = 13000;


        //growth factors:
        gdp = (commerce)/population;
        //Undercover spy count
        undercover_spy = ucs_east + ucs_north +ucs_south + ucs_west;

        cout << player_name << ", these are your current country stats" << endl;

        //output
        cout<<"CURRENT YEAR:                         "<<year<<endl<<endl;
        cout<<"Current population:                   "<<population<<endl;
        cout<<"Current food stocks:                  "<<food_stores<<"/"<<FOOD_MAX<<endl;
        cout<<"Current owned land:                   "<<land<<endl;
        cout<<"Current Military might:               "<<air_military+infantry_military<<endl;
        cout<<"Current Military factories            "<<military_factory;
        if(building_factory){cout<<"(1)"<<endl;}//The number in brackets indicate whether a factory or city is under construction
        else {cout<<endl;}
        cout<<"City Count:                           "<< city;
        if(building_city){cout <<"(1)"<<endl;}
        else {cout<<endl;}
        cout<<"Current Commercial prowess:           "<<commerce<<endl;
        cout<<"Current GDP/Capita:                   $"<<gdp<<endl;
        cout<<"Current Available Spy Count:          " << ospy << endl;
        cout<<"Current Available Counter Spy Count:  " << cspy << endl;
        cout<<"Spies who are undercover:             " << undercover_spy << endl;
        cout<<"Total number of wars:                 "<<number_of_wars<<endl;
        cout<<"Total wars won:                       "<<number_of_wars_won<<endl;
        cout<<"Happiness Level of Population:        "<< happiness_factor<<"%"<<endl;




        //growth
        pop_grow = 1+ city*((double)food/population)/100;
        //Prevents ludicrous population growth from happening
        if(pop_grow>1.4)
        {
            pop_grow = 1.400;
        }
        cout<<pop_grow<<endl;
        food_grow = land*100;
        mili_grow = military_factory*100;


        if(food_stores<FOOD_MAX)
        {
            food_stores = (food_stores - population*2) + (food_grow*city);// Food growth increases with city count CHANGED 4th DEC, muliplied by 2
        }
        population = population*pop_grow;
        air_military = air_military+mili_grow;
        infantry_military = infantry_military+(2*mili_grow);

        cout<<"\nPopulation growth: "<<pop_grow<<endl;

        if(food_stores<0)
        {
            food_stores = 0;
            starvationFactor(population,food_stores);   //Decreases population rapidly if food_stores are depleted

        }

        //game time options
        if (ospy == 0)
        {cout<<"1) Engage in a skirmish\n"
              "2) Build military factory\n"
              "3) Build a city\n"
              "4) Go to all out war\n"
              "5) Train a type of Spy \n"
              "6) Quit simulation\n";
        sentinelFunction(1, 7, next_year_option);

                if(next_year_option==1)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            int skirmish_choice;
            cout<<"Who do you want to go to skirmish against?\n";
            cout<<"1) "<<north_name<<endl;
            cout<<"2) "<<south_name<<endl;
            cout<<"3) "<<east_name<<endl;
            cout<<"4) "<<west_name<<endl;
            sentinelFunction(1,4,skirmish_choice);
            number_of_wars++;
            bool war_win = false;
            if (skirmish_choice ==1)
            {
                war_win = win_war_Skirmish(population, land, infantry_military, commerce, city, north_name, ucs_north, north_air_military, north_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==2)
            {
                war_win =win_war_Skirmish(population, land, infantry_military, commerce, city, south_name, ucs_south, south_air_military, south_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==3)
            {
                war_win = win_war_Skirmish(population, land, infantry_military, commerce, city, east_name, ucs_east, east_air_military, east_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==4)
            {
                war_win = win_war_Skirmish(population, land, infantry_military, commerce, city, west_name, ucs_west, west_air_military, west_infantry_military, ospy, check);
            }
            if(war_win)
            {

                number_of_wars_won++;

                // Happiness Effects
                if (happiness_factor < 100)
                    {happiness_factor = happiness_factor +10;}
                else
                    {happiness_factor;}
            }
            else
            {
                if(check == 0)
                {  happiness_factor = happiness_factor -10;}
                else
                {
                    check--;
                    number_of_wars--;
                    year--;
                }


            }
        }
        else if(next_year_option==2)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            building_factory = true;        //Boolean that starts construction of factory
            commerce = commerce - 5000;
            remaining_construction_time = 3;//Estimated time until factory finishes construction
        }
        else if (next_year_option ==3)
        {
            year++;
            building_city = true;
            commerce = commerce - 15000; // City building takes 15000 units of commerce
            remaining_time_city_construction = 5;
        }

        else if (next_year_option==4)
        {
            int all_out_war_choice;
            cout<<"Who do you want to go to war against?\n";
            cout<<"1) "<<north_name<<endl;
            cout<<"2) "<<south_name<<endl;
            cout<<"3) "<<east_name<<endl;
            cout<<"4) "<<west_name<<endl;

            sentinelFunction(1,4,all_out_war_choice);

            number_of_wars++;

            bool war_win = false;

            if(all_out_war_choice==1)
            {
                war_win = war_Room(air_military,infantry_military,land,population,north_air_military,
                                    north_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==2)
            {
                war_win = war_Room(air_military,infantry_military,land,population,south_air_military,
                                    south_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==3)
            {
                war_win = war_Room(air_military,infantry_military,land,population,east_air_military,
                                    east_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==4)
            {
                war_win = war_Room(air_military,infantry_military,land,population,west_air_military,
                                    west_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }

            if(war_win)
            {

                if (check_war_room == 0)
                {number_of_wars_won++;
                // Happiness Effects
                if (happiness_factor < 100)
                    {happiness_factor = happiness_factor +10;}
                else
                    {happiness_factor;}}
                else{check_war_room--;}
            }
            else
            {

                happiness_factor = happiness_factor -10;
            }
        }
        else if(next_year_option==5)
        {
            year++;
            spy(ospy,cspy);
        }
         else if(next_year_option==6)
        {
            cout << "Are you sure you want to quit?\n";
            cout << "Press 1 to continue. 0 to quit\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 0)
            {
                game_over = true;
                lost_game_quit = true;
                continue;
            }


        }
        else if(next_year_option == 7)
        {
            int testoptions;
            cout<<"TESTING ONLY!"<<endl;
            cout<<"1) Happiness\n"
                    "2) Population\n"
                    "3) Military Factories\n"
                    "4) Cities\n"
                    "5) Commerce\n"
                    "6) Win Game\n";
            cin>>testoptions;
            if(testoptions == 1)
            {
                cout<<"Happiness = ";
                cin>>happiness_factor;
            }
            else if(testoptions == 2)
            {
                cout<<"population = ";
                cin>>population;
            }
            else if(testoptions == 3)
            {
                cout<<"Military factories = ";
                cin>>military_factory;
            }
            else if(testoptions == 4)
            {
                cout<<"Cities = ";
                cin>>city;
            }
            else if(testoptions = 5)
            {
                cout<<"commerce =";
                cin>>commerce;
            }
            else if(testoptions = 6)
            {
                cout<<"Game won";
                game_over = true;
                game_won_gdp = true;
                continue;
            }


        }
        }
        else
        {cout<<"1) Engage in a skirmish\n"
              "2) Build military factory\n"
              "3) Build a city\n"
              "4) Go to all out war\n"
              "5) Train a type of Spy \n"
              "6) Send Spy Undercover \n"
              "7) quit simulation\n";
        sentinelFunction(1, 8, next_year_option);

        if(next_year_option==1)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            int skirmish_choice;
            cout<<"Who do you want to go to skirmish against?\n";
            cout<<"1) "<<north_name<<endl;
            cout<<"2) "<<south_name<<endl;
            cout<<"3) "<<east_name<<endl;
            cout<<"4) "<<west_name<<endl;
            sentinelFunction(1,4,skirmish_choice);
            number_of_wars++;
            bool war_win = false;
            if (skirmish_choice ==1)
            {
                war_win= win_war_Skirmish(population, land, infantry_military, commerce, city, north_name, ucs_north, north_air_military, north_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==2)
            {
                war_win=win_war_Skirmish(population, land, infantry_military, commerce, city, south_name, ucs_south, south_air_military, south_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==3)
            {
                war_win=win_war_Skirmish(population, land, infantry_military, commerce, city, east_name, ucs_east, east_air_military, east_infantry_military, ospy, check);
            }
            else if (skirmish_choice ==4)
            {
                war_win=win_war_Skirmish(population, land, infantry_military, commerce, city, west_name, ucs_west, west_air_military, west_infantry_military, ospy, check);
            }
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
                if ( check ==0)
                {

                happiness_factor = happiness_factor -10;
                }
                else
                {
                    check--;
                    number_of_wars--;
                    year--;
                }


            }
        }
        else if(next_year_option==2)
        {
            year++;//Increments year (Added here because if we go to war room it adds an extra year on top)
            cout<<"\nConstructing military factory. Est wait time: 3 years\n";
            building_factory = true;        //Boolean that starts construction of factory
            commerce = commerce - 5000;
            remaining_construction_time = 3;//Estimated time until factory finishes construction
        }
         else if (next_year_option ==3)
        {
            year++;
            cout<<"\nConstructing city. Est wait time: 5 years\n";
            building_city = true;
            commerce = commerce - 15000; // City building takes 15000 units of commerces
            remaining_time_city_construction = 5;
        }

        else if (next_year_option==4)
        {
            int all_out_war_choice;
            cout<<"Who do you want to go to war against?\n";
            cout<<"1) "<<north_name<<endl;
            cout<<"2) "<<south_name<<endl;
            cout<<"3) "<<east_name<<endl;
            cout<<"4) "<<west_name<<endl;
            sentinelFunction(1,4,all_out_war_choice);
            number_of_wars++;
            bool war_win = false;
            if(all_out_war_choice==1)
            {
                war_win = war_Room(air_military,infantry_military,land,population,north_air_military,
                                    north_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==2)
            {
                war_win = war_Room(air_military,infantry_military,land,population,south_air_military,
                                    south_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==3)
            {
                war_win = war_Room(air_military,infantry_military,land,population,east_air_military,
                                    east_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }
            else if(all_out_war_choice==4)
            {
                war_win = war_Room(air_military,infantry_military,land,population,west_air_military,
                                    west_infantry_military,player_name, year, commerce, city, military_factory, check_war_room);
            }

            if(war_win)
            {
                if (check_war_room == 0)
                {number_of_wars_won++;
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
                    check_war_room--;
                    number_of_wars++;
                }
            }
            else
            {

                happiness_factor = happiness_factor -10;
            }
        }
        else if(next_year_option==5)
        {
            year++;
            spy(ospy,cspy);
        }
        else if (next_year_option==6)
        {
            year++;
            player_attack_spy(north_name, south_name, east_name, west_name,  ospy,ucs_north,ucs_south,ucs_east,ucs_west, north_air_military, north_infantry_military, south_air_military, south_infantry_military, east_air_military, east_infantry_military, west_air_military, west_infantry_military);
        }
         else if(next_year_option==7)
        {
            cout << "Are you sure you want to quit?\n";
            cout << "Press 1 to continue. 0 to quit\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 0)
            {
                game_over = true;
                lost_game_quit = true;
                continue;
            }
        }
        else if(next_year_option == 8)
        {
            int testoptions = 0;
            cout<<"TESTING ONLY!"<<endl;
            cout<<"1) Happiness\n"
                    "2) Population\n"
                    "3) Military Factories\n"
                    "4) Cities\n"
                    "5) Commerce\n"
                    "6) Win Game\n";
            cin>>testoptions;
            if(testoptions == 1)
            {
                cout<<"Happiness = ";
                cin>>happiness_factor;
            }
            else if(testoptions == 2)
            {
                cout<<"population = ";
                cin>>population;
            }
            else if(testoptions == 3)
            {
                cout<<"Military factories = ";
                cin>>military_factory;
            }
            else if(testoptions == 4)
            {
                cout<<"Cities = ";
                cin>>city;
            }
            else if(testoptions = 5)
            {
                cout<<"commerce =";
                cin>>commerce;
            }
            else if(testoptions = 6)
            {
                cout<<"Game won";
                game_over = true;
                game_won_gdp = true;
                continue;
            }


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

        //North growth simulation
        north_population=north_population*north_population_growth;
        north_infantry_military = north_infantry_military + north_military_growth;
        north_air_military = north_air_military + north_military_growth;
        north_commerce=north_commerce*north_commerce_growth;
        north_gdp = north_commerce/north_population;

        //South growth simulation
        south_population = south_population*south_population_growth;
        south_infantry_military = south_infantry_military + south_military_growth;
        south_air_military = south_air_military + south_military_growth;
        south_commerce = south_commerce*south_commerce_growth;
        south_gdp = south_commerce/south_population;

        //East growth simulation
        east_population = east_population*east_population_growth;
        east_infantry_military = east_infantry_military + east_military_growth;
        east_air_military = east_air_military + east_military_growth;
        east_commerce = east_commerce*east_commerce_growth;
        east_gdp = east_commerce/east_population;

        //West growth simulation
        west_population = west_population*west_population_growth;
        west_infantry_military = west_infantry_military + west_military_growth;
        west_air_military = west_air_military + west_military_growth;
        west_commerce = west_commerce*west_commerce_growth;
        west_gdp = west_commerce/west_population;


        int north_random_options = d50_Random_Roll();
        int south_random_options = d50_Random_Roll();
        int east_random_options = d50_Random_Roll();
        int west_random_options = d50_Random_Roll();
        //The following functions determine if an ai declares war on the player.

        if(north_random_options<=7)

        {   bool player_defends = false;
            cout<<"\n"<<north_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 1)
            {
                player_defends= true;
            }
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

        if(west_random_options<=7)
        {   bool player_defends = false;
            cout<<"\n"<<west_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 1)
            {
                player_defends= true;
            }
            number_of_wars++;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population, land, infantry_military, air_military,
                                                     west_population, west_infantry_military, west_air_military);
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

        if(south_random_options<=7)
        {   bool player_defends = false;
            cout<<"\n"<<south_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 1)
            {
                player_defends= true;
            }
            number_of_wars++;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population, land, infantry_military, air_military,
                                                     south_population, south_infantry_military, south_air_military);
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

        if(east_random_options<=7)
        {   bool player_defends = false;
            cout<<"\n"<<east_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            int choice;
            sentinelFunction(0,1,choice);
            if (choice == 1)
            {
                player_defends= true;
            }
            number_of_wars++;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population, land, infantry_military, air_military,
                                                     east_population, east_infantry_military, east_air_military);
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

        //If random choice happens to be greater than 45, the countries build a new military factory
        if(north_random_options>44)
        {
            cout<<"It seems "<<north_name<<" may have invested in their military, perhaps we should too?\n";
            north_military_factory= north_military_factory+1;
        }
        if(south_random_options>44)
        {
            cout<<"It seems "<<south_name<<" may have invested in their military, perhaps we should too?\n";
            south_military_factory= south_military_factory+1;
        }
        if(east_random_options>44)
        {
            cout<<"It seems "<<east_name<<" may have invested in their military, perhaps we should too?\n";
            east_military_factory= east_military_factory+1;
        }
        if(west_random_options>44)
        {
            cout<<"It seems "<<west_name<<" may have invested in their military, perhaps we should too?\n";
            west_military_factory= west_military_factory+1;
        }
        //Theres a 2% chance that a nation will declare all out war on the player
        if(north_random_options==25)
        {
            number_of_wars++;
            cout<<north_name<<" is declaring all-out war on you! This is not a drill!\n";
            bool war_win = war_Room(air_military, infantry_military, land, population, north_air_military,
                                    north_infantry_military, player_name, year, commerce, city, military_factory, check_war_room);
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
        if(south_random_options==25)
        {
            number_of_wars++;
            cout<<south_name<<" is declaring all-out war on you! This is not a drill!\n";
            bool war_win = war_Room(air_military, infantry_military, land, population, south_air_military,
                                    south_infantry_military, player_name, year, commerce, city, military_factory, check_war_room);
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
        if(east_random_options==25)
        {
            number_of_wars++;
            cout<<east_name<<" is declaring all-out war on you! This is not a drill!\n";
            bool war_win = war_Room(air_military, infantry_military, land, population, east_air_military,
                                    east_infantry_military, player_name, year, commerce, city, military_factory, check_war_room);
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
        if(west_random_options==25)
        {
            number_of_wars++;
            cout<<west_name<<" is declaring all-out war on you! This is not a drill!\n";
            bool war_win = war_Room(air_military, infantry_military, land, population, west_air_military,
                                    west_infantry_military, player_name, year, commerce, city, military_factory, check_war_room);
            if(war_win)
            {

                number_of_wars_won++;
                // Happiness Effects of winning the war
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
                game_over= true;
                lost_game_overthrown = true;
                continue;
            }

        //Added land revenue from commerce
        commerce = commerce + (CITY_COMMERCE_GAIN*city) -(FACTORY_UPKEEP*military_factory) + (land * LAND_COMMERCE_GAIN) ; // Every city will add 2000 units of commerce and military factories reduce commerce due to maintenance

        if (city < 1)
            {
            game_over = true;
            lost_game_city = true;
            continue;
            }
        if (gdp < 10)
        {
            cout << endl << "YOUR GDP IS RUNNING LOW. THE PEOPLE ARE GETTING ANGRY! \n";
            happiness_factor = happiness_factor -20;
            system("pause");
        }

        if( happiness_factor < 41 )
        {
            protest(total_mili,commerce,happiness_factor,population);
        }



        if (gdp > GDP_WIN)
        {

            game_over = true;
            game_won_gdp = true;
            continue;
        }




    }
    //End game condition verification



    cumulative_score = (gdp*population)/(year-1921);
    Endscore score;
    score.name = player_name;
    score.score = cumulative_score;
    score.wars_won = number_of_wars_won;
    score.land = land;
    if(game_over && lost_game_quit)
    {
        cout<<"YOU QUIT THE GAME"<<endl;
        cout<<"Couldn't handle the heat, could you, "<<player_name<<"?\n";
        cout<<"Having a nation depend upon you isn't everyone's cup of tea after all";
    }
    else if(game_over && lost_game_city)
    {
        cout<<"YOU'VE LOST ALL YOUR CITIES"<<endl;
        cout<<player_name<<", how can you expect to run a nation without a city to run it from?\n";
        cout<<"Your nation lays in rubble, it's dreams of a prosperous future turned to ashes!\n";
    }
    else if(game_over && lost_game_overthrown)
    {
        cout<<"YOU'VE BEEN OVERTHROWN BECAUSE YOUR PEOPLE WERE TOO UNHAPPY"<<endl;
    }
    else if(game_over && lost_game_gdp)
    {
        cout<<"WITH A GDP OF "<<gdp<<" YOUR PEOPLE NOW LIVE IN ABSOLUTE POVERTY"<<endl;
        cout<<player_name<<", you have lost the game, and with that, the promise of a brighter future for your nation"<<endl;
    }
    else if(game_over && game_won_gdp)
    {
        cout<<"Congratulations "<<player_name<<". You have done something truly remarkable and turned your nation into a super power\n";
        cout<<"YOU HAVE WON THE GAME!"<<endl;
        cout<<"======================"<<endl;
        cout<<"Your final score is = "<<cumulative_score<<endl;
        cout<<"Your GDP was "<<gdp<<" at the end of the game!\n";
    }



}

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
//Workdate/time 6:22 pm, 18-Nov-2018

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
bool player_wins_war(int& player_pop, int& player_land, int& player_mili, int& neighbour_pop, int& neighbour_mili);
bool win_war_Skirmish(int& population, int& land, int& military); //stub. Must be replaced!!!
int d100_Random_Roll();
int d10_Random_Roll();
void player_Surrender(int& pop, int& land, int& military);

void starvationFactor(int& population, int food_stores)
{
    population = population*0.50;
}

int main()
{
    //initial conditions;

    int population, military, commerce, military_factory, land, food, happiness_factor;
    population = 100000;
    military = 1000;
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



    //Neighbour land values are inconsequential
    int north_id=1;
    string north_name="";
    int north_population=100000;
    int north_military=10000;
    int north_commerce=10000000;
    int north_gdp;
    int north_military_factory=1;
    int north_land=1000;
    //growth
    double north_population_growth = 1.05;
    double north_commerce_growth = 1.15;
    double north_military_growth = military_factory*25;


    int south_id=2;
    int east_id =3;
    int west_id =4;

    while(!game_over)
    {
        //resetting AI values
        int north_land = 1000;
        //growth factors:
        gdp = (commerce)/population;

        //output
        cout<<"CURRENT YEAR:                "<<year<<endl<<endl;
        cout<<"Current population:          "<<population<<endl;
        cout<<"Current food stocks:         "<<food_stores<<endl;
        cout<<"Current owned land:          "<<land<<endl;
        cout<<"Current Military might:      "<<military<<endl;
        cout<<"Current Military factories   "<<military_factory;
        if(building_factory){cout<<"(1)"<<endl;}
        else {cout<<endl;}
        cout<<"Current Commercial prowess:  "<<commerce<<endl;
        cout<<"Current GDP/Capita:          $"<<gdp<<endl;
        cout<<"Total number of wars:        "<<number_of_wars<<endl;
        cout<<"Total wars won:              "<<number_of_wars_won<<endl;
        cout<<"Happiness Level of Population: "<< happiness_factor<<"%"<<endl;

        //North


        //growth
        pop_grow = 1+ ((double)food/population)/100;
        cout<<pop_grow<<endl;
        food_grow = land*1000;
        mili_grow = military_factory*25;

        food_stores = (food_stores - population) + (food_grow);
        population = population*pop_grow;
        military = military+mili_grow;
        cout<<"\nPopulation growth: "<<pop_grow<<endl;

        if(food_stores<0)
        {
            food_stores = 0;
            starvationFactor(population,food_stores);

        }

        //game time
        cout<<"1) Go to war (skirmish)\n"
              "2) Build military factory\n"
              "3) Random invention\n"
              "4) quit simulation\n";
        cin>>next_year_option;
        if(next_year_option==1)
        {
            number_of_wars++;
            bool war_win = win_war_Skirmish(population, land, military);
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
            building_factory = true;
            remaining_construction_time = 3;
        }
        else if(next_year_option==4)
        {
            game_over = true;
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
        north_military = north_military + north_military_growth;
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
        {   bool player_defends = false;
            cout<<"\n"<<north_name<<" has declared war on you!\n";
            cout<<"Press 1 to defend, or 0 to concede:\n";
            cin>>player_defends;
            if(player_defends)
            {
                bool player_victory= player_wins_war(population,land,military,north_population,north_military);
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
                player_Surrender(population, land, military);
                happiness_factor = happiness_factor - 10;

            }
        }



        year++;
    }
}
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
bool player_wins_war(int& player_pop, int& player_land, int& player_mili, int& neighbour_pop, int& neighbour_mili)
{
    int chance = d100_Random_Roll();
    double win_pop = 0.90, win_land = 1.15, win_mil = 0.85;
    double loss_pop= 0.75, loss_land= 0.90, loss_mil= 0.70;

    if(chance>50)
    {
        player_pop      =player_pop         *win_pop;
        player_land     =player_land        *win_land;
        player_mili     =player_mili        *win_mil;
        neighbour_pop   =neighbour_pop      *loss_pop;
        neighbour_mili  =neighbour_mili     *loss_mil;
        return true;
    }
    else
    {
        player_pop      =player_pop         *loss_pop;
        player_land     =player_land        *loss_land;
        player_mili     =player_mili        *loss_mil;
        neighbour_pop   =neighbour_pop      *win_pop;
        neighbour_mili  =neighbour_mili     *win_mil;
        return false;
    }
}

void player_Surrender(int& pop, int& land, int& military)
{
    double poploss = 0.95, landloss=0.80, milloss=0.80;
    pop = pop*poploss;
    land = land*landloss;
    military = military*milloss;
}

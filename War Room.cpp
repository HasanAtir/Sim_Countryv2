#include <iostream>
#include <cmath>
#include <ctime>
#include  <cstdlib>

using namespace std;


int d10_Random_Roll() // Digits b/w 1-10
{
    int random = rand();
    int output = random%10;
    return output;
}


int d100_Random_Roll() // Digits b/w 1-100
{


    int random = rand();
    int output = random%100;
    return output;
}



bool WarRoom (int &air_player, int &air_computer, int &infantry_player, int &infantry_computer)
{

    int hp_enemy = 10;
    int hp_player = 10;
    int total_player = air_player+infantry_player;
    int total_computer = air_computer+infantry_computer;
    float const WIN = 0.9; // Win prob
    float const LOSE = 0.75; // Loss prob

    cout << "WELCOME TO THE WAR ROOM" << endl;
    cout << "AIRFORCE = JETS. ANTI PLANE GUNS EXIST EXCLUSIVE OF AIRFORCE AND CANNOT BE DESTROYED" << endl;
    cout << "INFANTRY = FOOTSOLDIERS. TANKS EXIST EXCLUSIVE OF INFANTRY AND CANNOT BE DESTROYED" << endl;
    cout << "MAY THE BEST COUNTRY WIN" << endl;



    do{
    int chance = d10_Random_Roll(); // Chance of you winning
    int chance_intel= d10_Random_Roll(); // Chance of receiving intel

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

    cin >> choice;
    // Game interaction
    {

 if (choice == 1)
    {

        {if (air_player > air_computer){
            {if ( chance >= 4)
               {
                cout << "You win the battle"<< endl;
                hp_enemy--;
                air_computer = air_computer*LOSE;
                air_player = air_player*WIN;
                }
            else
                {
                cout << "You lost the battle"<< endl;
                hp_player--;
                air_computer = air_computer*WIN;
                air_player = air_player*LOSE;
                }}

        }
        else if (air_player < air_computer)
            {if (chance < 4)
                {
                cout << "You win the battle"<< endl;
                hp_enemy--;
                air_computer = air_computer*LOSE;
                air_player = air_player*WIN;
                }
            else
                {
                cout << "You lost the battle" << endl;
                hp_player--;
                air_computer = air_computer*WIN;
                air_player = air_player*LOSE;
                }}
        else
            {if (chance < 5)
                {
                cout << "You win the battle" << endl;
                hp_enemy--;
                air_computer = air_computer*LOSE;
                air_player = air_player*WIN;
                }
            else
                {
                cout << "You lose the battle" << endl;
                hp_player--;
                air_computer = air_computer*WIN;
                air_player = air_player*LOSE;
                }}}
    }
    else if (choice == 2)
    {
        if (infantry_player > infantry_computer)
            {if ( chance >= 4)
                {cout << "You win the battle"<< endl;
                 hp_enemy--;
                 infantry_computer = infantry_computer*LOSE;
                 infantry_player = infantry_player*WIN;
                }
            else
                {
                    cout << "You lost the battle"<< endl;
                    hp_player--;
                    infantry_computer = infantry_computer*WIN;
                 infantry_player = infantry_player*LOSE;
                }}
        else if (infantry_player < infantry_computer)
            {if (chance < 4)
                {
                    cout << "You win the battle"<< endl;
                    hp_enemy--;
                    infantry_computer = infantry_computer*LOSE;
                 infantry_player = infantry_player*WIN;
                }
            else
                {
                    cout << "You lost the battle" << endl;
                    hp_player--;
                    infantry_computer = infantry_computer*WIN;
                 infantry_player = infantry_player*LOSE;
                }}
        else
            {if (chance < 5)
                {
                    cout << "You win the battle" << endl;
                    hp_enemy--;
                    infantry_computer = infantry_computer*LOSE;
                 infantry_player = infantry_player*WIN;
                }
            else
                {
                    cout << "You lose the battle" << endl;
                    hp_player--;
                    infantry_computer = infantry_computer*WIN;
                 infantry_player = infantry_player*LOSE;
                }}
    }
    else if (choice == 3)
    {
        {if (total_player > total_computer)
            {if ( chance >= 4)
                {
                    cout << "You win the battle"<< endl;
                    hp_enemy--;
                    infantry_computer = infantry_computer*LOSE;
                    infantry_player = infantry_player*WIN;
                    air_computer = air_computer*LOSE;
                    air_player = air_player*WIN;
                }
            else
                {
                    cout << "You lost the battle"<< endl;
                    hp_player--;
                    infantry_computer = infantry_computer*LOSE;
                    infantry_player = infantry_player*WIN;
                    air_computer = air_computer*WIN;
                    air_player = air_player*LOSE;                }}
        else if (total_player < total_computer)
            {if (chance < 4)
                {
                    cout << "You win the battle"<< endl;
                    hp_enemy--;
                    infantry_computer = infantry_computer*LOSE;
                    infantry_player = infantry_player*WIN;
                    air_computer = air_computer*LOSE;
                    air_player = air_player*WIN;
                }
            else
                {
                    cout << "You lost the battle" << endl;
                    hp_player--;
                    infantry_computer = infantry_computer*WIN;
                    infantry_player = infantry_player*LOSE;
                    air_computer = air_computer*WIN;
                    air_player = air_player*LOSE;
                }}
        else
            {if (chance < 5)
                {
                    cout << "You win the battle" << endl;
                    hp_enemy--;
                    infantry_computer = infantry_computer*LOSE;
                    infantry_player = infantry_player*WIN;
                    air_computer = air_computer*LOSE;
                    air_player = air_player*WIN;
                }
            else
                {
                    cout << "You lose the battle" << endl;
                    hp_player--;
                    infantry_computer = infantry_computer*WIN;
                    infantry_player = infantry_player*LOSE;
                    air_computer = air_computer*WIN;
                    air_player = air_player*LOSE;
                }}}
    }
    }
    }
    while(hp_player!=0 && hp_enemy!=0);

    if (hp_player == 0)
    {
        cout << "You lost the war" << endl;
    }
    else if (hp_enemy == 0)
    {
        cout << "You won the war" << endl;
    }


}

int main()
{
    srand(time(0));
    int airforce = d100_Random_Roll();
    int infantry = d100_Random_Roll();

    int airforce_c= d100_Random_Roll();
    int infantry_c= d100_Random_Roll();

    WarRoom(airforce,airforce_c,infantry,infantry_c);

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Random_Number_Generator
{
private:
    int Number_Generated;
    int Attempts;

public:
    Random_Number_Generator(); // Constructor

    void Play_game(); // Check number

    ~Random_Number_Generator(); // Destructor
};

/*Takes input from user->
Check if gusses is correct or high or low->
Does recursive call untill correct no is gussed->*/
void Random_Number_Generator::Play_game()
{
    int Number_guessed;

    cout << "Enter the number: ";
    cin >> Number_guessed;

    Attempts++;

    if (Number_Generated == Number_guessed)
    {
        cout << "You have guessed the correct number in " << Attempts << " attempts!!!" << endl;
    }
    else if (Number_guessed < Number_Generated)
    {
        cout << "Value is too low, maybe you go higher?" << endl;
        Play_game();
    }
    else
    {
        cout << "Value is too high, maybe guess lower?" << endl;
        Play_game();
    }
}

Random_Number_Generator::Random_Number_Generator()
{
    srand(time(0));                     // Generates differnt no everytime->
    Number_Generated = rand() % 30 + 1; // Generates no between 1 to 30->
    Attempts = 0;
}

Random_Number_Generator::~Random_Number_Generator()
{
    cout << "Thank you for playing the game :)" << endl;
}

int main()
{
    cout << "Hello! this the number gussing game." << endl;
    cout << "A number is selected between 1 to 30 at random, try to guess it!" << endl;
    
    Random_Number_Generator Lets_play;

    Lets_play.Play_game();

    return 0;
}

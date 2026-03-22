#include <iostream>
#include <string>
using namespace std;

enum class Choice { Rock, Scissors, Paper, Invalid };

Choice getComputerChoice()
{
    int randomValue = rand() % 3;
    return static_cast<Choice>(randomValue);
}

Choice getChoice(const int& input)
{
    if (input == 1) return Choice::Rock;
    if (input == 2) return Choice::Scissors;
    if (input == 3) return Choice::Paper;
    return Choice::Invalid;
}


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int userInput;
    cout << "Enter your choice ( rock[1], scissors[2], paper[3]): ";
    cin >> userInput;

    Choice userChoice = getChoice(userInput);

    if (userChoice == Choice::Invalid)
    {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    Choice computerChoice = getComputerChoice();

    // Display choices
    cout << "Computer chose: ";
    switch (computerChoice)
    {
        case Choice::Rock: cout << "rock" << endl; break;
        case Choice::Scissors: cout << "scissors" << endl; break;
        case Choice::Paper: cout << "paper" << endl; break;
        default: break;
    }

    if (userChoice == computerChoice)
    {
        cout << "It's a tie!" << endl;
    }
    else if ((userChoice == Choice::Rock && computerChoice == Choice::Scissors) ||
             (userChoice == Choice::Scissors && computerChoice == Choice::Paper) ||
             (userChoice == Choice::Paper && computerChoice == Choice::Rock))
    {
        cout << "You win!" << endl;
    }
    else
    {
        cout << "Computer wins!" << endl;
    }

    return 0;
}
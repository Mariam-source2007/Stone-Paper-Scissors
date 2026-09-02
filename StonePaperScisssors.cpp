#include <iostream>
#include <ctype.h>
using namespace std;
enum EnChoices { Stone=1 , Paper=2 , Scissors=3};
enum EnWinner { Player=1 , Computer=2, NoWinner=3};
struct StScores
{
    int ComputerWinTimes=0;
    int PlayerWinTimes=0;
    int DrawTimes=0;
};

// Ask User If He/She want to play again

bool AskPlayerToPlayAgain()
{
    char PlayOrNot;
    cout<<"Do You Want to Play Again [Y/N] ?";
    cin>>PlayOrNot;
    if(tolower(PlayOrNot)=='y') return true;
    else return false;
}

// Ask User how many times they want to play

int GetRoundTimes()
{
    int RoundTimes;
    cout<<"How many Rounds 1 to 10 ?\n";
    cin>>RoundTimes;
    return RoundTimes;
}
EnChoices GetPlayerChoice()
{
    int PlayerNumber;
    cout<<"Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
    cin>>PlayerNumber;
    EnChoices PlayerChoice=(EnChoices)PlayerNumber;
    return PlayerChoice;
}

// to Get Random value for computer 

int Random()
{
    return rand()%3+1;
}
EnChoices GetComputerChoice()
{
    int ComputerNumber=Random();
    EnChoices ComputerChoice=(EnChoices)ComputerNumber;
    return ComputerChoice;
}

// Compare two choices to know who wins


EnWinner DetermineRoundWinner(EnChoices PlayerChoice, EnChoices ComputerChoice)
{
    EnWinner Winner;
    if(PlayerChoice==EnChoices::Paper && ComputerChoice==EnChoices::Paper)
    {
        Winner=EnWinner::NoWinner;
    }
    else if(PlayerChoice==EnChoices::Stone && ComputerChoice==EnChoices::Stone)
    {
        Winner=EnWinner::NoWinner;
    }
    else if(PlayerChoice==EnChoices::Scissors && ComputerChoice==EnChoices::Scissors)
    {
        Winner=EnWinner::NoWinner;
    }
    else if(PlayerChoice==EnChoices::Paper && ComputerChoice==EnChoices::Scissors)
    {
        Winner=EnWinner::Computer;
    }
    else if(PlayerChoice==EnChoices::Scissors && ComputerChoice==EnChoices::Paper)
    {
        Winner=EnWinner::Player;
    }
    else if(PlayerChoice==EnChoices::Paper && ComputerChoice==EnChoices::Stone)
    {
        Winner=EnWinner::Player;
    }
    else if(PlayerChoice==EnChoices::Stone && ComputerChoice==EnChoices::Paper)
    {
        Winner=EnWinner::Computer;
    }
    else if(PlayerChoice==EnChoices::Scissors && ComputerChoice==EnChoices::Stone)
    {
        Winner=EnWinner::Computer;
    }
    else if(PlayerChoice==EnChoices::Stone && ComputerChoice==EnChoices::Scissors)
    {
        Winner=EnWinner::Player;
    }
    return Winner;
}

// update scores after every round to determine the final winner in GameOver fn


void UpdateScores(EnWinner Winner, StScores &Scores)
{
    if(Winner==EnWinner::Computer) Scores.ComputerWinTimes++;
    else if(Winner==EnWinner::Player) Scores.PlayerWinTimes++;
    else if(Winner==EnWinner::NoWinner) Scores.DrawTimes++;
}


// Convert enum int value to string to print it 


string PlayerChoiceToString(EnChoices PlayerChoice)
{
    switch(PlayerChoice)
    {
        case EnChoices::Paper:
        return "Paper";
        break;
        case EnChoices::Scissors:
        return "Scissors";
        break;
        case EnChoices::Stone:
        return "Stone";
        break;
    }
    return "";
}
string ComputerChoiceToString(EnChoices ComputerChoice)
{
    switch(ComputerChoice)
    {
        case EnChoices::Paper:
        return "Paper";
        break;
        case EnChoices::Scissors:
        return "Scissors";
        break;
        case EnChoices::Stone:
        return "Stone";
        break;
    }
    return "";
}
string WinnerToString(EnWinner Winner)
{
    switch(Winner)
    {
        case EnWinner::Computer:
        return "Computer";
        break;
        case EnWinner::NoWinner:
        return "No Winner";
        break;
        case EnWinner::Player:
        return "Player";
        break;
    }
    return "";
}


// Determine which color appear on terminal based on the winner


void RoundColor(EnWinner Winner)
{
    if(Winner==EnWinner::Computer)
    {
        cout<<'\a';
        system("color 0C");
    }
    else if(Winner==EnWinner::Player)
    {
        cout<<'\a';
        system("color 0A");
    }
    else if(Winner==EnWinner::NoWinner)
    {
        cout<<'\a';
        system("color 0E");
    }
}

// Determine the final winner based on scores uodateed after every round

EnWinner DetermineFinalWinner(StScores &Scores)
{
    EnWinner FinalWinner;
    if(Scores.ComputerWinTimes>Scores.PlayerWinTimes) FinalWinner=EnWinner::Computer;
    else if(Scores.ComputerWinTimes<Scores.PlayerWinTimes) FinalWinner=EnWinner::Player;
    if(Scores.ComputerWinTimes==Scores.PlayerWinTimes) FinalWinner=EnWinner::NoWinner;
    return FinalWinner;
}


// when game is done we will v=call this fn to terminate the game and announce the results 


void GameOver(int RoundTimes, StScores &Scores, EnWinner FinalWinner)
{
    cout<<"\t\t\t\t\t__________________________________________\t\t\t\n\n";
    cout<<"\t\t\t\t\t\t + + + G A M E O V E R + + + \t\t\t\t\t\t\n";
    cout<<"\t\t\t\t\t___________________________________________\t\t\t\n\n";
    cout<<"Game Rounds        : "<<RoundTimes<<endl;
    cout<<"Player won times   : "<<Scores.PlayerWinTimes<<endl;
    cout<<"Computer won times : "<<Scores.ComputerWinTimes<<endl;
    cout<<"Draw times         : "<<Scores.DrawTimes<<endl;
    cout<<"Final Winner       : "<<WinnerToString(FinalWinner)<<endl;
    cout<<"___________________________________________________________________________________________________________________________\n\n";
}
// The core , the fn all in all

void StonePaperScissorsGame()
{
    int RoundTimes=GetRoundTimes();
    StScores Scores;
    for(int i=1;i<=RoundTimes;i++)
    {
        cout<<"Round ["<<i<<"] Begins :\n";
        EnChoices PlayerChoice=GetPlayerChoice();
        EnChoices ComputerChoice=GetComputerChoice();
        EnWinner Winner=DetermineRoundWinner(PlayerChoice,ComputerChoice);
        RoundColor(Winner);
        UpdateScores(Winner,Scores);
        cout<<"____________________________________________________ Round ["<<i<<"] ______________________________________________________\n\n";
        cout<<"Player Choice : "<<PlayerChoiceToString(PlayerChoice)<<endl;
        cout<<"Computer Choice : "<<ComputerChoiceToString(ComputerChoice)<<endl;
        cout<<"Round Winner : ["<<WinnerToString(Winner)<<"]"<<endl;
        cout<<"_________________________________________________________________________________________________________________________\n\n";
    }
    EnWinner FinalWinner=DetermineFinalWinner(Scores);
    GameOver(RoundTimes,Scores,FinalWinner);
}
int main()
{
    srand((unsigned)time(NULL));
    do // player will play at least one time
    {
        system("cls"); //clear the screen before a new game
        StonePaperScissorsGame();
    } while (AskPlayerToPlayAgain());
}
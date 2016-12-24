/* This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// In UNREAL we use FText for interaction with the user.
using FText = std::string;
using int32 = int;

// Function prototypes as outside a class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game which we *re-use across plays*

// App entrypoint
int main()
{
	do{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	
	return 0;
}


void PrintIntro()
{
	std::cout << "Hello you big cunt" << "\n\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

// Plays a single game until completion
void PlayGame()
{
	BCGame.Reset();

	FText Guess = "";
	int32 maxTries = BCGame.GetMaxTries();
	std::cout << maxTries << std::endl;

	// loop for the number of turns asking for guesses
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries)
	{
		Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//print num of bulls & cows
		std::cout << "RESULTS:-----------------\n";
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << "\n\n";

		// increment the turn number
		BCGame.incrementCurrentTry();
	}

	PrintGameSummary();
}

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {		
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Your current try is: " << currentTry << " of " << BCGame.GetMaxTries() << "\nEnter your guess...\n";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "\nError - Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
			//return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get valid input (or no errors)
	return Guess;
}

bool AskToPlayAgain()
{
	FText yesOrNo = "";
	std::cout << "\nDo you want to play again? y or n...\n";
	std::cin;
	std::getline(std::cin, yesOrNo);

	return (yesOrNo[0] == 'y') || (yesOrNo[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congrats!";
	}
	else {
		std::cout << "Unlucky!";
	}
}

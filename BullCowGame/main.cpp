/* This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// In UNREAL we use FText for interaction with the user.
using FText = std::string;
using int32 = int;

// Contract / Overview of what we are going to implement below main entrypoint.
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

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
	std::cout << "Hello you big cunt" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

void PlayGame()
{
	// Reset the game.
	BCGame.Reset();

	FText Guess = "";
	int32 maxTries = BCGame.GetMaxTries();
	std::cout << maxTries << std::endl;

	// loop for the number of turns asking for guesses
	// TODO change from for to while loop once we are validating tries
	constexpr int32 numberOfTurns = 5;
	for (int32 i = 0; i < numberOfTurns; i++) 
	{
		// Get guess from the player
		Guess = GetValidGuess(); // TODO make loop checking valid

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		//print num of bulls & cows
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << "\n\n";

		// increment the turn number
		BCGame.incrementCurrentTry();
	}

	// TODO summarise the game
}

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Your current try is: " << currentTry << "\nEnter your guess...";
		FText Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			//break;
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get valid input (or no errors)
}

bool AskToPlayAgain()
{
	FText yesOrNo = "";
	std::cout << "Do you want to play again? y or n...\n";
	std::cin;
	std::getline(std::cin, yesOrNo);

	return (yesOrNo[0] == 'y') || (yesOrNo[0] == 'Y');
}
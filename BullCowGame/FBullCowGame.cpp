#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
void FBullCowGame::incrementCurrentTry() { MyCurrentTry++; }

void FBullCowGame::Reset()
{
	// we should establish constants as much as possible.
	// constexpr are known at compile time.
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

// Inside the game logic we use FString as std::string, not FText
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (false)
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

	return EGuessStatus::OK; // todo: make actual error
}

// Receives a valid guess, increments
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// setup a return variable
	FBullCowCount BullCowCount = FBullCowCount();

	// loop thru all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessLength = Guess.length();

	// we cannot iterate past the length of the smallest word.
	/*if (HiddenWordLength > GuessLength)
		HiddenWordLength = GuessLength;*/
	
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < GuessLength; j++)
		{
			// if they match and in same place then increment bulls
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	return BullCowCount;
}



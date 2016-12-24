/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind.
*/

#pragma once

#include "FBullCowGame.h"
#include <map>// copy paste <map> code on top here, making std:map accessible
#define TMap std::map//textual replacement of TMap for all std::map

// we use #define instead of #using here because:
//1. its another way to do it, a cut and paste
//2. have to get involved with parameters for TMap

// To make the syntax Unreal friendly.
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
void FBullCowGame::incrementCurrentTry() { MyCurrentTry++; }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset()
{
	// we should establish constants as much as possible.
	// constexpr are known at compile time.
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,10},{6,15},{7,20} };
	
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// Inside the game logic we use FString as std::string, not FText
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
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

	return EGuessStatus::OK;
}

// Receives a valid guess, increments
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
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
	
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter words as isograms.
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> Map;

	//for (int32 i = 0; i < Guess.length(); i++) {
	for (auto letter : Guess) 
	{
		letter = tolower(letter);
		if (Map[letter]) {
			return false;
		}
		else {
			Map[letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	// Check through all letters making sure they are all lowercase
	for (auto letter : Guess) {
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

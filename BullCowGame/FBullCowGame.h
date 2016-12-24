#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// We will introduce some new type which counts bulls and cows and increments turn number.
// All values initialized to 0.
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows= 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString); // todo make a more rich return value

	void Reset();
	FBullCowCount SubmitGuess(FString);
	void incrementCurrentTry();
	
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};
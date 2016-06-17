//
//  FGame.hpp
//  HangMan
//
//  Created by Eric Peterford on 5/17/16.
//  Copyright © 2016 Eric Peterford. All rights reserved.
//

#ifndef FGame_hpp
#define FGame_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using int32 = int;
using FString = std::string;

enum class EGameOverStatus
{
    Invalid,
    WrongWord,
    WordGuessed,
    AllLettersGuessed,
    Hung
};

class FGame
{
public:
    FGame();
    void DrawBoard();
    void PrintHiddenWordProgress();
    void CheckWordGuess(FString);
    void CheckLetterGuess(char);
    void CheckWordProgress();
    
    EGameOverStatus CheckGameoverStatus() const;
    
    FString hiddenWord;
    
private:
    // Creates array of possible hidden words from given txt file
    void GenerateListOfWords();
    
    // Selects a random word from hidden word array
    FString SelectRandomWord();
    
    int32 numWrongGuesses;
    FString lettersGuessed = "";
    bool bAllLettersGuessed;
    bool bCorrectWordGuessed;
    bool bWrongWordGuessed;
};
#endif /* FGame_hpp */

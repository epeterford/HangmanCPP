//
//  FGame.cpp
//  HangMan
//
//  Created by Eric Peterford on 5/17/16.
//  Copyright © 2016 Eric Peterford. All rights reserved.
//

#include "FGame.hpp"
#include <map>
#include <time.h>

#define TMap std::map

std::vector<FString> words; // List of possible hidden words

// Setup our maps
TMap<char, bool> HiddenWordMap;
TMap<char, bool> LetterMap;

FGame::FGame() // Constructor
{
    lettersGuessed = "";
    bAllLettersGuessed = false;
    bCorrectWordGuessed = false;
    bWrongWordGuessed = false;
    numWrongGuesses = 0;
    GenerateListOfWords();
    hiddenWord = SelectRandomWord();
    
}

void FGame::GenerateListOfWords()
{
    FString line;
    std::ifstream myfile ("hangmaninput.txt" , std::ios_base::in | std::ios_base::binary);
    if(myfile.is_open())
    {
        while(std::getline(myfile, line))
        {
            words.push_back(line);
        }
        
        myfile.close();
    }
    else{
        std::cout<<"Unable to open file";
    }
}

FString FGame::SelectRandomWord()
{
    srand (time(NULL));
    
    int32 randomWord = rand() % words.size() + 0;
    
    for(auto Letter : hiddenWord)
    {
        HiddenWordMap[Letter] = false;
    }
    
    return words[randomWord];
}

void FGame::DrawBoard()
{
    switch (numWrongGuesses) {
        case 1:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |\n";
            std::cout<<" |\n";
            std::cout<<" |\n";
            std::cout<<"_|______\n\n";
            break;
        case 2:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |      |\n";
            std::cout<<" |      |\n";
            std::cout<<" |\n";
            std::cout<<"_|______\n\n";
            break;
        case 3:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |     \\|\n";
            std::cout<<" |      |\n";
            std::cout<<" |\n";
            std::cout<<"_|______\n\n";
            break;
        case 4:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |     \\|/\n";
            std::cout<<" |      |\n";
            std::cout<<" |\n";
            std::cout<<"_|______\n\n";
            break;
        case 5:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |     \\|/\n";
            std::cout<<" |      |\n";
            std::cout<<" |     / \n";
            std::cout<<"_|______\n\n";
            break;
        case 6:
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |     (_)\n";
            std::cout<<" |     \\|/\n";
            std::cout<<" |      |\n";
            std::cout<<" |     / \\\n";
            std::cout<<"_|______\n\n";
            break;
        default: // 0 wrong guesses
            std::cout<<"  _______\n";
            std::cout<<" |/     |\n";
            std::cout<<" |\n";
            std::cout<<" |\n";
            std::cout<<" |\n";
            std::cout<<" |\n";
            std::cout<<"_|______\n\n";
            break;
    }
}

void FGame::PrintHiddenWordProgress()
{
    bAllLettersGuessed = true;
    // loop through all the letters of the hidden word
    for(auto Letter : hiddenWord) // for all letters of the word
    {
        if(HiddenWordMap[Letter]) // if letter was guessed
        {
            Letter = toupper(Letter);
            std::cout<<Letter<<" "; // display letter
        }
        else // otherwise
        {
            bAllLettersGuessed = false;
            std::cout<<"_ "; // display blank
        }
    }
    std::cout<<std::endl<<"guessed letters:["<<lettersGuessed<<"]";
    std::cout<<std::endl<<std::endl;
    
}

void FGame::CheckWordProgress()
{
    bAllLettersGuessed = true;
    // Loop through all the letters of the hidden word
    for(auto Letter : hiddenWord) // For all letters of the word
    {
        if(!HiddenWordMap[Letter]) // If letter was guessed
        {
             bAllLettersGuessed = false;
        }
    }
    
}
void FGame::CheckWordGuess(FString guess)
{
    if(guess!=hiddenWord)
    {
        bWrongWordGuessed = true;
        
    }
    else
    {
        bCorrectWordGuessed = true;
    }

}

void FGame::CheckLetterGuess(char guess) 
{
    int32 correctGuessCount = 0; // counts same letters
    bool bCorrectGuess = false; // is a correct guess made
    
    if(LetterMap[guess] == true)
    {
        std::cout<<"You already guessed this letter. Try again!\n";
        return;
    }
    else
    {
        LetterMap[guess] = true;
    }
    for(auto Letter : hiddenWord) // for all letters of the word
    {
        if(guess == Letter) // if letter was guessed
        {
            HiddenWordMap[Letter] = true;
            
            correctGuessCount++;
            bCorrectGuess = true; // player made a correct guess
        }
    }
    guess = toupper(guess);
    if(!bCorrectGuess) // if a correct guess wasn't made
    {
        std::cout<<"\nSorry! There are no " <<guess<<"'s in the hidden word.\n";
        
        numWrongGuesses++;
    }
    else // otherwise
    {
        //Determine correct sentence based on number of same letters guessed
        if(correctGuessCount==1)
        {
             std::cout<<"\nCorrect! There is 1 "<<guess<<" in the hidden word.\n\n";
        }
        else
        {
             std::cout<<"\nCorrect! There are "<<correctGuessCount<<" "<<guess<<"'s in the hidden word.\n\n";
        }
    }
    lettersGuessed.append(1, tolower(guess));
}

EGameOverStatus FGame::CheckGameoverStatus() const
{
    if(numWrongGuesses>5) // out of guesses
    {
        return EGameOverStatus::Hung;
    }
    else if(bAllLettersGuessed) // guessed all letters
    {
        return EGameOverStatus::AllLettersGuessed;
    }
    else if(bCorrectWordGuessed) // guessed correct word
    {
        return EGameOverStatus::WordGuessed;
    }
    else if(bWrongWordGuessed) // guessed wrong word
    {
        return EGameOverStatus::WrongWord;
    }
    else{ // still guessing
        return EGameOverStatus::Invalid;
    }
}


//
//  main.cpp
//  HangMan
//
//  Created by Eric Peterford on 5/16/16.
//  Copyright © 2016 Eric Peterford. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector> 
#include "FGame.hpp"

// Make Unreal friendly
using int32 = int;
using FString = std::string;

void PrintWelcome();
void PrintGameOver();
FString GetValidGuess();

bool bGameOver = false;

// Create a new game
FGame newGame;

int32 main() // Entry to application
{
    PrintWelcome(); // Welcome player
    
    do
    {
        newGame.DrawBoard(); // Draw current board
        newGame.PrintHiddenWordProgress(); // Print current hidden word progress
        
        FString guess = GetValidGuess(); // Retreives a valid guess from the player
        
        if(guess.size()>1) // If guess is more than one character
        {
            // Player entered a word guess
            newGame.CheckWordGuess(guess);
            
        }
        else // otherwise
        {
            // Player entered a letter guess
            char letterGuess = guess[0]; // convert string to char
            newGame.CheckLetterGuess(letterGuess);
        }
        
        newGame.CheckWordProgress();
        
    }while(newGame.CheckGameoverStatus()==EGameOverStatus::Invalid); // While game is still in progress
    
    PrintGameOver();
    return 0;
    
}

void PrintWelcome()
{
    //Introduce the game
    std::cout<<"Welcome to HANGMAN!\n\n";
    std::cout<<"The way to play is simple: A hidden word has been secretly chosen and it is up to you to find out what it is.\n\nIf you guess a letter and it is correct, you are one step closer in solving the puzzle.\nIf you guess wrong, a piece of HangMan is drawn.  Once HangMan is completely drawn, you LOSE!\n\nIf you are super confident that you know the word, you may guess the entire word.  But if you are wrong, you LOSE!\n\nIf you are able to get all the correct letters before the HangMan is hung, or the entire word, you WIN!\nNow let's play!\n\n";
}

FString GetValidGuess()
{
    bool bIsValid = false;
    FString guess;
    
    /// Makes sure guess is all letters
    do
    {
        bIsValid = true;
        std::cin.clear();
        std::cout<<"Guess a LETTER or a WORD: ";
        std::cin>>guess;
        
        for(auto letter: guess) // Loops through all characters
        {
            if(!isalpha(letter)) // If a character in the guess is not a letter
            {
                bIsValid = false;
            }
        }
        
    }while(! bIsValid);
    
    return guess;
}
void PrintGameOver()
{
    switch (newGame.CheckGameoverStatus())
    {
        case EGameOverStatus::Hung: // LOSE: Out of guesses
            newGame.DrawBoard();
            std::cout<<"Oh no! Hangman has been hung!\nThe hidden word was: "<<newGame.hiddenWord<<"\nYou LOSE.\nThanks for playing!\n\n";
            break;
            
        case EGameOverStatus::WordGuessed: // WIN: Corrrect word guessed
            std::cout<<"\nCongrats! You guessed the correct word.\nYou WIN.  Thanks for playing!\n\n";
            break;
            
        case EGameOverStatus::AllLettersGuessed: // WIN: All letters guessed
            newGame.PrintHiddenWordProgress();
            std::cout<<"Congrats! You guessed all of the correct letters.\nYou WIN. Thanks for playing!\n\n";
            break;
        
        case EGameOverStatus::WrongWord: // LOSE: Wrong word guessed
            std::cout<<"\nOh no! You guessed the wrong word.\nThe hidden word was: "<<newGame.hiddenWord<<"\nYou LOSE.\nThanks for playing!\n\n";
            break;
        
        default:
            break;
    }
}


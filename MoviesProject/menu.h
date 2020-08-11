#pragma once
#include "hashTable.h"

class Menu
{
    HashTable *movieTable;

public:
    Menu();
    ~Menu();
    int GetSelection();
    void AddMovie();
    void SearchMovie();
    void LoadMovies(std::string filename);
    HashTable *GetMovieTable();
    void StartMenu();
};


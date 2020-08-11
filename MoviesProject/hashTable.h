#pragma once
#include "movieList.h"

class HashTable
{
    MovieList *table;
    int size;
    double movieCount;

public:
    HashTable();
    HashTable(int size);
    ~HashTable();

    int GetSize();
    void Resize();

    void Merge(std::vector<Movie> &allMovies, int left, int middle, int right);
    void Sort(std::vector<Movie> &allMovies, int left, int right);

    int Hash(std::string key);    

    void Insert(std::string title, std::string leadActorActress, std::string description, int yearReleased);
    bool Delete(std::string title);
    Movie * Search(std::string title);

    void PrintYearFrequency();
    void PrintTable();
    void PrintSorted();
};


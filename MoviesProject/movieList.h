#pragma once
#include <vector>
#include "movie.h"

class MovieList
{
    Movie *head;
public:
    MovieList();
    ~MovieList();
    bool IsEmpty();
    void Insert(std::string title, std::string leadActorActress, std::string description, int yearReleased);
    void Insert(Movie *movie);
    bool Delete(std::string title);
    Movie * Search(std::string title);
    Movie * DetachAndGetFirst();
    std::vector<Movie> GetElements();
    void PrintList();
};


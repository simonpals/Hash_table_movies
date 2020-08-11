#pragma once
#include <string>
#include <iostream>

class Movie
{
    std::string title;
    std::string leadActorActress;
    std::string description;
    int yearReleased;

    Movie *next;
    Movie *prev;

public:
    Movie();    
    Movie(std::string title, std::string leadActorActress, std::string description, int yearReleased);

    bool operator <= (const Movie &movie);
    void Print();

    Movie *GetNext();
    void SetNext(Movie *next);
    Movie *GetPrev();
    void SetPrev(Movie *prev);
    std::string GetTitle();
    void SetTitle(std::string title);
    std::string GetLeadActorActress();
    void SetLeadActorActress(std::string leadActorActress);
    std::string GetDescription();
    void SetDescription(std::string description);
    int GetYearReleased();
    void SetYearReleased(int yearReleased);
};


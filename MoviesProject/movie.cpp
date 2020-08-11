#include "movie.h"

Movie::Movie()
    : Movie("","","",0)
{
}

Movie::Movie(std::string title, std::string leadActorActress, std::string description, int yearReleased)
{
    next = nullptr;
    prev = nullptr;

    this->title = title;
    this->leadActorActress = leadActorActress;
    this->description = description;
    this->yearReleased = yearReleased;
}

bool Movie::operator<=(const Movie &movie)
{
    return this->yearReleased <= movie.yearReleased;
}

void Movie::Print()
{
    std::cout << GetTitle() << "," << GetLeadActorActress() << "," << GetDescription() << "," << GetYearReleased() << '\n';
}

Movie * Movie::GetNext()
{
    return next;
}

void Movie::SetNext(Movie * next)
{
    this->next = next;
}

Movie * Movie::GetPrev()
{
    return prev;
}

void Movie::SetPrev(Movie * prev)
{
    this->prev = prev;
}

std::string Movie::GetTitle()
{
    return this->title;
}

void Movie::SetTitle(std::string title)
{
    this->title = title;
}

std::string Movie::GetLeadActorActress()
{
    return leadActorActress;
}

void Movie::SetLeadActorActress(std::string leadActorActress)
{
    this->leadActorActress = leadActorActress;
}

std::string Movie::GetDescription()
{
    return description;
}

void Movie::SetDescription(std::string description)
{
    this->description = description;
}

int Movie::GetYearReleased()
{
    return yearReleased;
}

void Movie::SetYearReleased(int yearReleased)
{
    this->yearReleased = yearReleased;
}

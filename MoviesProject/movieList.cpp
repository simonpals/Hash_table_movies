#include "movieList.h"

MovieList::MovieList()
{
    this->head = nullptr;
}

MovieList::~MovieList()
{
    Movie *curr = this->head;
    
    while (curr)
    {
        auto movie = curr;
        curr = curr->GetNext();
        delete movie;
    }
}

bool MovieList::IsEmpty()
{
    return !head;
}

void MovieList::Insert(std::string title, std::string leadActorActress, std::string description, int yearReleased)
{
    Movie *movie = new Movie(title, leadActorActress, description, yearReleased);
    Insert(movie);
}

void MovieList::Insert(Movie * movie)
{
    Movie *curr = this->head;

    if (!head)
    {
        head = movie;
        return;
    }

    while (curr && curr->GetNext())
    {
        curr = curr->GetNext();
    }

    curr->SetNext(movie);
    movie->SetPrev(curr);
}

bool MovieList::Delete(std::string title)
{
    Movie *curr = this->head;

    while (curr)
    {
        if (curr->GetTitle() == title)
        {
            auto prev = curr->GetPrev();
            auto next = curr->GetNext();

            if (!prev)
                head = next;

            if (prev)
                prev->SetNext(next);
            if (next)
                next->SetPrev(prev);

            delete curr;
            return true;
        }

        curr = curr->GetNext();
    }

    return false;
}

Movie * MovieList::Search(std::string title)
{
    Movie *curr = this->head;

    while (curr)
    {
        if (curr->GetTitle() == title)
            return curr;

        curr = curr->GetNext();
    }

    return nullptr;
}

Movie * MovieList::DetachAndGetFirst()
{
    if(!head)
        return nullptr;

    auto curr = head;
    auto next = this->head->GetNext();
    if(next) next->SetPrev(nullptr);
    head = next;

    return curr;
}

std::vector<Movie> MovieList::GetElements()
{
    std::vector<Movie> movies;
    Movie *curr = this->head;

    while (curr)
    {        
        movies.push_back(*curr);
        curr = curr->GetNext();
    }
    return movies;
}

void MovieList::PrintList()
{
    Movie *curr = this->head;

    while (curr)
    {
        curr->Print();
        curr = curr->GetNext();
    }
}

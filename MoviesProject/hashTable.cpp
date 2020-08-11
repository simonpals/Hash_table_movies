#include <unordered_map>
#include "hashTable.h"

const int defaultSize = 13;
const double loadFactor = 0.5;

HashTable::HashTable()
    : HashTable(defaultSize)
{
}

HashTable::HashTable(int size)
{
    this->size = size;
    this->movieCount = 0;
    table = new MovieList[size];
}

HashTable::~HashTable()
{
    delete[] table;
}

int HashTable::GetSize()
{
    return this->size;
}

void HashTable::Resize()
{
    auto oldCount = this->movieCount;
    auto oldSize = this->size;
    MovieList *oldTable = table;

    this->size *= 2;
    table = new MovieList[this->size];

    for (int i = 0; i < oldSize; ++i)
    {
        while (auto movie = oldTable[i].DetachAndGetFirst())
        {
            Insert(movie->GetTitle(), movie->GetLeadActorActress(), movie->GetDescription(), movie->GetYearReleased());
        }
    }

    this->movieCount = oldCount;
    delete[] oldTable;
}


void HashTable::Merge(std::vector<Movie>& allMovies, int left, int middle, int right)
{
    int size1 = middle - left + 1;
    int size2 = right - middle;
    std::vector<Movie> L(size1);
    std::vector<Movie> R(size2);

    for (int i = 0; i < size1; ++i)
    {
        L[i] = allMovies[left + i];
    }
    for (int j = 0; j < size2; ++j)
    {
        R[j] = allMovies[middle + j + 1];
    }

    int i = 0, j = 0;
    int k;
    for (k = left; k <= right && i < size1 && j < size2; ++k)
    {
        if (L[i] <= R[j])
        {
            allMovies[k] = L[i];
            i++;
        }
        else
        {
            allMovies[k] = R[j];
            j++;
        }
    }
    for (i = i; i < size1; ++i)
    {
        allMovies[k] = L[i];
        k++;
    }

    for (j = j; j < size2; ++j)
    {
        allMovies[k] = R[j];
        k++;
    }
}


void HashTable::Sort(std::vector<Movie>& allMovies, int left, int right)
{
    if (left < right)
    {
        int q = (left + right) / 2;
        Sort(allMovies, left, q);
        Sort(allMovies, q + 1, right);
        Merge(allMovies, left, q, right);
    }
}

int HashTable::Hash(std::string key)
{
    unsigned long hash = 5381;
    for (auto c : key) {
        hash = hash * 33 + c; // (hash << 5) + hash + c;
    }
    return hash % this->GetSize(); // ??
}

void HashTable::Insert(std::string title, std::string leadActorActress, std::string description, int yearReleased)
{
    Movie *movie = new Movie(title, leadActorActress, description, yearReleased);

    int hash = Hash(title);
    table[hash].Insert(movie);
    this->movieCount++;

    int loadCount = 0;
    int size = GetSize();
    for (int i = 0; i < size; ++i)
    {
        if (!table[i].IsEmpty())
            loadCount++;
    }

    if (loadCount > loadFactor*GetSize())
        Resize();
}

bool HashTable::Delete(std::string title)
{
    int hash = Hash(title);
    int removedMovies = 0;

    while (auto movie = table[hash].DetachAndGetFirst())
        removedMovies++;

    this->movieCount -= removedMovies;

    return removedMovies > 0;
}

Movie * HashTable::Search(std::string title)
{
    int hash = Hash(title);
    return table[hash].Search(title);
}

void HashTable::PrintYearFrequency()
{
    std::unordered_map<int, int> umap;

    int size = GetSize();
    for (int i = 0; i < size; ++i)
    {
        auto vec = table[i].GetElements();

        for (auto &movie : vec)
        {
            umap[movie.GetYearReleased()]++;
        }
    }

    for (auto &pair : umap)
    {
        std::cout << pair.first << "  -  " << pair.second << " movies" << '\n';
    }
}

void HashTable::PrintTable()
{
    int size = GetSize();
    for (int i = 0; i < size; ++i)
    {
        table[i].PrintList();
    }
}

void HashTable::PrintSorted()
{
    std::vector<Movie> allMovies;

    int size = GetSize();
    for (int i = 0; i < size; ++i)
    {
        auto vec = table[i].GetElements();
        allMovies.insert(allMovies.end(), vec.begin(), vec.end());
    }

    Sort(allMovies, 0, allMovies.size() - 1);

    for (auto &movie : allMovies)
    {
        movie.Print();
    }
}

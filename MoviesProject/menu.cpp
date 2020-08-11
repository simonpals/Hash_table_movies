#include "menu.h"
#include <fstream>

Menu::Menu()
{
    movieTable = new HashTable();
}

Menu::~Menu()
{
    delete movieTable;
}

int Menu::GetSelection()
{
    int mode;

    std::cout << "==============Menu==============" << '\n';
    std::cout << "1. Add Movie" << '\n';
    std::cout << "2. Search Movie" << '\n';
    std::cout << "3. Load Movies" << '\n';
    std::cout << "4. Print Table" << '\n';
    std::cout << "5. Print Sorted" << '\n';
    std::cout << "6. Print Year Frequency" << '\n';
    std::cout << "7. Exit" << '\n';
    std::cout << "Choose the number please: " << std::endl;
    std::cin >> mode;

    return mode;
}

void Menu::AddMovie()
{
    std::string title;
    std::string leadActorActress;
    std::string description;
    int yearReleased;

    std::cout << "Enter the movie title: " << std::endl;
    std::cin >> title;
    std::cout << "Enter the movie lead actor/actress: " << std::endl;
    std::cin >> leadActorActress;
    std::cout << "Enter the movie description: " << std::endl;
    std::cin >> description;
    std::cout << "Enter the movie released year: " << std::endl;
    std::cin >> yearReleased;

    movieTable->Insert(title, leadActorActress, description, yearReleased);

    std::cout << "Movie was added" << std::endl;
}

void Menu::SearchMovie()
{
    std::string title;
    std::cout << "Enter the movie title: " << std::endl;
    std::cin >> title;

    Movie *movie = movieTable->Search(title);

    if (movie)
        movie->Print();
    else
        std::cout << "Could not find movie" << std::endl;
}

static std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;

    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } 
    while (pos < str.length() && prev < str.length());

    return tokens;
}

void Menu::LoadMovies(std::string filename)
{
    std::ifstream infile(filename);
    if (infile.is_open())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            std::vector<std::string> parts = split(line, ",");
            if (parts.size() != 4)
            {
                std::cout << "Error input file format !" << std::endl;
                return;
            }

            std::string title = parts[0];
            std::string leadActorActress = parts[1];
            std::string description = parts[2];
            int yearReleased = std::stoi(parts[3]);

            movieTable->Insert(title, leadActorActress, description, yearReleased);
        }
    }
}

HashTable * Menu::GetMovieTable()
{
    return movieTable;
}

void Menu::StartMenu()
{
    while (true)
    {
        switch (GetSelection())
        {
        case 1:
        {
            AddMovie();
            break;
        }
        case 2:
        {
            SearchMovie();
            break;
        }
        case 3:
        {
            std::string path;
            std::cout << "Enter the file path please: " << std::endl;
            std::cin >> path;
            LoadMovies(path);
            break;
        }
        case 4:
        {
            movieTable->PrintTable();
            break;
        }
        case 5:
        {
            movieTable->PrintSorted();
            break;
        }
        case 6:
        {
            movieTable->PrintYearFrequency();
            break;
        }
        case 7:
        {
            return;
        }
        default:
            std::cout << "Wrong number!" << std::endl;
            break;
        }
    }
}

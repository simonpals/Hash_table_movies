//
//  TestCase.cpp
//  HashTable
//
//  Created by Zakaria Al-Qudah on 3/17/20.
//  Copyright © 2020 Zakaria Al-Qudah. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "catch/catch.hpp"
#include "../movie.h"
#include "../movielist.h"
#include "../hashtable.h"
#include "../menu.h"

TEST_CASE("Movie")
{
    Movie movie;
    REQUIRE(movie.GetTitle() == "");
    REQUIRE(movie.GetNext() == nullptr);
    REQUIRE(movie.GetPrev() == nullptr);
    
    Movie anotherMovie("test title", "test actor", "test desc", 2020);
    REQUIRE(anotherMovie.GetTitle() == "test title");
    REQUIRE(anotherMovie.GetLeadActorActress() == "test actor");
    REQUIRE(anotherMovie.GetDescription() == "test desc");
    REQUIRE(anotherMovie.GetYearReleased() == 2020);
}

TEST_CASE("MovieList")
{
    MovieList movieList;
    movieList.Insert ("test title", "test actress", "test desc",2020);
    Movie* searchResult;
    searchResult = movieList.Search("test title");
    REQUIRE(searchResult != nullptr);
    REQUIRE(searchResult->GetTitle() == "test title");
    REQUIRE(searchResult->GetLeadActorActress() == "test actress");
    REQUIRE(searchResult->GetDescription() == "test desc");
    REQUIRE(searchResult->GetYearReleased() == 2020);
    
    // test multi-element list ..
    movieList.Insert ("test title2", "test actress2", "test desc2",2020);
    searchResult = movieList.Search("test title2");
    REQUIRE(searchResult != nullptr);
    REQUIRE(searchResult->GetTitle() == "test title2");
    REQUIRE(searchResult->GetLeadActorActress() == "test actress2");
    REQUIRE(searchResult->GetDescription() == "test desc2");
    REQUIRE(searchResult->GetYearReleased() == 2020);
    
    // search for a non-existing item
    searchResult = movieList.Search("title does not exist");
    REQUIRE(searchResult == nullptr);
    
    //delete an item
    bool result = movieList.Delete("test title");
    searchResult = movieList.Search("test title");
    REQUIRE(searchResult == nullptr);
    REQUIRE (result == true);
    
    //delete the last item in the list
    result = movieList.Delete("test title2");
    searchResult = movieList.Search("test title2");
    REQUIRE(searchResult == nullptr);
    REQUIRE( result == true);
    
    movieList.Insert("test title","test actor/actress","test desc",2030);
    Movie * detachResult = movieList.DetachAndGetFirst ();
    REQUIRE(detachResult->GetTitle() == "test title");
    
    searchResult = movieList.Search("test title");
    REQUIRE(searchResult == nullptr);
}

TEST_CASE("HashTable")
{
    HashTable ht;
    int value = ht.Hash("test string");
    REQUIRE(value ==0);
    REQUIRE(ht.GetSize() == 13);
    
    ht.Insert("test title","test actress","test desc",2030);
    Movie* searchResult = ht.Search("test title");
    REQUIRE(searchResult != nullptr);
    REQUIRE(searchResult->GetTitle() == "test title");
    REQUIRE(searchResult->GetLeadActorActress() == "test actress");
    REQUIRE(searchResult->GetDescription() == "test desc");
    REQUIRE(searchResult->GetYearReleased() == 2030);
    
    ht.Insert ("test title2", "test actress2", "test desc2",2020);
    searchResult = ht.Search("test title2");
    REQUIRE(searchResult != nullptr);
    REQUIRE(searchResult->GetTitle() == "test title2");
    REQUIRE(searchResult->GetLeadActorActress() == "test actress2");
    REQUIRE(searchResult->GetDescription() == "test desc2");
    REQUIRE(searchResult->GetYearReleased() == 2020);
    
    // search for a non-existant item
    searchResult = ht.Search("No title");
    REQUIRE(searchResult == nullptr);
    
    //delete an item
    bool result = ht.Delete("test title");
    searchResult = ht.Search("test title");
    REQUIRE(searchResult == nullptr);
    REQUIRE (result == true);
    
    //delete the last item in the ht
    result = ht.Delete("test title2");
    searchResult = ht.Search("test title2");
    REQUIRE(searchResult == nullptr);
    REQUIRE (result ==  true);
    
    //delete item that does not exist
    result = ht.Delete("no title");
    
    REQUIRE(result == false);
    
    //load movies from file
    Menu menu;
    menu.LoadMovies("movies.txt");
    HashTable* mT = menu.GetMovieTable();
    //hash table should resize
    REQUIRE (mT->GetSize() == 26);
    searchResult = mT->Search("titanic1");
    REQUIRE (searchResult != nullptr);
    REQUIRE(searchResult->GetTitle() == "titanic1");
    REQUIRE(searchResult->GetLeadActorActress() == "best actor/actress1");
    REQUIRE(searchResult->GetDescription() == "best movie ever");
    REQUIRE(searchResult->GetYearReleased() == 2000);
             
}

// Add more test cases as needed

// Compile & run:
// make test

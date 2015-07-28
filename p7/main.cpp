#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "song.h"

using namespace std;

void titleinsertsort(vector<Song> &found)
{
  for (vector<Song>::iterator i = found.begin(); i != found.end(); i++)
  {
    vector<Song>::iterator temp = i;
    --temp;

    for (vector<Song>::iterator j = i; j != found.begin() && j->getTitle() < 
         temp->getTitle(); --j, --temp)
    {
      j->swap(*temp);
    } // for loop
  } // loop
}  // titleinsertsort()

void artistinsertsort(vector<Song> &found)
{
  for (vector<Song>::iterator i = found.begin(); i != found.end(); i++)
  {
    vector<Song>::iterator temp = i;
    --temp;

    for (vector<Song>::iterator j = i; j != found.begin() && j->getArtist() < 
         temp->getArtist(); --j, --temp)
    {
      j->swap(*temp);
    } // for loop
  } // loop
}  // artistinsertsort()

void print(vector<Song> found)
{
  for (vector<Song>::iterator it = found.begin(); it != found.end(); it++)
  {
    Song temp = *it;
    cout << temp;
  }// for
}// print

void findTitlePhrase(vector<Song> songlist, vector<Song> found)
{
  string input = "";
  cout << "Please enter the phrase: ";
  getline(cin, input);
  
  for (vector<Song>::iterator it = songlist.begin(); 
       it != songlist.end(); it++)
  {
    Song temp = *it;
    int pos = 0;
    pos = (temp.getTitle()).find(input);
    
    if (pos != -1)
    {
      found.push_back(temp);
    }// if
    
  }// for
  
  artistinsertsort(found);
  
  print(found);
}// findtitlephrase

void findAlbum(vector<Song> songlist, vector<Song> found)
{
  string input = "";
  cout << "Please enter the album: ";
  getline(cin, input);
  
  for (vector<Song>::iterator it = songlist.begin();
       it != songlist.end(); it++)
  {
    Song temp = *it;
    
    if (input == temp.getAlbum())
    {
      found.push_back(temp);
    }// if
    
  }// for

  titleinsertsort(found);
  
  print(found);
}// findalbum

void findTitle(vector<Song> songlist, vector<Song> found)
{
  string input = "";
  cout << "Please enter the title: ";
  getline(cin, input);
  
  for (vector<Song>::iterator it = songlist.begin(); 
       it != songlist.end(); it++)
  {
    Song temp = *it;
    
    if (input == temp.getTitle())
    {
      found.push_back(temp);
    }// if
    
  }// for

  artistinsertsort(found);
  
  print(found);
}// findtitle

void findArtist(vector<Song> songlist, vector<Song> found)
{
  string input = "";
  cout << "Please enter the artist's name: ";
  getline(cin, input);
  
  for (vector<Song>::iterator it = songlist.begin(); 
       it != songlist.end(); it++)
  {
      Song temp = *it;
      
      if (input == temp.getArtist())
      {
        found.push_back(temp);
      } // if statement
      
  }// for

  titleinsertsort(found);
  
  print(found);
}// findartist

void processCommand(int choice, vector<Song> songlist)
{
  vector<Song> found;
  
  switch (choice)
  {
    case 0: exit(0); break;
    case 1: findArtist(songlist, found); break;
    case 2: findTitle(songlist, found); break;
    case 3: findAlbum(songlist, found); break;
    case 4: findTitlePhrase(songlist, found); break;
    default: break;
  } // switch
} // processCommand(choice)

void menu(vector<Song> songlist)
{
  int choice = -1;
  
  while (choice != 0)
  {
    cout << endl;
    cout << "Song Menu" << endl;
    cout << "0. Done." << endl;
    cout << "1. Search for Artist." << endl;
    cout << "2. Search for Title." << endl;
    cout << "3. Search for Album." << endl;
    cout << "4. Search for title phrase." << endl << endl;
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore(256, '\n');
    
    if (choice < 0 || choice > 4) // choice outside range
    {
      cout << "Your choice must be between 0 and 4." << endl;
      cout << "Please try again." << endl << endl;
      continue;
    } // if
    
    else // choice is within range
    {
      processCommand(choice, songlist);
    } // else
    
  } // do while loop
  
} // menu()

int main()
{
  vector<Song> songlist;
  ifstream in("songs.txt");
  char c;
  int i = 0;
  
  while (in.get(c))
    if (c == '\n')
        ++i;
  
  in.close();
  ifstream inf("songs.txt");
  int j = 0;
  
  while(j != i)
  {
    Song temp;
    inf >> temp;
    songlist.push_back(temp);
    j++;
  }// while loop
  
  menu(songlist);
  return 0;
}// main

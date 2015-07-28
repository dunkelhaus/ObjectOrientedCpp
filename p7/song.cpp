#include "song.h"
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

istream& operator>>(istream& is, Song &rhs)
{
  string str = ""; 
  string str2 = "";
  getline(is, str, '_'); 
  str = rhs.fixTitle(str);
  // cout << "Title: " << str << endl;
  rhs.title = str; 
  str.clear(); 
  is.ignore(3, '_'); 
  is.ignore(3, '_'); 
  getline(is, str, '_'); 
  str2 = rhs.titleCase(str);
  // cout << "Artist: " << str2 << endl;
  rhs.artist = str2;
  str.clear(); 
  is.ignore(3, '_'); 
  is.ignore(3, '_'); 
  is.ignore(3, '_'); 
  is.ignore(40, '_'); 
  is.ignore(3, '_'); 
  is.ignore(3, '_'); 
  getline(is, str, '\n'); 
  str = rhs.fixCDG(str);
  // cout << "Album: " << str << endl;
  rhs.album = str; 
  return is;
}// instream operator

string Song::fixCDG(string str)
{
  string str2 = "";
  int pos = str.find("CD+G");
  int length = str.length();
  
  if (pos == -1)// if it does not exist
    return str;
  else // if it does exist
  {
    str.resize(length - 5);
    return str;
  }// else
}// fixCDG

void Song::swap(Song &song)
{
  title.swap(song.title);
  artist.swap(song.artist);
  album.swap(song.album);
} // swap()

string Song::fixTitle(string str)
{
    string str2 = "";
    string str3 = "";
    str2 = str.substr(0, 4);
    str3 = str.substr(0, 1);
    int pos = 0, pos2 = 0;
    
    if (str3 == "A" || str3 == "T")
    {
      pos = str2.find("A ");
      pos2 = str2.find("THE ");
      
      if (pos != -1)
      {
          str.erase(0, 2);
          str.append(", A");
          return str;
      }// if
      
      if (pos2 != -1)
      {
          str.erase(0, 4);
          str.append(", THE");
          return str;
      }// if
    }// if
    
    return str;
}// fix title

int Song::countSpaces(string str)
{
  int spaceCount = 0;
    
  for (string::iterator it = str.begin(); it != str.end(); it++)
    if (*it == ' ')// if it's a space
      spaceCount++;
  
  return spaceCount;
}// countSpaces()

string Song::titleCase(string str)
{
  string str2 = "", str3 = "";
  int spacePos = 0, spaceCount = 0, spaceIterator = 0;
  spaceCount = countSpaces(str);
  spacePos = str.find(" ", spaceIterator + 1);
  str3 = str.substr(0, spacePos);
  str3 = properNoun(str3); 
  str2 += str3; 
  str3.clear();
  spaceIterator = spacePos;
    
  for (int i = 2; i <= spaceCount; i++)
  {
    spacePos = 0;
    spacePos = str.find(" ", spaceIterator + 1);
    str3 = str.substr(spaceIterator + 1, spacePos - (spaceIterator + 1));
    str3 = properNoun(str3);
    str2 += " ";
    str2 += str3;
    str3.clear();
    spaceIterator = spacePos;
  }// for
  
  if (spaceCount > 0)
  {
    str3 = str.substr(spacePos + 1);
    str3 = properNoun(str3);
    str2 += " ";
    str2 += str3; 
  } // if
  
  return str2;
}//  titleCase()

string Song::properNoun(string str)
{
  string str2 = "";
  // cout << str << endl;
  
  for (string::iterator it = str.begin(); it != str.end(); it++)
  {
    str2 += toupper(*it);
    break;
  }// first letter as upper
  
  string::iterator i = str.begin();
  
  for (i++; i != str.end(); i++)
  {
    str2 += tolower(*i);
  }// for loop
  
  return str2;
}// change 

ostream& operator<<(ostream& os, Song &rhs)
{
  os << rhs.title;
  os << ":";
  os << rhs.artist;
  os << ":";
  os << rhs.album;
  os << endl; 
  return os;
}// outstream operator

string Song::getArtist()
{
    return artist;
}// getArtist()

string Song::getAlbum()
{
    return album;
}// getAlbum

string Song::getTitle()
{
    return title;
}// getTitle()

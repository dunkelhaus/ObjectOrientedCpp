#ifndef SONG_H
  #define SONG_H

#include <string>

using namespace std;

class Song
{
  string artist;
  string album;
  string title;
public:
  string titleCase(string title);
  string properNoun(string str);
  string fixCDG(string str);
  string artistCase(string str);
  string fixTitle(string str);
  int countSpaces(string str);
  string getArtist();
  string getAlbum();
  string getTitle();
  void swap(Song &song);
  friend istream& operator>>(istream& is, Song &rhs);
  friend ostream& operator<<(ostream& os, Song &rhs);
}; // songs

#endif 

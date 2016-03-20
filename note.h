#ifndef NOTE_H
#define NOTE_H

#include "string"

class Note
{
public:
    Note(int x,int y,std::string chemin,std::string nom);
    std::string getNom();
    std::string getChemin();
    int getY();
    int getX();
private:
    std::string nom;
    std::string chemin;
    int y;
    int x;
};

#endif // NOTE_H

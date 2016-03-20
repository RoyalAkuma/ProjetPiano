#include "note.h"

Note::Note(int x1, int y1,std::string ch,std::string n){
    x = x1;
    y = y1;
    chemin = ch;
    nom = n;
}


std::string Note::getChemin(){
    return chemin;
}

std::string Note::getNom(){
    return nom;
}

int Note::getY(){
    return y;
}

int Note::getX(){
    return x;
}

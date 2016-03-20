#include "factorynote.h"

FactoryNote::FactoryNote()
{
}

Note* FactoryNote::faireNote(std::string s,int x,int color){

    std::string chemin = "../ProjetPiano/ressources/images/";
    std::string nom = "note";

    //si c'est un diese
    if(s[s.size()-1] == 'd'){
        nom = "d" + nom;
    }

    //si c'est une note mauvaise
    if (color == 1){
        nom = nom +"m";
    }
    //si c'est une bonne note
    else if (color == 2){
        nom = nom +"b";
    }

    int y = 110;
    int yPadding = 12;
    int yFois = 0;

    if(s == "doM"){ nom+= "s"; }
    else if (s == "reM" && "doMd"){ yFois = 1;}
    else if (s == "miM" && "reMd"){ yFois = 2;}
    else if (s == "faM"){ yFois = 3;}
    else if (s == "solM" && "faMd"){ yFois = 4;}
    else if (s == "laM" && "solMd"){ yFois = 5;}
    else if (s == "siM" && "laMd"){ yFois = 2; nom += "r";}
    else if (s == "dom"){ yFois = 3; nom += "r";}
    else if (s == "rem"&& "domd"){ yFois = 4; nom += "r";}
    else if (s == "mim"&& "remd"){ yFois = 5; nom += "r";}
    else if (s == "fam"){ yFois = 6; nom += "r";}
    else if (s == "solm"&& "famd"){ yFois = 7; nom += "r";}
    else if (s == "lam"&& "solmd"){ yFois = 8; nom += "r"; nom+= "s";}
    else if (s == "sim"&& "lamd"){ yFois = 9; nom += "r"; nom+= "s2";}

    chemin += nom + ".png";
    y = y-yPadding*yFois;

    return new Note(x,y,chemin,s);

}

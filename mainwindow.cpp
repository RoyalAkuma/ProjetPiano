#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSound"
#include "QString"
#include <iostream>
#include <string>
#include <fstream>
#include "ctime"
using namespace std;

string chemin = "../ProjetPiano/ressources/sons/";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}







MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sons(string s){
    std::string str = chemin + s+".wav";
    QString qstr = QString::fromStdString(str);
    QSound::play(qstr);
}

void MainWindow::log(string s){
    ofstream fichier("log.txt", ios::app);  // ouverture en écriture avec effacement du fichier ouvert

            if(fichier)
            {
                time_t t;
                time(&t);
                string time =  ctime(&t) ;
                time[time.size()-1]=':';
                    fichier<<time<< s << endl;

                    fichier.close();
            }
            else
                    cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void MainWindow::on_B1Do_clicked()
{
    sons("do2M");
    log("doM");
}


void MainWindow::on_B2Re_clicked()
{
    sons("re2M");


}



void MainWindow::on_B3Mi_clicked()
{
    sons("mi2M");

}

void MainWindow::on_B4Fa_clicked()
{
    sons("fa2M");

}

void MainWindow::on_B5Sol_clicked()
{
    sons("sol2M");

}

void MainWindow::on_B6La_clicked()
{
    sons("la2M");

}

void MainWindow::on_B7Si_clicked()
{
    sons("si2M");

}

void MainWindow::on_B8Do2_clicked()
{
    sons("dom");

}

void MainWindow::on_B9Re2_clicked()
{
    sons("rem");

}

void MainWindow::on_B_10Mi2_clicked()
{

    sons("mim");
}

void MainWindow::on_B_11Fa2_clicked()
{
    sons("fam");

}

void MainWindow::on_B_12Sol2_clicked()
{
    sons("solm");

}

void MainWindow::on_B_13La2_clicked()
{

    sons("lam");
}

void MainWindow::on_B_14Si2_clicked()
{

    sons("sim");
}

void MainWindow::on_C1_clicked()
{

    sons("do2MD");
}

void MainWindow::on_C2_clicked()
{
    sons("re2MD");

}

void MainWindow::on_C3_clicked()
{
    sons("fa2MD");

}

void MainWindow::on_C4_clicked()
{
    sons("sol2MD");

}

void MainWindow::on_C5_clicked()
{
    sons("la2MD");

}

void MainWindow::on_C6_clicked()
{
    sons("domD");

}

void MainWindow::on_C7_clicked()
{
    sons("remD");

}

void MainWindow::on_C8_clicked()
{
    sons("famD");

}

void MainWindow::on_C9_clicked()
{

    sons("solmD");
}

void MainWindow::on_C_10_clicked()
{
    sons("lamD");

}

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
    ofstream fichier("log.txt", ios::out);
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
    log("reM");


}



void MainWindow::on_B3Mi_clicked()
{
    sons("mi2M");
    log("miM");

}

void MainWindow::on_B4Fa_clicked()
{
    sons("fa2M");
    log("faM");
}

void MainWindow::on_B5Sol_clicked()
{
    sons("sol2M");
    log("solM");

}

void MainWindow::on_B6La_clicked()
{
    sons("la2M");
    log("laM");

}

void MainWindow::on_B7Si_clicked()
{
    sons("si2M");
    log("siM");

}

void MainWindow::on_B8Do2_clicked()
{
    sons("dom");
    log("dom");

}

void MainWindow::on_B9Re2_clicked()
{
    sons("rem");
    log("rem");

}

void MainWindow::on_B_10Mi2_clicked()
{

    sons("mim");
    log("mim");
}

void MainWindow::on_B_11Fa2_clicked()
{
    sons("fam");
    log("fam");

}

void MainWindow::on_B_12Sol2_clicked()
{
    sons("solm");
    log("solm");

}

void MainWindow::on_B_13La2_clicked()
{

    sons("lam");
    log("lam");
}

void MainWindow::on_B_14Si2_clicked()
{

    sons("sim");
    log("sim");
}

void MainWindow::on_C1_clicked()
{

    sons("do2MD");
    log("doMD");
}

void MainWindow::on_C2_clicked()
{
    sons("re2MD");
    log("reMD");

}

void MainWindow::on_C3_clicked()
{
    sons("fa2MD");
    log("faMD");

}

void MainWindow::on_C4_clicked()
{
    sons("sol2MD");
    log("solMD");

}

void MainWindow::on_C5_clicked()
{
    sons("la2MD");
    log("laMD");

}

void MainWindow::on_C6_clicked()
{
    sons("domD");
    log("domD");

}

void MainWindow::on_C7_clicked()
{
    sons("remD");
    log("remD");

}

void MainWindow::on_C8_clicked()
{
    sons("famD");
    log("famD");

}

void MainWindow::on_C9_clicked()
{

    sons("solmD");
    log("solmD");
}

void MainWindow::on_C_10_clicked()
{
    sons("lamD");
    log("lamD");

}

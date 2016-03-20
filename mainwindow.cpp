#include "mainwindow.h"

using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setFixedSize(940, 550);
    ui->setupUi(this);
    nomsPartitions = ui->choixPartition;
    keybord = ui->Keyboard;
    partitionPaint = new Partition(ui->partition);

    QVBoxLayout* resultat = new QVBoxLayout;
    QHBoxLayout* reussite = new QHBoxLayout;
    QHBoxLayout* boutons = new QHBoxLayout;
    QVBoxLayout* Lratio = new QVBoxLayout;
    QHBoxLayout* total = new QHBoxLayout;
    partieBas = new QLabel(this);
    nbNote = new QLabel();
    nbNotesBonnes= new QLabel();
    nbNotesFausse= new QLabel();
    ratio= new QLabel();
    QLabel* ratio1=new QLabel();
    ratio1->setText("Réussite");


    //ratio->setSizePolicy();

    QPushButton* rejouer= new QPushButton();
    rejouer->setText("Rejouer");
    QPushButton* suivant= new QPushButton();
    suivant->setText("Suivant");
    total->addWidget(nbNote);
    resultat->addLayout(total);
    reussite->addWidget(nbNotesBonnes);
    reussite->addWidget(nbNotesFausse);
    resultat->addLayout(reussite);
    Lratio->addWidget(ratio1);
    Lratio->addWidget(ratio);
    resultat->addLayout(Lratio);
    boutons->addWidget(rejouer);
    boutons->addWidget(suivant);
    resultat->addLayout(boutons);

    nbNotesFausse->setAlignment(Qt::AlignRight);

    total->setAlignment(Qt::AlignCenter);


    QFont* f = new QFont(ratio->font());
    f->setPixelSize(30);
    ratio->setFont(*f);
    ratio->setAlignment(Qt::AlignCenter);

    Lratio->setAlignment(Qt::AlignCenter);
    Lratio->setSpacing(0);

    boutons->setSpacing(50);

    resultat->setAlignment(Qt::AlignCenter);
    resultat->setSpacing(20);


    partieBas->setLayout(resultat);
    partieBas->hide();
    partieBas->setGeometry(0,270,941,231);

    ui->aide->setChecked(true);




    xPadding = 80;
    cheminSons  = "../ProjetPiano/ressources/sons/";
    cheminPartitions = "../ProjetPiano/ressources/partitions/";
    factory = FactoryNote();
    xCurrent = 80;
    nbNotesJouer = 0;
    nbNotes = 0;
    nbPartitions = 0;

    QObject::connect(rejouer, SIGNAL(clicked()), this, SLOT(on_rejouer_clicked()));
    QObject::connect(suivant, SIGNAL(clicked()), this, SLOT(on_suivant_clicked()));


    //efface le fichier de log
    ofstream fichier("log.txt", ios::out);



    //ajout des partitions dans la combobox
    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    char* c = (char*)cheminPartitions.c_str();
    rep = opendir(c);
    if (rep == NULL)
       exit(1);

    fichierLu = readdir(rep);
    while ((fichierLu = readdir(rep)) != NULL){
       string str = fichierLu->d_name;
       if(str.find('~')==-1 && str != "." && str != ".."){
           str.erase(str.find(".txt"),str.size());
           QString qstr = QString::fromStdString(str);
           nomsPartitions->addItem(qstr);
           nbPartitions++;
       }
    }

    if (closedir(rep) == -1)
        exit(-1);


    //dessin du premier combobox
    if(nomsPartitions->itemText(0) != NULL)
        ecriturePartition(nomsPartitions->itemText(0));






}


MainWindow::~MainWindow()
{
    delete ui;
}

//ecrit la partition contenu dans /ressources/partitions/nomFichier.txt sur le widget partition
void MainWindow::ecriturePartition(QString nomFichier, vector<int> color){
    nbNotes = 0;
    nbNotesJouer = 0;
    log(nomFichier.toStdString());
    xCurrent = 80;
    string ch = cheminPartitions + nomFichier.toStdString() + ".txt";
    char* che = (char*)ch.c_str();
    ifstream fichier1(che, ios::in);

    if(fichier1)
    {
        vector<Note*> vtmp = vector<Note*>();
        string contenu;
        getline(fichier1, contenu);
        while(contenu.find(";")!=-1){
            string s = contenu.substr(0,contenu.find_first_of(";"));
            contenu = contenu.substr(contenu.find_first_of(";"));;
            contenu.erase(0,1);
            Note* ntmp;
            if(!color.empty())
                ntmp = factory.faireNote(s,xCurrent,color[nbNotes]);
            else
                ntmp = factory.faireNote(s,xCurrent);
            xCurrent += xPadding;
            vtmp.push_back(ntmp);
            nbNotes ++;
        }
        partitionPaint->setNotes(vtmp);
        partitionPaint->repaint();
        fichier1.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}



//Joue le son qui est dans ressources/sons/nomSon.wav
void MainWindow::sons(string nomSon){
    std::string str = cheminSons + nomSon+".wav";
    QString qstr = QString::fromStdString(str);
    QSound::play(qstr);
}

//fonction qui ecrit dans log.txt le s avec sa date
void MainWindow::log(string s){
    ofstream fichier("log.txt", ios::app);

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

//desactive la combobox
void MainWindow::disable(){
    for(int i = 0; i<nbPartitions;++i){
        // Get the index of the value to disable
        QModelIndex index = nomsPartitions->model()->index(i, 0);

        // This is the effective 'disable' flag
        QVariant v(0);

        // the magic
        nomsPartitions->model()->setData(index, v, Qt::UserRole - 1);
    }
}

//active la combobox
void MainWindow::enable(){
    for(int i = 0; i<nbPartitions;++i){
        // Get the index of the value to disable
        QModelIndex index = nomsPartitions->model()->index(i, 0);

        // This is the effective 'disable' flag
        QVariant v(1|32);

        // the magic
        nomsPartitions->model()->setData(index, v, Qt::UserRole - 1);
    }
}

void MainWindow::score(){
    if(nbNotes == nbNotesJouer){
        keybord->hide();
        partieBas->show();

        disable();

        ecriturePartition(nomsPartitions->currentText(),couleursNotes);

        string str = "Nombre de notes : " + intToString(nbNotes);
        QString tmp = QString::fromStdString(str);
        nbNote->setText(tmp);

        double nbNotesFausse = 0;
        double nbNotesBonnes = 0;
        for(int i = 0; i<couleursNotes.size();++i){
            if(couleursNotes[i] == 1) nbNotesFausse++;
            else nbNotesBonnes++;
        }
        double ratio = nbNotesBonnes/(nbNotesFausse+nbNotesBonnes) *100;

        str = "Reussite : " + intToString(nbNotesBonnes);
        tmp = QString::fromStdString(str);
        this->nbNotesBonnes->setText(tmp);

        str = "Fausses : " + intToString(nbNotesFausse);
        tmp = QString::fromStdString(str);
        this->nbNotesFausse->setText(tmp);


        if(ratio >= 50){
            this->ratio->setStyleSheet("color: green;");
        }else{
            this->ratio->setStyleSheet("color: red;");
        }
        str = intToString(ratio) + "%";
        tmp = QString::fromStdString(str);
        this->ratio->setText(tmp);


    }
}

std::string MainWindow::intToString(int i) {
    std::ostringstream oss;
    oss << i;
    return oss.str();
}



void MainWindow::addCouleursNotes(string s){

    if(s == partitionPaint->getNotes()[nbNotesJouer]->getNom()){
        couleursNotes.push_back(2);
    } else {
        couleursNotes.push_back(1);
    }
}

void MainWindow::on_rejouer_clicked(){

    partieBas->hide();
    keybord->show();
    couleursNotes.clear();
    enable();
    ecriturePartition(nomsPartitions->currentText());

}

void MainWindow::on_suivant_clicked(){

    partieBas->hide();
    keybord->show();
    couleursNotes.clear();
    enable();
    if(nomsPartitions->itemText(nomsPartitions->currentIndex()+1) != NULL){
        ecriturePartition(nomsPartitions->itemText(nomsPartitions->currentIndex()+1));
        nomsPartitions->setCurrentIndex(nomsPartitions->currentIndex()+1);
    }else{
        ecriturePartition(nomsPartitions->itemText(0));
        nomsPartitions->setCurrentIndex(0);
    }
}



void MainWindow::on_B1Do_clicked()
{
    sons("do2M");
    log("doM");
    addCouleursNotes("doM");
    nbNotesJouer++;
    score();
}


void MainWindow::on_B2Re_clicked()
{
    sons("re2M");
    log("reM");
    addCouleursNotes("reM");
    nbNotesJouer++;
    score();
}



void MainWindow::on_B3Mi_clicked()
{
    sons("mi2M");
    log("miM");
    addCouleursNotes("miM");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B4Fa_clicked()
{
    sons("fa2M");
    log("faM");
    addCouleursNotes("faM");
    nbNotesJouer++;
    score();
}

void MainWindow::on_B5Sol_clicked()
{
    sons("sol2M");
    log("solM");
    addCouleursNotes("solM");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B6La_clicked()
{
    sons("la2M");
    log("laM");
    addCouleursNotes("laM");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B7Si_clicked()
{
    sons("si2M");
    log("siM");
    addCouleursNotes("siM");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B8Do2_clicked()
{
    sons("dom");
    log("dom");
    addCouleursNotes("dom");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B9Re2_clicked()
{
    sons("rem");
    log("rem");
    addCouleursNotes("rem");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B_10Mi2_clicked()
{

    sons("mim");
    log("mim");
    addCouleursNotes("mim");
    nbNotesJouer++;
    score();
}

void MainWindow::on_B_11Fa2_clicked()
{
    sons("fam");
    log("fam");
    addCouleursNotes("fam");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B_12Sol2_clicked()
{
    sons("solm");
    log("solm");
    addCouleursNotes("solm");
    nbNotesJouer++;
    score();

}

void MainWindow::on_B_13La2_clicked()
{

    sons("lam");
    log("lam");
    addCouleursNotes("lam");
    nbNotesJouer++;
    score();
}

void MainWindow::on_B_14Si2_clicked()
{

    sons("sim");
    log("sim");
    addCouleursNotes("sim");
    nbNotesJouer++;
    score();
}

void MainWindow::on_C1_clicked()
{
    string s = "doMd";
    sons("do2MD");
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();
}

void MainWindow::on_C2_clicked()
{
    string s = "reMd";
    sons("re2MD");
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C3_clicked()
{
    string s = "faMd";
    sons("fa2MD");
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C4_clicked()
{
    string s = "solMd";
    sons("sol2MD");
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C5_clicked()
{
    string s = "laMd";
    sons("la2MD");
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C6_clicked()
{
    sons("domD");
    string s = "domd";
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C7_clicked()
{
    sons("remD");
    string s = "remd";
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C8_clicked()
{
    sons("famD");
    string s = "famd";
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_C9_clicked()
{

    sons("solmD");
    string s = "solmd";
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();
}

void MainWindow::on_C_10_clicked()
{
    sons("lamD");
    string s = "lamd";
    log(s);
    addCouleursNotes(s);
    nbNotesJouer++;
    score();

}

void MainWindow::on_choixPartition_activated(const QString &arg1)
{
    ecriturePartition(arg1);
}

void MainWindow::on_aide_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->B1Do->setText("\n\n\nDo");
        ui->B2Re->setText("\n\n\nRe");
        ui->B3Mi->setText("\n\n\nMi");
        ui->B4Fa->setText("\n\n\nFa");
        ui->B5Sol->setText("\n\n\nSol");
        ui->B6La->setText("\n\n\nLa");
        ui->B7Si->setText("\n\n\nSi");
        ui->B8Do2->setText("\n\n\nDo");
        ui->B9Re2->setText("\n\n\nRe");
        ui->B_10Mi2->setText("\n\n\nMi");
        ui->B_11Fa2->setText("\n\n\nFa");
        ui->B_12Sol2->setText("\n\n\nSol");
        ui->B_13La2->setText("\n\n\nLa");
        ui->B_14Si2->setText("\n\n\nSi");
        ui->C1->setText("\n\n\nDo#");
        ui->C2->setText("\n\n\nRe#");
        ui->C3->setText("\n\n\nFa#");
        ui->C4->setText("\n\n\nSol#");
        ui->C5->setText("\n\n\nLa#");
        ui->C6->setText("\n\n\nDo#");
        ui->C7->setText("\n\n\nRe#");
        ui->C8->setText("\n\n\nFa#");
        ui->C9->setText("\n\n\nSol#");
        ui->C_10->setText("\n\n\nLa#");
    } else {
        ui->B1Do->setText("");
        ui->B2Re->setText("");
        ui->B3Mi->setText("");
        ui->B4Fa->setText("");
        ui->B5Sol->setText("");
        ui->B6La->setText("");
        ui->B7Si->setText("");
        ui->B8Do2->setText("");
        ui->B9Re2->setText("");
        ui->B_10Mi2->setText("");
        ui->B_11Fa2->setText("");
        ui->B_12Sol2->setText("");
        ui->B_13La2->setText("");
        ui->B_14Si2->setText("");
        ui->C1->setText("");
        ui->C2->setText("");
        ui->C3->setText("");
        ui->C4->setText("");
        ui->C5->setText("");
        ui->C6->setText("");
        ui->C7->setText("");
        ui->C8->setText("");
        ui->C9->setText("");
        ui->C_10->setText("");

    }
}

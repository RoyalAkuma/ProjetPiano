#include "partition.h"
using namespace std;

Partition::Partition(QWidget *parent):QLabel(parent)
{
    this->setMinimumHeight(300);
    this->setMinimumWidth(900);
    notes =  vector<Note*>();
}

Partition::~Partition(){

}

void Partition::setNotes(vector<Note*> n){
    notes = n;
}

vector<Note*> Partition::getNotes(){
    return notes;
}

void Partition::tracerNotes(QPainter& painter){
    for(int i=0; i<notes.size();i++){
        QString s = QString::fromStdString(notes[i]->getChemin());
        QImage im(s);
        painter.drawImage(notes[i]->getX(),notes[i]->getY(),im);
    }
}

void Partition::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    tracerNotes(painter);
    painter.end();
}

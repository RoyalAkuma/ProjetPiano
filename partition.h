#ifndef PARTITION_H
#define PARTITION_H

#include "QLabel"
#include "QPainter"
#include "note.h"
#include "vector"
#include "iostream"


class Partition : public QLabel {

    Q_OBJECT

    public:
        Partition(QWidget *parent);
        ~Partition();
        void setNotes(std::vector<Note*>);
        std::vector<Note*> getNotes();

    private:
        void paintEvent(QPaintEvent*);
        void tracerNotes(QPainter&);

        std::vector<Note*> notes;

};

#endif // PARTITION_H

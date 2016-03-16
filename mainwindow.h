#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_B1Do_clicked();
    
    void on_B2Re_clicked();
    
    void on_B3Mi_clicked();

    void on_B4Fa_clicked();

    void on_B5Sol_clicked();

    void on_B6La_clicked();

    void on_B7Si_clicked();

    void on_B8Do2_clicked();

    void on_B9Re2_clicked();

    void on_B_10Mi2_clicked();

    void on_B_11Fa2_clicked();

    void on_B_12Sol2_clicked();

    void on_B_13La2_clicked();

    void on_B_14Si2_clicked();

    void on_C1_clicked();

    void on_C2_clicked();

    void on_C3_clicked();

    void on_C4_clicked();

    void on_C5_clicked();

    void on_C6_clicked();

    void on_C7_clicked();

    void on_C8_clicked();

    void on_C9_clicked();

    void on_C_10_clicked();

private:
    Ui::MainWindow *ui;
    void sons(std::string);
};

#endif // MAINWINDOW_H

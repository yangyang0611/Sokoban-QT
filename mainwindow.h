#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"secdialog.h"
#include <QMainWindow>
#include<QMessageBox>
#include<QPaintEvent>
#include<QPainter>
#include<QPalette>
#include<QLabel>
#include<QKeyEvent>
#include<QGraphicsItem>
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* );
    void keyPressEvent(QKeyEvent *event);
    QLabel *label = new QLabel(this);
    void Play();
    void Play2();
    void move();
    bool                check_move(int i_pos,int j_pos);
    bool                check_box_move(int box_ipos, int box_jpos);
    void                move_box();
    void                win(int box_ipos, int box_jpos);
    int                 direction=1;
    int                 score = 100;
    int                 step=0;
    int                 i=0;
    int                 i_pos=5, j_pos=5;
    int                 box1_ipos=3,box1_jpos=5;
    int                 box2_ipos=7,box2_jpos=5;
    int                 box3_ipos=5,box3_jpos=3;
    int                 box4_ipos=5,box4_jpos=7;
    int                 flag;
    int                 flag2;
    int                 flag3;
    int                 flag4;
    int                 key;
    int                 time=0;
    int                 map[11][11]={{2,2,2,2,1,1,1,2,2,2,2},
                                     {2,2,2,2,1,3,1,2,2,2,2},
                                     {2,2,2,2,1,2,1,2,2,2,2},
                                     {2,2,2,2,1,6,1,2,2,2,2},
                                     {1,1,1,1,1,4,1,1,1,1,1},
                                     {1,3,2,8,4,5,4,9,2,3,1},
                                     {1,1,1,1,1,4,1,1,1,1,1},
                                     {2,2,2,2,1,7,1,2,2,2,2},
                                     {2,2,2,2,1,2,1,2,2,2,2},
                                     {2,2,2,2,1,3,1,2,2,2,2},
                                      2,2,2,2,1,1,1,2,2,2,2};
               // 3 target 4 coin 5 player 6 box
    QGraphicsTextItem           *text;
    QGraphicsTextItem           *message;

private slots:
    void on_actionStart_triggered();

    void on_actionRestart_triggered();

    void on_actionlevel1_triggered();

    void on_actionlevel2_triggered();

    void on_actionEXit_triggered();
    void updateTimer();

private:
    Ui::MainWindow *ui;
    SecDialog* secDialog;
    QTimer *timer;
};

#endif // MAINWINDOW_H

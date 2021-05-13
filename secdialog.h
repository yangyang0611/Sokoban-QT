#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QMainWindow>
#include <QMainWindow>
#include<QMessageBox>
#include<QPaintEvent>
#include<QPainter>
#include<QPalette>
#include<QLabel>
#include<QKeyEvent>
#include<QGraphicsItem>
namespace Ui {
class SecDialog;
}

class SecDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();
    void paintEvent(QPaintEvent* );
    void keyPressEvent(QKeyEvent *event);
    QLabel *label = new QLabel(this);
    int                 direction=1;
    int                 score = 100;
    int                 step=0;
    int                 i=0;
    int                 flag;
    int                 flag2;
    int                 flag3;
    int                 flag4;
    int                 flag2_2;
    int                 flag2_1;
    int                 flag4_3;
    int                 flag3_3;
    int                 i2_pos=1,j2_pos=1;
    int                 box1_mp2_ipos=3,box1_mp2_jpos=1;
    int                 box2_mp2_ipos=3,box2_mp2_jpos=2;
    int                 box3_mp2_ipos=3,box3_mp2_jpos=3;
    int                 map2[9][9]={{1,1,1,1,1,1,1,1,1},    // 1 wall
                                    {1,5,1,2,2,2,2,2,1},    // 2 land
                                    {1,4,4,4,2,2,2,2,1},
                                    {1,6,7,8,2,2,2,2,1},
                                    {1,3,3,3,2,2,2,2,1},
                                    {1,1,1,1,2,2,2,0,1},
                                    {2,1,1,1,2,2,2,9,1},
                                    {2,2,1,1,2,2,2,2,1},
                                    {2,2,1,1,1,1,1,1,1}};
    bool                win(int box_mp2_ipos,int box_mp2_jpos);
    bool                check_move2(int i2_pos, int j2_pos);
    bool                check_box_move2(int box_mp2_ipos, int box_mp2_jpos);
    void                move2();
    void                move_box2();
    void                print_score(int i_pos,int j_pos);
    //QGraphicsTextItem           *text;
    //QGraphicsTextItem           *message;

private slots:
    void on_actionRestart_triggered();

    void on_actionlevel1_triggered();

    void on_actionQuit_triggered();

private:
    Ui::SecDialog *ui;
    SecDialog *secDialog;
};

#endif // SECDIALOG_H

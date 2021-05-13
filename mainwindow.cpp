#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include<QApplication>
#include<QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,800);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timerout()),this,SLOT(updateTimer()));
    timer->start(1000);
}
void MainWindow::updateTimer(){

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawText(50,630, "SCORE :"+QString::number(score));

    QPainter painter1(this);
    painter1.setPen(Qt::red);
    painter1.drawText(150,630, "STEP :"+QString::number(step));

    QPainter painter2(this);
    painter2.setPen(Qt::red);
    painter2.drawText(250,630, "Timer :"+QString::number(time));

    for(int i=0;i<11;i++)
        for(int j=0;j<11;j++)
            switch(map[i][j]){
            case 0:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/boom.png")); break;
            case 1:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/greystone.png")); break;
            case 2:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/black.png")); break;
            case 3:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/ball.png")); break;
            case 4:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/energizer.png")); break;
            case 5:{
                switch(direction){
                    case 1:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/back.jpg")); break;
                    break;
                    case 2:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/front.jpg")); break;
                    break;
                    case 3:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/left.jpg")); break;
                    break;
                    case 4:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/right.jpg")); break;
                    break;
                    default:
                    break;
                }
                break;
            }
            case 6:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/box.jpg")); break;
            case 7:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/box.jpg")); break;
            case 8:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/box.jpg")); break;
            case 9:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/box.jpg")); break;

    }
}


void    MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
     {
        direction = 3;
        repaint();
     }
     if (event->key() == Qt::Key_Right)
     {
        this->direction = 4;
         repaint();
     }
     if (event->key() == Qt::Key_Down)
     {
        this->direction = 2;
        repaint();
     }
     if (event->key() == Qt::Key_Up)
     {
        this->direction = 1;
        repaint();
     }
     move();
}

void MainWindow::move(){  // get boom move level2
    if(direction == 1){
        if(check_move(i_pos-1, j_pos)){
            if(map[i_pos-1][j_pos]==6){
                if(check_box_move(box1_ipos-1,box1_jpos)){
                    if(map[box1_ipos-1][box1_jpos]!=3){
                        box1_ipos--;
                        map[box1_ipos][box1_jpos] = 6;
                    }
                    else {
                        flag=1;
                        box1_ipos--;
                        map[box1_ipos][box1_jpos] = 6;
                        map[i_pos][j_pos]=2;
                        i_pos--;
                        map[i_pos][j_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
        }
            if(map[i_pos-1][j_pos]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map[i_pos-1][j_pos]==0){  // print u win print score
                hide();
                secDialog = new SecDialog(this);
                secDialog->show();
            }

            else{
                map[i_pos][j_pos]=2;
                i_pos--;
                map[i_pos][j_pos]=5;
            }
        }
    }
    if(direction == 2){
        if(check_move(i_pos+1, j_pos)){
            if(map[i_pos+1][j_pos]==7){
                if(check_box_move(box2_ipos+1,box2_jpos)){
                    if(map[box2_ipos+1][box2_jpos]!=3){
                        box2_ipos++;
                        map[box2_ipos][box2_jpos] = 7;
                    }
                else {
                    flag2=1;
                    box2_ipos++;
                    map[box2_ipos][box2_jpos] = 7;
                    map[i_pos][j_pos]=2;
                    i_pos++;
                    map[i_pos][j_pos]=5;
                    return;
                }
            }
                else {
                    return;
                }
        }
            if(map[i_pos+1][j_pos]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map[i_pos+1][j_pos]==0){  // print u win print score
                hide();
                secDialog = new SecDialog(this);
                secDialog->show();
            }

            else {
                 map[i_pos][j_pos]=2;
                i_pos++;
                map[i_pos][j_pos]=5;
            }
        }
    }
    if(direction == 3){
        if(check_move(i_pos, j_pos-1)){
            if(map[i_pos][j_pos-1]==8){
                if(check_box_move(box3_ipos,box3_jpos-1)){
                     if(map[box3_ipos][box3_jpos-1]!=3){
                        box3_jpos--;
                        map[box3_ipos][box3_jpos] = 8;
                     }
                     else {
                         flag3=1;
                         box3_jpos--;
                         map[box3_ipos][box3_jpos] = 8;
                         map[i_pos][j_pos]=2;
                         j_pos--;
                         map[i_pos][j_pos]=5;
                         return;
                     }
                }
            else {   // touch the wall,player cannot move
                return;
             }
          }
            if(map[i_pos][j_pos-1]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map[i_pos][j_pos-1]==0){  // print u win print score

            }
            else{
                map[i_pos][j_pos]=2;
                j_pos--;
                map[i_pos][j_pos]=5;
            }
        }
    }
    if(direction == 4){
        if(check_move(i_pos, j_pos+1)){

            if(map[i_pos][j_pos+1]==9){
                 if(check_box_move(box4_ipos,box4_jpos+1)){  // no touch the wall, box can move, return1
                     if(map[box4_ipos][box4_jpos+1]!=3){         //
                        box4_jpos++;
                        map[box4_ipos][box4_jpos] = 9;
                    }
                     else {
                         flag4=1;
                         box4_jpos++;
                         map[box4_ipos][box4_jpos] = 9;
                         map[i_pos][j_pos]=2;
                         j_pos++;
                         map[i_pos][j_pos]=5;
                         return;
                     }
                 }
                 else {   // touch the wall,player cannot move
                     return;
                 }
            }
            if(map[i_pos][j_pos+1]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map[i_pos][j_pos+1]==0){  // print u win print score
                hide();
                secDialog = new SecDialog(this);
                secDialog->show();
            }
            else{
                map[i_pos][j_pos]=2;
                j_pos++;
                map[i_pos][j_pos]=5;
            }
        }
    }
    repaint();
    if(flag==1 && flag2==1 && flag3==1 && flag4==1){
        QMessageBox::about(this,"Game Status","Level 1 cleared, jump to level 2");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();
    }
}

void MainWindow::win(int box_ipos, int box_jpos){
    if(map[box_ipos][box_jpos]==3){
        i=2;
    }
    else {   // do not touch wall, continue move

    }
}

bool MainWindow::check_move(int i_pos, int j_pos)
{
    if (map[i_pos][j_pos] == 1)  // cannot move
        return (0);
    else {   // can move
        step++;
        return (1);
    }
}

bool MainWindow::check_box_move(int box_ipos, int box_jpos){
    if(map[box_ipos][box_jpos]==1)
        return (0);
    else
        return (1);
}

void MainWindow::on_actionStart_triggered()
{

}

void MainWindow::on_actionRestart_triggered()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void MainWindow::on_actionlevel2_triggered()
{
    hide();
    secDialog = new SecDialog(this);
    secDialog->show();
}

void MainWindow::on_actionEXit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"End Mode Set","Are u sure you want to quit",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
       QApplication::quit();
    else
        QMessageBox::Close;
}


void MainWindow::on_actionlevel1_triggered(){

}

void MainWindow::Play2(){
    QPalette back;
        back.setBrush(QPalette::Background,QBrush(QPixmap(":/pic/map2.jpg")));
        this->setPalette(back);
}

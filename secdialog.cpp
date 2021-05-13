#include "secdialog.h"
#include "ui_secdialog.h"

#include <QPainter>
#include <QPaintEvent>
#include<QApplication>
#include<QProcess>
SecDialog::SecDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    this->setFixedSize(800,800);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawText(50,630, "SCORE :"+QString::number(score));

    QPainter painter1(this);
    painter1.setPen(Qt::red);
    painter1.drawText(150,630, "STEP :"+QString::number(step));

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            switch(map2[i][j]){
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
            case 9:painter.drawImage(QRect(48*j,48*i,48,48),QImage(":/candy.jpg")); break;
    }
}

void SecDialog::keyPressEvent(QKeyEvent *event)
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
     move2();
}

void SecDialog::move2(){
    if(direction == 1){
        if(check_move2(i2_pos-1, j2_pos)){

            if(map2[i2_pos-1][j2_pos]==6){
                if(check_box_move2(box1_mp2_ipos-1,box1_mp2_jpos)){
                    if(map2[box1_mp2_ipos-1][box1_mp2_jpos]!=3){
                        box1_mp2_ipos--;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                    }
                    else {
                        flag=1;
                        box1_mp2_ipos--;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos--;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos-1][j2_pos]==7){
                if(check_box_move2(box1_mp2_ipos-1,box1_mp2_jpos)){
                    if(map2[box2_mp2_ipos-1][box2_mp2_jpos]!=3){
                        box2_mp2_ipos--;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                    }
                    else {
                        flag=1;
                        box2_mp2_ipos--;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos--;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos-1][j2_pos]==8){
                if(check_box_move2(box3_mp2_ipos-1,box3_mp2_jpos)){
                    if(map2[box3_mp2_ipos-1][box3_mp2_jpos]!=3){
                        box3_mp2_ipos--;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                    }
                    else {
                        flag=1;
                        box3_mp2_ipos--;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos--;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }

            if(map2[i2_pos-1][j2_pos]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map2[i2_pos-1][j2_pos]==0){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a boom switch to level1");
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
            }
            if(map2[i2_pos-1][j2_pos]==9){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a candy, stage clear~");
                this->close();
            }

            else{
                map2[i2_pos][j2_pos]=2;
                i2_pos--;
                map2[i2_pos][j2_pos]=5;
            }
        }
    }
    if(direction == 2){
        if(check_move2(i2_pos+1, j2_pos)){
            if(map2[i2_pos+1][j2_pos]==6){
                if(check_box_move2(box1_mp2_ipos+1,box1_mp2_jpos)){
                    if(map2[box1_mp2_ipos+1][box1_mp2_jpos]!=3){
                        box1_mp2_ipos++;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                    }
                    else {
                        flag2=1;
                        box1_mp2_ipos++;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos++;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos+1][j2_pos]==7){
                if(check_box_move2(box2_mp2_ipos+1,box2_mp2_jpos)){
                    if(map2[box2_mp2_ipos+1][box2_mp2_jpos]!=3){
                        box2_mp2_ipos++;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                    }
                    else {
                        flag2_1=1;
                        box2_mp2_ipos++;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos++;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos+1][j2_pos]==8){
                if(check_box_move2(box3_mp2_ipos+1,box3_mp2_jpos)){
                    if(map2[box3_mp2_ipos+1][box3_mp2_jpos]!=3){
                        box3_mp2_ipos++;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                    }
                    else {
                        flag2_2=1;
                        box3_mp2_ipos++;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                        map2[i2_pos][j2_pos]=2;
                        i2_pos++;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos+1][j2_pos]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map2[i2_pos+1][j2_pos]==0){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a boom switch to level1");
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
            }
            if(map2[i2_pos+1][j2_pos]==9){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a candy, stage clear~");
                this->close();
            }
            else{
                map2[i2_pos][j2_pos]=2;
                i2_pos++;
                map2[i2_pos][j2_pos]=5;
            }
        }
    }
    if(direction == 3){
        if(check_move2(i2_pos, j2_pos-1)){
            if(map2[i2_pos][j2_pos-1]==6){
                if(check_box_move2(box1_mp2_ipos,box1_mp2_jpos-1)){
                    if(map2[box1_mp2_ipos][box1_mp2_jpos-1]!=3){
                        box1_mp2_jpos--;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                    }
                    else {
                        flag3=1;
                        box1_mp2_jpos--;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                        map2[i2_pos][j2_pos]=2;
                        j2_pos--;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos][j2_pos-1]==7){
                if(check_box_move2(box2_mp2_ipos,box2_mp2_jpos-1)){
                    if(map2[box2_mp2_ipos][box2_mp2_jpos-1]!=3){
                        box2_mp2_jpos--;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                }
                else {
                    flag3=1;
                    box2_mp2_jpos--;
                    map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                    map2[i2_pos][j2_pos]=2;
                    j2_pos--;
                    map2[i2_pos][j2_pos]=5;
                    return;
                }
            }
                else{
                    return;
                }
            }
            if(map2[i2_pos][j2_pos-1]==8){
                if(check_box_move2(box3_mp2_ipos,box3_mp2_jpos-1)){
                    if(map2[box3_mp2_ipos][box3_mp2_jpos-1]!=3){
                        box3_mp2_jpos--;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                    }
                    else {
                        flag3_3=1;
                        box3_mp2_jpos--;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                        map2[i2_pos][j2_pos]=2;
                        j2_pos--;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos][j2_pos-1]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map2[i2_pos][j2_pos-1]==0){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a boom switch to level1");
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
            }
            if(map2[i2_pos][j2_pos-1]==9){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a candy, stage clear~");
                this->close();
            }
            else{
                map2[i2_pos][j2_pos]=2;
                j2_pos--;
                map2[i2_pos][j2_pos]=5;
            }
        }
    }
    if(direction == 4){
        if(check_move2(i2_pos, j2_pos+1)){
            if(map2[i2_pos][j2_pos+1]==6){
                if(check_box_move2(box1_mp2_ipos,box1_mp2_jpos+1)){
                    if(map2[box1_mp2_ipos][box1_mp2_jpos+1]!=3){
                        box1_mp2_jpos++;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                    }
                    else {
                        flag4=1;
                        box1_mp2_jpos++;
                        map2[box1_mp2_ipos][box1_mp2_jpos] = 6;
                        map2[i2_pos][j2_pos]=2;
                        j2_pos++;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos][j2_pos+1]==7){
                if(check_box_move2(box2_mp2_ipos,box2_mp2_jpos+1)){
                    if(map2[box2_mp2_ipos][box2_mp2_jpos+1]!=3){
                        box2_mp2_jpos++;
                        map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                }
                else {
                    flag4=1;
                    box2_mp2_jpos++;
                    map2[box2_mp2_ipos][box2_mp2_jpos] = 7;
                    map2[i2_pos][j2_pos]=2;
                    j2_pos++;
                    map2[i2_pos][j2_pos]=5;
                    return;
                }
            }
                else{
                    return;
                }
            }
            if(map2[i2_pos][j2_pos+1]==8){
                if(check_box_move2(box3_mp2_ipos,box3_mp2_jpos+1)){
                    if(map2[box3_mp2_ipos][box3_mp2_jpos+1]!=3){
                        box3_mp2_jpos++;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                    }
                    else {
                        flag4_3=1;
                        box3_mp2_jpos++;
                        map2[box3_mp2_ipos][box3_mp2_jpos] = 8;
                        map2[i2_pos][j2_pos]=2;
                        j2_pos++;
                        map2[i2_pos][j2_pos]=5;
                        return;
                    }
                }
                else {
                    return;
                }
            }
            if(map2[i2_pos][j2_pos+1]==4){
                QMessageBox::about(this,"Game Status","You get 10 coins");
                score+=10;
            }
            if(map2[i2_pos][j2_pos+1]==0){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a boom switch to level1");
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
            }
            if(map2[i2_pos][j2_pos+1]==9){  // print u win print score
                QMessageBox::about(this,"Game Status","You get a candy, stage clear~");
                this->close();
            }
            else{
                map2[i2_pos][j2_pos]=2;
                j2_pos++;
                map2[i2_pos][j2_pos]=5;
            }
        }
    }
    repaint();
    if((flag2==1 && flag2_1==1 && flag2_2==1) || (flag2==1 && flag2_1==1 && flag3_3==1)){
        QMessageBox::about(this,"Game Status","You WIN");
        this->close();
    }
    if(flag2==1 && flag2_1==1 && flag4_3==1){
        QMessageBox::about(this,"Game Status","You WIN");
        this->close();
    }
}

bool SecDialog::win(int box_mp2_ipos,int box_mp2_jpos){
    if(map2[box_mp2_ipos][box_mp2_jpos] == 3){
        i++;
    }
    else {
        return (0);
    }
}

bool SecDialog::check_move2(int i2_pos, int j2_pos)
{
    if (map2[i2_pos][j2_pos] == 1)
        return (0);
    else {   // can move
        step++;
        return (1);
    }
}

bool SecDialog::check_box_move2(int box_mp2_ipos, int box_mp2_jpos){
    if(map2[box_mp2_ipos][box_mp2_jpos]==1)
        return (0);
    else
        return (1);
}

void SecDialog::on_actionRestart_triggered()
{
    hide();
    secDialog = new SecDialog(this);
    secDialog->show();
}

void SecDialog::on_actionlevel1_triggered()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void SecDialog::on_actionQuit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"End Mode Set","Are u sure you want to quit",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
       QApplication::quit();
    else
        QMessageBox::Close;
}

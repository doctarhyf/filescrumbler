#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mediaplayer = new QMediaPlayer(this);
    mediapleylist = new QMediaPlaylist(mediaplayer);
    dialogtext = new QDialog(this);

    connect(ui->pbplay, &QPushButton::clicked, mediaplayer, &QMediaPlayer::play);
    connect(ui->pbpause, &QPushButton::clicked, mediaplayer, &QMediaPlayer::pause);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pbplay_clicked()
{

}


void Widget::on_pbpause_clicked()
{

}


void Widget::on_pbopen_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Open Audio File", "", "*.*");
    if(!filepath.isEmpty()){
        mediapleylist->addMedia(QUrl::fromLocalFile(filepath));
        mediaplayer->setPlaylist(mediapleylist);
    }
}


void Widget::on_lepwd_returnPressed()
{

}


void Widget::on_pblock_clicked()
{
    qInfo() << ui->lepwd->text();
}


void Widget::on_pbunlock_clicked()
{

}


void Widget::on_pbshowtext_clicked()
{
    dialogtext->show();
}


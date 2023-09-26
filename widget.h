#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbplay_clicked();

    void on_pbpause_clicked();

    void on_pbopen_clicked();

    void on_lepwd_returnPressed();

    void on_pblock_clicked();

    void on_pbunlock_clicked();

    void on_pbshowtext_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer *mediaplayer;
    QMediaPlaylist *mediapleylist;
    QDialog *dialogtext;

};
#endif // WIDGET_H

#ifndef FORMTEXT_H
#define FORMTEXT_H

#include <QWidget>
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QCryptographicHash>
#include <QByteArray>
#include <QVector>
#include <algorithm>
#include <random>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class FormText;
}

class FormText : public QWidget
{
    Q_OBJECT

public:
    explicit FormText(QWidget *parent = nullptr);
    ~FormText();

private slots:
    void on_pbshuffle_clicked();

    void on_pbunshuffle_clicked();

    void on_lepwd_textChanged(const QString &arg1);

    void on_pbloadfile_clicked();

private:
    Ui::FormText *ui;
    void shuffleFile(const QString& inputFileName, const QString& outputFileName, const QString& password);
    void unshuffleFile(const QString& inputFileName, const QString& outputFileName, const QString& password);
    QString inputFileName, filename, shuffledFileName,unshuffledFileName, password = "my_secret_password";
};

#endif // FORMTEXT_H

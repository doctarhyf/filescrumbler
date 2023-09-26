#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QDebug>
#include <QtCore>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pbprocess_clicked();

    void on_pbloadfile_clicked();

    void on_rbscrumble_toggled(bool checked);

    void on_rbunscrumble_toggled(bool checked);

private:
    Ui::Form *ui;
    int operation;
    QString inputFilePath, outputFilePath, fileNameOut,fileNameIn;
    QFile inputfile, outputfile;
    void scrambleFile(const QString& inputFileName, const QString& outputFileName, const QString& password);
    void unscrambleFile(const QString& inputFileName, const QString& outputFileName, const QString& password);

};

#endif // FORM_H

#include "formtext.h"
#include "ui_formtext.h"



FormText::FormText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormText)
{
    ui->setupUi(this);
}

// Function to shuffle bytes in a file based on a password
void FormText::shuffleFile(const QString& inputFileName, const QString& outputFileName, const QString& password) {
    QFile inputFile(inputFileName);
    QFile outputFile(outputFileName);

    if (!inputFile.open(QIODevice::ReadOnly) || !outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open input or output file.";
        return;
    }

    QByteArray passwordBytes = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QByteArray inputData = inputFile.readAll();

    QVector<quint8> shuffleIndices(inputData.size());
    for (int i = 0; i < shuffleIndices.size(); ++i) {
        shuffleIndices[i] = i;
    }

    std::seed_seq seed(passwordBytes.begin(), passwordBytes.end());
    std::mt19937 rng(seed);

    std::shuffle(shuffleIndices.begin(), shuffleIndices.end(), rng);

    QByteArray shuffledData(inputData.size(), 0);

    for (int i = 0; i < inputData.size(); ++i) {
        shuffledData[i] = inputData[shuffleIndices[i]];
    }

    outputFile.write(shuffledData);

    inputFile.close();
    outputFile.close();
}

// Function to unshuffle bytes in a file based on a password
void FormText::unshuffleFile(const QString& inputFileName, const QString& outputFileName, const QString& password) {
    QFile inputFile(inputFileName);
    QFile outputFile(outputFileName);

    if (!inputFile.open(QIODevice::ReadOnly) || !outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open input or output file.";
        return;
    }

    QByteArray passwordBytes = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QByteArray inputData = inputFile.readAll();

    QVector<quint8> unshuffleIndices(inputData.size());
    for (int i = 0; i < unshuffleIndices.size(); ++i) {
        unshuffleIndices[i] = i;
    }

    std::seed_seq seed(passwordBytes.begin(), passwordBytes.end());
    std::mt19937 rng(seed);

    std::shuffle(unshuffleIndices.begin(), unshuffleIndices.end(), rng);

    QByteArray unshuffledData(inputData.size(), 0);

    for (int i = 0; i < inputData.size(); ++i) {
        unshuffledData[unshuffleIndices[i]] = inputData[i];
    }

    outputFile.write(unshuffledData);

    inputFile.close();
    outputFile.close();
}


FormText::~FormText()
{
    delete ui;
}

void FormText::on_pbshuffle_clicked()
{


    QString password = ui->lepwd->text();

shuffledFileName = "/home/doctarhyf/Desktop/tmp/" + shuffledFileName;

    shuffleFile(inputFileName,  shuffledFileName, password );



}


void FormText::on_pbunshuffle_clicked()
{
    QString password = ui->lepwd->text();

shuffledFileName = "/home/doctarhyf/Desktop/tmp/" + shuffledFileName;

    unshuffleFile(inputFileName,  shuffledFileName, password );
}


void FormText::on_lepwd_textChanged(const QString &arg1)
{

}


void FormText::on_pbloadfile_clicked()
{
     inputFileName = QFileDialog::getOpenFileName(this, "Open input file", "/home/doctarhyf/Desktop/tmp/", "*.*");
     if(inputFileName.isEmpty()){
         int ret = QMessageBox::warning(this, tr("Select input file"),
                                        tr("Please select an input file first!"),
                                        QMessageBox::Ok);


         return;
     }

     QFile file(inputFileName);
     if(!file.open(QIODevice::ReadOnly)){
         QMessageBox::warning(this, tr("Cant open file"),
                                                 tr("File not opened!"),
                                                 QMessageBox::Ok);

         return;
     }
     ui->ptetext->document()->setPlainText(file.readAll());
     setWindowTitle(inputFileName);
     QStringList splits = inputFileName.split("/");
     filename = splits.at(splits.length() -1);

     shuffledFileName = "sh_" + filename;
     unshuffledFileName = "unsh_" + filename;
     ui->leshuffledfile->setText(shuffledFileName);
     ui->leunshuffledfile->setText(unshuffledFileName);

     file.close();

}


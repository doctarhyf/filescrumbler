#include "form.h"
#include "ui_form.h"
#define OP_SCRUMBLRE 1
#define OP_UNSCRUMBLE 0

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    operation = OP_SCRUMBLRE;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pbprocess_clicked()
{
    QFile in(inputFilePath);
    QFile out(outputFilePath);



    if(in.open(QIODevice::ReadOnly) && out.open(QIODevice::WriteOnly)){

        QString pwd = ui->lepwd->text();

        if(operation == OP_SCRUMBLRE){
            qInfo() << "Scrumbling ...";

            scrambleFile(inputFilePath, outputFilePath, pwd);
        }else{
            qInfo() << "Unscrumbling ...";
            unscrambleFile(inputFilePath, outputFilePath, pwd);
        }


        return;
    }


    in.close();
    out.close();
    QMessageBox::critical(this, "Erreur ", "Erreur opening out or in file");


}

void Form::scrambleFile(const QString& inputFileName, const QString& outputFileName, const QString& password){
    QFile inputFile(inputFileName);
       QFile outputFile(outputFileName);

       qDebug() << "Operation";
        qDebug() << "inputFileName :, " << inputFileName;
        qDebug() << "outputFileName :, " << outputFileName;

       if (!inputFile.open(QIODevice::ReadOnly) || !outputFile.open(QIODevice::WriteOnly)) {
           qDebug() << "Failed to open input or output file.";
           return;
       }

       QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5);

       while (!inputFile.atEnd()) {
           QByteArray inputBuffer = inputFile.read(1024); // Read in chunks
           QByteArray outputBuffer;
           outputBuffer.resize(inputBuffer.size());

           for (int i = 0; i < inputBuffer.size(); ++i) {
               outputBuffer[i] = inputBuffer[i] ^ passwordHash[i % passwordHash.size()];
           }

           outputFile.write(outputBuffer);
       }

       inputFile.close();
       outputFile.close();
}
void Form::unscrambleFile(const QString& inputFileName, const QString& outputFileName, const QString& password){
     scrambleFile(inputFileName, outputFileName, password);
}

void Form::on_pbloadfile_clicked()
{
    inputFilePath = QFileDialog::getOpenFileName(this, "Select file ...", "/home/doctarhyf/Desktop/tmp/");
    QStringList splits = inputFilePath.split("/");
    fileNameIn = splits.at(splits.length()-1);

    QString op = "scr_";

    if(operation == OP_UNSCRUMBLE) op = "uns_";

    fileNameOut = op + fileNameIn;
    outputFilePath = "/home/doctarhyf/Desktop/tmp/" + fileNameOut;

    if(inputFilePath.isEmpty()){
        QMessageBox::critical(this, "Error selecting input file", "Please select an input file");
        return;
    }



    ui->lbfilename->setText(fileNameIn);
    ui->lbfilepath->setText(inputFilePath);
    setWindowTitle(inputFilePath);



}


void Form::on_rbscrumble_toggled(bool checked)
{
    operation = checked ? 1 : 0;
}


void Form::on_rbunscrumble_toggled(bool checked)
{
    operation = checked ? 0 : 1;
}


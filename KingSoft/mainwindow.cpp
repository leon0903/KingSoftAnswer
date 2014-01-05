#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
    connect (this, SIGNAL( singleFileLoad() ), this, SLOT( matchFiles() ) );

    needtochange1 = false;
    needtochange2 = false;
}

bool MainWindow::matchFiles()
{
    if (file1Name != "" && file2Name != "")
    {
        ui->pushButton_3->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    file1Name = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "..",
                                                    tr("Text (*.txt)"));
    QFile file1 (file1Name );
    if(!file1.open(QIODevice::ReadWrite | QIODevice::Text))
    {
         qDebug()<<"Can't open the file1!"<<endl;
         return;
    }
    else
    {
         qDebug()<<"Open file1 OK!"<<endl;
    }

    QString pattern("([ \t])*");
    QRegExp rx(pattern);

    QTextStream in1(&file1);

    ui->lineEdit->setText("");
    while ( !in1.atEnd() )
    {
        QString linefile1 = in1.readLine();
        ui->lineEdit->setText( ui->lineEdit->text() + linefile1 + " " );
        if ( rx.exactMatch(linefile1) )
        {
            needtochange1 = true;
            continue;
        }
        else
        {
            list1.push_back(linefile1);
        }

    }

    emit singleFileLoad();

}

void MainWindow::on_pushButton_2_clicked()
{
    file2Name = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "..",
                                                    tr("Text (*.txt)"));
    QFile file2 (file2Name );
    if(!file2.open(QIODevice::ReadWrite | QIODevice::Text))
    {
         qDebug()<<"Can't open the file2!"<<endl;
         return;
    }
    else
    {
         qDebug()<<"Open file2 OK!"<<endl;
    }

    QString pattern("([ \t])*");
    QRegExp rx(pattern);

    QTextStream in2(&file2);

    ui->lineEdit_2->setText("");
    while ( !in2.atEnd() )
    {
        QString linefile2 = in2.readLine();
        ui->lineEdit_2->setText( ui->lineEdit_2->text() + linefile2 + " " );
        if ( rx.exactMatch(linefile2) )
        {
            needtochange2 = true;
            continue;
        }
        else
        {
            list3.push_back(linefile2);
        }
    }

    emit singleFileLoad();
}

//bool MainWindow::matchFiles()
//{
//    if (ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")
//    {
//        ui->pushButton_3->setEnabled(true);
//        ui->pushButton_3->setToolTip(0);
//    }
//    return 1;
//}

void MainWindow::on_pushButton_3_clicked()
{


    QString backfile1Name = file1Name.left(file1Name.length() - 4) + ".bak";
    QString backfile2Name = file2Name.left(file2Name.length() - 4) + ".bak";

    QFile backfile001(backfile1Name);
    if ( backfile001.exists() )
    {
        QFile::remove( backfile1Name);
    }


    if( !QFile::copy(file1Name, backfile1Name ) )
    {
        qDebug() << "back file1 failed";
    }
    else
    {
        qDebug() << "back file1 OK";
    }


    QFile backfile002(backfile2Name);
    if ( backfile002.exists() )
    {
        QFile::remove( backfile2Name);
    }

    if( !QFile::copy(file2Name, backfile2Name ) )
    {
        qDebug() << "back file2 failed";
    }
    else
    {
        qDebug() << "back file2 OK";
    }



    for (QList <QString>::iterator it1 = list1.begin(); it1 != list1.end(); it1++)
    {
        for (QList <QString>::iterator it2 = list3.begin(); it2 != list3.end(); it2++)
        {
            if (*it1 == *it2)
            {
                needtochange1 = true;
                needtochange2 = true;
                list1.erase(it1);
                it1--;
                list3.erase(it2);
                it2--;
            }
        }
    }


    if (needtochange1)
    {
        ui->lineEdit->setText("");
        qDebug()<<"ready to rewrite file1!"<<endl;
        QFile file001 ( file1Name );
        if(!file001.open(QIODevice::WriteOnly | QIODevice::Text))
        {
                        qDebug()<<"Can't ReWrite the file!"<<endl;
        }
        else
        {
            QTextStream in001(&file001);
            for (QList <QString>::const_iterator it1 = list1.begin(); it1 != list1.end(); it1++)
            {
                ui->lineEdit->setText(  ui->lineEdit->text() + *it1 + " "  );
                in001 << *it1;
                if (it1 + 1 != list1.end() )
                {
#ifdef Q_OS_MAC
in001 << "\n";
#endif

#ifdef Q_OS_LINUX
in001 << "\n";
#endif

#ifdef Q_OS_WIN32
in001 << "\r\n";
#endif
                }
            }
        }

        file001.close();
    }

    if (needtochange2)
    {
        ui->lineEdit_2->setText("");
        qDebug()<<"ready to rewrite file2!"<<endl;
        QFile file002 ( file2Name );
        if(!file002.open(QIODevice::WriteOnly | QIODevice::Text))
        {
                        qDebug()<<"Can't ReWrite the file!"<<endl;
        }
        else
        {
            QTextStream in002(&file002);
            for (QList <QString>::const_iterator it2 = list3.begin(); it2 != list3.end(); it2++)
            {
                ui->lineEdit_2->setText(  ui->lineEdit_2->text() + *it2 + " "   );
                in002 << *it2;
                if (it2 + 1 != list3.end() )
                {
#ifdef Q_OS_MAC
in002 << "\n";
#endif

#ifdef Q_OS_LINUX
in002 << "\n";
#endif

#ifdef Q_OS_WIN32
in002 << "\r\n";
#endif
                }
            }
        }
        file002.close();
    }
    ui->pushButton_3->setEnabled(false);
}

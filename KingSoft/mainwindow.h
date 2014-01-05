#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    QString file1Name;
    QString file2Name;
    QList <QString> list1;
    QList <QString> list3;

    bool needtochange1;
    bool needtochange2;



private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();



    bool matchFiles ();

signals:
    void singleFileLoad ();
};

#endif // MAINWINDOW_H

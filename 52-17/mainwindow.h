#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

// TODO Migliorare nomi ui

namespace Ui {
class MainWindow;
}


class TimerThread : public QThread
{
        Q_OBJECT
signals:
    void progressChanged(int percent);
    void remainingMinutesUpdated(int min);
    void remainingSecondsUpdated(int sec);
    void statusChanged(QString status, bool showMsgbox=false);

public slots:
    void stopTimer();

private:
    void run();
    void startTimer(unsigned min);

    bool __timerEnabled;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onProgressChanged(int percent);
    void onRemainingMinutesUpdated(int min);
    void onRemainingSecondsUpdated(int sec);
    void onStatusChanged(QString status, bool showMsgbox=false);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    TimerThread *timerThread;
};




#endif // MAINWINDOW_H

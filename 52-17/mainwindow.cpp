#include "mainwindow.h"
#include "ui_mainwindow.h"

# include <ctime>
# include <QThread>

using std::time;
using std::time_t;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void
TimerThread::run()
{
    __timerEnabled = true;

    while(true)
    {
        //TODO Dialog
        if(not __timerEnabled) break; emit statusChanged("Lavora, sfaticato che non sei altro!");
        if(not __timerEnabled) break; startTimer(52);
        if(not __timerEnabled) break; emit statusChanged("Ora puoi riposarti un POCO");
        if(not __timerEnabled) break; startTimer(17);
    }

    emit statusChanged("Timer non avviato");
    emit progressChanged(0);
    emit remainingMinutesUpdated(0);
    emit remainingSecondsUpdated(0);
}


void
TimerThread::startTimer(unsigned min)
{
    const time_t startTime = time(NULL);
    const time_t endTime = startTime + (min * 60);

    while((time(NULL) < endTime) && __timerEnabled)
    {
      sleep(1);

        time_t timeSpent = time(NULL) - startTime;
        float timeSpentPercent = (float)timeSpent/(min * 60) * 100;
        int remainingTime = (min * 60) - timeSpent;

        int remainingMin = remainingTime / 60;
        int remainingSec = remainingTime % 60;

        emit progressChanged(timeSpentPercent);
        emit remainingMinutesUpdated(remainingMin);
        emit remainingSecondsUpdated(remainingSec);
    }
}


void
TimerThread::stopTimer()
{
    __timerEnabled = false;

}


void
MainWindow::onProgressChanged(int percent)
{
    ui->progressBar->setValue(percent);
}


void
MainWindow::onRemainingMinutesUpdated(int min)
{
    ui->lcdNumber->display(min);
}


void
MainWindow::onRemainingSecondsUpdated(int sec)
{
    ui->lcdNumber_2->display(sec);
}


void
MainWindow::onStatusChanged(QString status)
{
    ui->label->setText(status);
}


void MainWindow::on_pushButton_clicked()
{
   timerThread = new TimerThread;

   connect(timerThread, SIGNAL(progressChanged(int)), SLOT(onProgressChanged(int)));
   connect(timerThread, SIGNAL(statusChanged(QString)), SLOT(onStatusChanged(QString)));
   connect(timerThread, SIGNAL(remainingMinutesUpdated(int)), SLOT(onRemainingMinutesUpdated(int)));
   connect(timerThread, SIGNAL(remainingSecondsUpdated(int)), SLOT(onRemainingSecondsUpdated(int)));

   connect(timerThread, SIGNAL(finished()), timerThread, SLOT(deleteLater()));
   connect(ui->pushButton_2, SIGNAL(clicked()), timerThread, SLOT(stopTimer()));

   timerThread->start();
}

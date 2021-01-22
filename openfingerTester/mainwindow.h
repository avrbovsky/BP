#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "preprocessing.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Preprocessing preprocessing;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void proprocessingResultsSlot(PREPROCESSING_ALL_RESULTS result);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

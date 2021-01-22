#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "hilditch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    preprocessing.setFeatures(true);
    ui->setupUi(this);
    qRegisterMetaType<PREPROCESSING_ALL_RESULTS>("PREPROCESSING_ALL_RESULTS");
    connect(&preprocessing, SIGNAL(preprocessingDoneSignal(PREPROCESSING_ALL_RESULTS)), this, SLOT(proprocessingResultsSlot(PREPROCESSING_ALL_RESULTS)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Select a file");
    cv::Mat src = imread( path.toStdString().c_str(), cv::IMREAD_GRAYSCALE);
    preprocessing.loadInput(src);


    QPixmap picture(path);

    preprocessing.start();
    ui->label->setPixmap(picture);
}

void MainWindow::proprocessingResultsSlot(PREPROCESSING_ALL_RESULTS result)
{
    cv::imshow("imgSkeleton",result.imgSkeleton);

    Hilditch *hilditch = new Hilditch(result.imgBinarized);

    hilditch->skeletonization();

    cv::imshow("binarized", result.imgBinarized);
    cv::imshow("after", hilditch->imgAfter);
}

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonBad, &QPushButton::clicked, this, &MainWindow::clickedPushButtonBad);
    connect(ui->pushButtonGood, &QPushButton::clicked, this, &MainWindow::clickedPushButtonGood);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedPushButtonGood()
{
    QFileDialog::getExistingDirectory();
}

void MainWindow::clickedPushButtonBad()
{
    QFileDialog::getExistingDirectory();
}


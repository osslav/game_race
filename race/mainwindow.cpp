#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    race = new Race();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(race);
}


MainWindow::~MainWindow()
{
    delete race;
    delete ui;
}


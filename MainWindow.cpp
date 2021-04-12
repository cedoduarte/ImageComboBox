#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->comboBox, &ImageComboBox::currentPixmapChanched, ui->label, &QLabel::setPixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}


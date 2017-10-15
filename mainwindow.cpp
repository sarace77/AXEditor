#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_input_file_dialog(new QFileDialog(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), m_input_file_dialog, SLOT(show()));
    connect(m_input_file_dialog, SIGNAL(accepted()), this, SLOT(loadFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    if(m_input_file_dialog && !m_input_file_dialog->selectedFiles().empty())
    {
        ui->xmlWidget->loadXmlFile(m_input_file_dialog->selectedFiles().first());
    }
}

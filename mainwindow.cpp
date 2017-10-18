#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

#include <QDebug>


#define _PAGE_SIZE_BYTES    5000

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
    qDebug() << "Entered";
    if(m_input_file_dialog && !m_input_file_dialog->selectedFiles().empty())
    {
        QFile   l_file(m_input_file_dialog->selectedFiles().first());
        if(l_file.open(QIODevice::ReadOnly))
        {
            QByteArray l_page = l_file.read(_PAGE_SIZE_BYTES);
            ui->textEdit->setPlainText(l_page);
            m_buffer.clear();
            m_buffer = l_page;
            while(l_file.bytesAvailable() > 0)
            {
                l_page = l_file.read(_PAGE_SIZE_BYTES);
                m_buffer.append(l_page);
                ui->textEdit->append(l_page);
            }
            ui->xmlWidget->decode(m_buffer);
            l_file.close();
        }
    }
}

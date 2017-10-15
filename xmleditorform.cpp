#include "xmleditorform.h"
#include "ui_xmleditorform.h"

#include <QDebug>

XmlEditorForm::XmlEditorForm(QWidget *parent) :
    QWidget(parent),
    m_input_file(NULL),
    m_output_file(NULL),
    ui(new Ui::XmlEditorForm)
{
    ui->setupUi(this);
}

XmlEditorForm::~XmlEditorForm()
{
    delete ui;
}

void XmlEditorForm::loadXmlFile(QString a_file_name)
{
    if(m_input_file)
    {
        delete m_input_file;
    }
    m_input_file = new QFile(a_file_name);
    if(m_input_file->open(QIODevice::ReadOnly))
    {
        m_input_file->close();
    }
    else
    {
        qWarning() << a_file_name << " open error!";
    }
}

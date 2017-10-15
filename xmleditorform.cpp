#include "xmleditorform.h"
#include "ui_xmleditorform.h"

#include <QDebug>

#define _ITEM_TYPE_TEXT "ItemTypeText"
#define _ITEM_TYPE_ATTR "ItemTypeAttribute"

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

QTreeWidgetItem *XmlEditorForm::addChildItem(QXmlStreamReader *a_reader)
{
    QTreeWidgetItem *l_item = NULL;
    if(a_reader)
    {
        l_item = new QTreeWidgetItem();
        l_item->setText(0, QString(a_reader->name().toLatin1()));
        if(!a_reader->attributes().isEmpty())
        {
            QXmlStreamAttributes l_attributes = a_reader->attributes();
            while(!l_attributes.isEmpty())
            {
                QXmlStreamAttribute l_item_attribute = l_attributes.first();
                l_attributes.pop_front();
                QTreeWidgetItem *l_attr_item = new QTreeWidgetItem(l_item);
                l_attr_item->setText(0, "Attribute");
                l_attr_item->setText(1, _ITEM_TYPE_ATTR);
                l_attr_item->setText(2, QString(l_item_attribute.name().toLatin1()));
                l_attr_item->setText(3, QString(l_item_attribute.value().toLatin1()));
            }
        }
        bool l_exit_loop = false;
        while(!l_exit_loop && QXmlStreamReader::EndDocument != a_reader->readNext())
        {
            switch(a_reader->tokenType())
            {
            case QXmlStreamReader::EndDocument:
            case QXmlStreamReader::EndElement:
            case QXmlStreamReader::Invalid:
            {
                l_exit_loop = true;
                break;
            }
            case QXmlStreamReader::StartElement:
            {
                l_item->addChild(addChildItem(a_reader));
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if(!a_reader->isComment() && !a_reader->isWhitespace())
                {
                    QTreeWidgetItem *l_child_item = new QTreeWidgetItem(l_item);
                    l_child_item->setText(0, QString(a_reader->text().toLatin1()));
                    l_child_item->setText(1, _ITEM_TYPE_TEXT);
                }
                break;
            }
            default:
                break;
            }
        }
    }
    return l_item;
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
        QXmlStreamReader    l_reader(m_input_file);
        while(l_reader.readNextStartElement())
        {
            QTreeWidgetItem *l_item = addChildItem(&l_reader);
            if (l_item)
            {
                ui->itemsWidget->addTopLevelItem(l_item);
                ui->itemsWidget->repaint();
                qDebug() << l_item->text(0) << l_item->childCount();
            }
        }
        m_input_file->close();
    }
    else
    {
        qWarning() << a_file_name << " open error!";
    }
}

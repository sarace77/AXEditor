#ifndef XMLEDITORFORM_H
#define XMLEDITORFORM_H

#include <QFile>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QXmlStreamReader>

namespace Ui {
class XmlEditorForm;
}

class XmlEditorForm : public QWidget
{
    Q_OBJECT

    QFile   *m_input_file, m_output_file;

public:
    explicit XmlEditorForm(QWidget *parent = 0);
    ~XmlEditorForm();

private:
    Ui::XmlEditorForm *ui;

    QTreeWidgetItem *addChildItem(QXmlStreamReader *a_reader);

public slots:
    void    loadXmlFile(QString a_file_name);
};

#endif // XMLEDITORFORM_H

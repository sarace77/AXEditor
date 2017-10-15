#ifndef XMLEDITORFORM_H
#define XMLEDITORFORM_H

#include <QWidget>
#include <QFile>

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

public slots:
    void    loadXmlFile(QString a_file_name);
};

#endif // XMLEDITORFORM_H

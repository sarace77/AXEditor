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

public:
    explicit XmlEditorForm(QWidget *parent = 0);
    ~XmlEditorForm();

private:
    Ui::XmlEditorForm *ui;

    QTreeWidgetItem *addChildItem(QXmlStreamReader *a_reader);
    void            copyChildren(QTreeWidgetItem *a_source, QTreeWidgetItem *a_target);
    QTreeWidgetItem *searchChild(QTreeWidgetItem *a_item, QString a_search);

public slots:
    void            decode(QByteArray a_data);

private slots:
    void            on_itemSearch_textChanged(const QString &a_search);
    void            on_itemsWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
};

#endif // XMLEDITORFORM_H

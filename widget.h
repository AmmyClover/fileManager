#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private slots:

    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);
    void on_backButton_clicked();

private:
    Ui::widget *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QList <QModelIndex> memory;
    int countTreeWalking = 0;
    QString strPath;

    void treeWalkingRecord(const QModelIndex &index);
    void disableBackButton();
    void pathTransfer(const QModelIndex &index);

};
#endif // WIDGET_H

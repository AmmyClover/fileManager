#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(dirModel->rootPath());
    ui->treeView->setModel(dirModel);


    fileModel = new QFileSystemModel(this);
    // fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    //fileModel->setRootPath(dirModel->rootPath());
    //fileModel->setReadOnly(false);

    ui->listView->setModel(fileModel);
    ui->listView->horizontalHeader()->resizeSection(0,300);
    ui->listView->horizontalHeader()->moveSection(3,1);
    ui->listView->horizontalHeader()->moveSection(2,3);
    ui->backButton->setDisabled(true);
    ui->forwardButton->setDisabled(true);
}

widget::~widget()
{
    delete ui;
}



void widget::on_treeView_clicked(const QModelIndex &index)
{
    qDebug() << "Path dirModel: " << dirModel->fileInfo(index).absoluteFilePath();
    strPath = dirModel->fileInfo(index).absoluteFilePath();
    if(fileModel->rootPath() != strPath)
    {
        ui->listView->setRootIndex(fileModel->setRootPath(strPath));
        treeWalkingRecord(index);
        pathTransfer(index);
    }
}


void widget::on_listView_doubleClicked(const QModelIndex &index)
{


    strPath = dirModel->fileInfo(index).absoluteFilePath();
    if(dirModel->fileInfo(index).isDir())
    {
        ui->listView->setRootIndex(fileModel->setRootPath(strPath));
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dirModel->fileInfo(index).absoluteFilePath()));
    }

    treeWalkingRecord(index);
    pathTransfer(index);
}



void widget::on_backButton_clicked()
{
    countTreeWalking--;
    ui->listView->setRootIndex(memory[countTreeWalking-1]);

    disableForwardButton();
    disableBackButton();
    qDebug() << "Path dirModel: " << dirModel->filePath(memory[countTreeWalking-1]);
    pathTransfer(memory[countTreeWalking-1]);
}

void widget::on_forwardButton_clicked()
{
    countTreeWalking++;
    ui->listView->setRootIndex(memory[countTreeWalking-1]);


    disableForwardButton();
    disableBackButton();
    pathTransfer(memory[countTreeWalking-1]);
}

void widget::treeWalkingRecord(const QModelIndex &index)
{
    countTreeWalking++;
    memory.resize(countTreeWalking);
    memory.insert(countTreeWalking-1,fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));

    disableForwardButton();
    disableBackButton();
}

void widget::disableBackButton()
{
    if(countTreeWalking-1 == 0)
    {
        ui->backButton->setDisabled(true);
    }
    else
    {
        ui->backButton->setDisabled(false);
    }
}

void widget::disableForwardButton()
{
    qDebug() << countTreeWalking << memory.size();
    if(countTreeWalking+1 == memory.size())
    {
        ui->forwardButton->setDisabled(true);
    }
    else
    {
        ui->forwardButton->setDisabled(false);
    }
}

void widget::pathTransfer(const QModelIndex &index)
{
    ui->lineEdit->setText(dirModel->filePath(index));
}






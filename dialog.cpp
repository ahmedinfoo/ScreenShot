#include "dialog.h"
#include "./ui_dialog.h"
#include <QMessageBox>
#include <QFileDialog>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    foreach (QScreen *screen, QGuiApplication::screens()) {
        ui->comboBox->addItem(screen->name());
    }
ui->btnSave->setEnabled(false);
ui->lblScreen->setText("");
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_btnScreen_clicked()
{
    QScreen *screen=QGuiApplication::screens().at(ui->comboBox->currentIndex());
    if(!screen)
    {
        QMessageBox::critical(this,"error","there is no screen");
        return;
    }
    ui->btnSave->setEnabled(true);
    m_timer.singleShot(500,this,&Dialog::shoot);
    hide();
}


void Dialog::on_btnSave_clicked()
{

QString path = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), tr("PNG Files (*.png)"));
if(path.isEmpty())return;
QFile file(path);

if(!m_image.save(path,"PNG"))
    {
        QMessageBox::critical(this,"Error","Could not save image!");
    }

file.close();

}

void Dialog::shoot()
{

  QScreen *screen=QGuiApplication::screens().at(ui->comboBox->currentIndex());
  m_image=screen->grabWindow(0);
  QPixmap scaled=m_image.scaled(ui->lblScreen->width(),ui->lblScreen->height());
  ui->lblScreen->setPixmap(scaled);
  show();
}


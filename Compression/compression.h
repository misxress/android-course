#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>

namespace Ui {
    class compression;
}



class compression : public QMainWindow
{
    Q_OBJECT

public:
    explicit compression(QWidget *parent = nullptr);
    ~compression();

private slots:
    void on_zip_clicked();

    void on_unzip_clicked();

private:
    Ui::compression* ui;
};

#endif // COMPRESSION_H

#include "compression.h"
#include "ui_compression.h"
#include "lzw.h"
#include "bmp.h"
#include "txt.h"
#include <QDebug>
#include <QString>
#include <string>
#include <cstdio>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;

compression::compression(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::compression)
{
    ui->setupUi(this);
}

compression::~compression(){
    delete ui;
}

void compression::on_zip_clicked()
{
      //定义文件对话框类
      QFileDialog *fileDialog = new QFileDialog(this);
      //定义文件对话框标题
      fileDialog->setWindowTitle(tr("打开文件"));
      //设置默认文件路径
      fileDialog->setDirectory(".");
      //设置文件过滤器
      fileDialog->setNameFilter(tr("text(*.txt);;""Images(*.bmp)"));
      //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
      fileDialog->setFileMode(QFileDialog::ExistingFiles);
      //设置视图模式
      fileDialog->setViewMode(QFileDialog::Detail);
      //打印所有选择的文件的路径
      lzw lzwTool;
      QString QFileName;
      string filename;
      if (fileDialog->exec()) {
        QFileName = fileDialog->selectedFiles()[0];
        filename = QFileName.toStdString();
      }

      if(filename.length() == 0) {
          return;
      }

      string outputname = filename+".lzw";

      if(filename.at(filename.length() - 1) == 'p') {
          //bmp文件
          char c_filename[50],c_outputname[50];
          strcpy(c_filename,filename.c_str());
          strcpy(c_outputname,outputname.c_str());
          bmp bmpTool;
          bmpTool.readBmp(c_filename);
          bmpTool.setLzw(lzwTool.encode(bmpTool.getData()));
          bmpTool.writeLzw(c_outputname);
      } else if(filename.at(filename.length() - 1) == 't') {
          //txt文件
          char c_filename[50],c_outputname[50];
          strcpy(c_filename,filename.c_str());
          strcpy(c_outputname,outputname.c_str());
          txt txtTool;
          txtTool.readTxt(c_filename);
          txtTool.setLzw(lzwTool.encode(txtTool.getTxtBuf()));
          txtTool.writeLzw(c_outputname);
      }

}

void compression::on_unzip_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("lzw(*.*.lzw)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径

    lzw lzwTool;
    QString QFileName;
    string filename;
    if (fileDialog->exec()) {
      QFileName = fileDialog->selectedFiles()[0];
      filename = QFileName.toStdString();
    }

    if(filename.length() == 0) {
        return;
    }

    string outputname = string(filename);
    outputname.erase(outputname.length() - 4);

    if(filename.at(filename.length() - 5) == 'p') {
        //bmp文件
        char c_filename[50],c_outputname[50];
        strcpy(c_filename,filename.c_str());
        strcpy(c_outputname,outputname.c_str());
        bmp bmpTool;
        bmpTool.readLzw(c_filename);
        bmpTool.setData(lzwTool.decode(bmpTool.getLzw()));
        bmpTool.writeBmp(c_outputname);
    } else if(filename.at(filename.length() - 5) == 't') {
        //txt文件
        char c_filename[50],c_outputname[50];
        strcpy(c_filename,filename.c_str());
        strcpy(c_outputname,outputname.c_str());
        txt txtTool;
        txtTool.readLzw(c_filename);
        txtTool.setTxt(lzwTool.decode(txtTool.getLzwBuf()));
        txtTool.writeTxt(c_outputname);
    }
}

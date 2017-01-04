#pragma once
#include "smart_zip_qt.h"

#include <QPushButton>
#include <QDebug>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QScrollBar>
#include <QGridLayout>
#include <QTextBrowser>
#include <QFileDialog>
#include <Qdir>
#include <QMessageBox>
#include <QApplication>
#include <QTextCodec>
#include <QLabel>
#include <thread>

Smart_Zip_QT::Smart_Zip_QT(QWidget *parent)
: QMainWindow(parent)
{
	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec::setCodecForLocale(codec);

	ui.setupUi(this);
	QObject::connect(ui.pushButton_intput, SIGNAL(clicked()), this, SLOT(openInputPath()));
	QObject::connect(ui.pushButton_output, SIGNAL(clicked()), this, SLOT(openOuputPath()));
	QObject::connect(ui.pushButton_run, SIGNAL(clicked()), this, SLOT(compressStart()));
	ui.combobox_choose->addItem(QString(QStringLiteral("批量")));
	ui.combobox_choose->addItem(QString(QStringLiteral("单张")));
	QScrollBar * scV = ui.scrollArea->verticalScrollBar();
	QScrollBar * scV2 = ui.scrollArea_2->verticalScrollBar();
	QScrollBar * scH = ui.scrollArea->horizontalScrollBar();
	QScrollBar * scH2 = ui.scrollArea_2->horizontalScrollBar();

	connect(scV, SIGNAL(valueChanged(int)), scV2, SLOT(setValue(int)));
	connect(scV2, SIGNAL(valueChanged(int)), scV, SLOT(setValue(int)));
	connect(scH, SIGNAL(valueChanged(int)), scH2, SLOT(setValue(int)));
	connect(scH2, SIGNAL(valueChanged(int)), scH, SLOT(setValue(int)));
	//	QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)), horizontalScrollBar_2, SLOT(setValue(int)));
	//	QObject::connect(horizontalScrollBar_2, SIGNAL(valueChanged(int)), horizontalScrollBar, SLOT(setValue(int)));	  

	showImgIndex = 0;
	connect(ui.pushButton_UpPage, SIGNAL(clicked()), this, SLOT(showImgByIndex()));
	connect(ui.pushButton_DownPage, SIGNAL(clicked()), this, SLOT(showImgByIndex()));

	//设置晶体管控件QLCDNumber能显示的位数    
	ui.lcdNumber->setDigitCount(10);
	//设置显示的模式为十进制    
	ui.lcdNumber->setMode(QLCDNumber::Dec);
	//设置显示方式    
	ui.lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	sizep = 0;
	sizea = 0;

}

Smart_Zip_QT::~Smart_Zip_QT()
{

}

void Smart_Zip_QT::openInputPath()
{
	quint64 size = 0;
	
	switch (ui.combobox_choose->currentIndex())
	{
	case 0:
	{
			  //QString type
			  //inputPath = QFileDialog::getOpenFileName(this, QString("open file"), " ", QString("*.jpg *.bmp *.png"));


			  inputPath = QFileDialog::getExistingDirectory(this, QString("open file"), " ");
			  //QMessageBox::information(this, "ttt",inputPath);
			  QDir dir(inputPath);
			  for each (QFileInfo fileInfo in dir.entryInfoList(QDir::Files))
			  {
				  size += fileInfo.size();
			  }
	}
		
		break;
	case 1:
	{
			  inputPath = QFileDialog::getOpenFileName(this, QString("open file"), "D:\\", "JPEG Files(*.jpg);;BMP Files(*.bmp);;PNG Files(*.png);;GIF Files(*.gif)");
			  QFileInfo fileInfo(inputPath);
			  size = fileInfo.size();			 
	}
		
		break;
	default:
		break;
	}
	
	
	double rate = ((double)(sizep - sizea)) / (double)sizep;
	if (size < 1000)
	{
		ui.label_PreSize->setText(QString::number(size) + QString("B"));
	}
	else if (size < 1000000)
	{
		ui.label_PreSize->setText(QString::number(size / 1000) + QString("KB"));
	}
	else if (size < 1000000000)
	{
		ui.label_PreSize->setText(QString::number(size / 1000000) + QString("MB"));
	}
	else if (size < 1000000000000)
	{
		ui.label_PreSize->setText(QString::number(size / 1000000000) + QString("GB"));
	}
	sizep = size;

	//QString s = QTextCodec::toUnicode(inputPath.toStdString().c_str());
	ui.textEdit_inputPath->setText(inputPath);
	//ui.textEditSrc->setPlainText(tr(inputPath.toStdString().c_str()));
	
}
void Smart_Zip_QT::openOuputPath()
{
	switch (ui.combobox_choose->currentIndex())
	{
	case 0:
	{
		outputPath = QFileDialog::getExistingDirectory(this, QString("open file"), " ");
	}
		break;
	case 1:
	{
			  outputPath = QFileDialog::getExistingDirectory(this, QString("open file"), " ");
			  QFileInfo fileInfo(inputPath);
			  outputPath = outputPath + "\/" + fileInfo.fileName();
			  char drive[10], dir[500], fname[100], ext[10];
			  _splitpath(outputPath.toStdString().c_str(), drive, dir, fname, ext);
			  string extString(ext);
			  if (extString == ".bmp")
			  {
				 
				  extString = string(".jpg");
			  }


			  outputPath = QString(string(string(drive) + string(dir) + string(fname) + extString).c_str());
			  qDebug() << "outputPath" << outputPath;
	}

		break;
	default:
		break;
	}
	//ui.textEdit_outputPath->setText(outputPath);
	ui.textEdit_outputPath->setPlainText(tr(outputPath.toStdString().c_str()));
}

void Smart_Zip_QT::compressStart()
{
	score = ui.spinBox->value();
	startTime.restart();
	bool isOK = false;
	switch (ui.combobox_choose->currentIndex())
	{
	case 0:
	{
			  if (inputPath.isEmpty() || outputPath.isEmpty())
			  {
				  qDebug() << "empty!";
				  qDebug() << inputPath;
				  qDebug() << outputPath;
			  }
			  else
			  {
				  // 	inputPath = "D:/images/31321";
				  // 	outputPath = "D:/images/12312E";
				  qDebug() << "compressStart!";
				  qDebug() << inputPath;
				  qDebug() << outputPath;
				  //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
				  //QTextCodec::setCodecForLocale(codec);
				  QByteArray cpath = inputPath.toLocal8Bit();
				  char *str1 = cpath.data();
				  //QString t = QString::fromLocal8Bit(str1);
				  QByteArray cpath2 = outputPath.toLocal8Bit();
				  char *str2 = cpath2.data();
				
				  if (running(std::string(str1), std::string(str2), score))
				  {
					  QMessageBox::information(this, QString(""), QString("success!"));
					  isOK = true;;
					  //加载压缩图像
					  QImage* img_1 = new QImage;
					  QImage* img_2 = new QImage;

					  if (!(img_1->load(QString::fromLocal8Bit(qImagesProcessed.at(0).src.c_str())))) //加载图像
					  {
						  QMessageBox::information(this,
							  QString(QStringLiteral("打开图像失败")),
							  QString(QStringLiteral("打开图像失败!")));
						  delete img_1;
						  return;
					  }
					  if (!(img_2->load(QString::fromLocal8Bit(qImagesProcessed.at(0).dst.c_str())))) //加载图像
					  {
						  QMessageBox::information(this,
							  QString(QStringLiteral("打开图像失败")),
							  QString(QStringLiteral("打开图像失败!")));
						  delete img_2;
						  return;
					  }

					  //ui.label_inputImage->resize(img->size());
					  ui.label_inputImage->setPixmap(QPixmap::fromImage(*img_1));
					  // ui.label_outputImage->resize(img2->size());
					  ui.label_outputImage->setPixmap(QPixmap::fromImage(*img_2));
					  ui.label_Page->setText(QString(QString::number(showImgIndex + 1) + QString("/") + QString::number(qImagesProcessed.size())));
				  }
				  else
				  {
					  isOK = false;
					  qDebug() << "failed!";
					  QMessageBox::information(this, QString(""), QString("failed!"));
				  }
			  }
	}
		break;
	case 1:
	{
			  string imageSrcPath = inputPath.toStdString();
			  string imageDstPath = outputPath.toStdString();
			  qDebug() << "R: " << imageSrcPath.c_str();
			  qDebug() << "R: " << imageDstPath.c_str();
			  for (int i = 0; i < inputPath.size(); i++)
			  {
				  if (inputPath[i] == '/')
				  {
					  inputPath[i] = '\\';
				  }
			  }
			  for (int i = 0; i < outputPath.size(); i++)
			  {
				  if (outputPath[i] == '/')
				  {
					  outputPath[i] = '\\';
				  }
			  }
			  Compressor * cp = new Compressor();
			  QByteArray cpath = inputPath.toLocal8Bit();
			  char *str1 = cpath.data();
			  QByteArray cpath2 = outputPath.toLocal8Bit();
			  char *str2 = cpath2.data();

			  if (cp->Compress(0, string(str1), string(str2), score))
			  {
				  isOK = true;
				  QImage* img = new QImage;
				  QImage* img2 = new QImage;
				  if (!(img->load(inputPath))) //加载图像
				  {
					  QMessageBox::information(this,
						  tr("打开图像失败"),
						  tr("打开图像失败!"));
					  delete img;
					  return;
				  }
				  if (!(img2->load(outputPath))) //加载图像
				  {
					  QMessageBox::information(this,
						  QStringLiteral("打开图像失败"),
						  QStringLiteral("打开图像失败!"));
					  delete img2;
					  return;
				  }

				  //ui.label_inputImage->resize(img->size());
				  ui.label_inputImage->setPixmap(QPixmap::fromImage(*img));

				  // ui.label_outputImage->resize(img2->size());
				  ui.label_outputImage->setPixmap(QPixmap::fromImage(*img2));

			  }
			  else
			  {
				  QMessageBox::information(this, QString(""), QString("failed!"));
				  isOK = false;
			  }

	}
		break;
	default:
		break;
	}
	//获取文件大小
	quint64 size = 0;
	switch (ui.combobox_choose->currentIndex())
	{
	case 0:
	{

			  for each (imageNames fileName in qImagesProcessed)
			  {
				  //QByteArray cpath = QString(fileName.dst.c_str()).toLocal8Bit();
				  //char *str1 = cpath.data();
				  int handle;
				  handle = open(fileName.dst.c_str(), 0x0100); //open file for read
				  long length = filelength(handle); //get length of file
				  size += length;
				 // QFileInfo fileInfo(QString(fileName.dst.c_str()));
				  //size += fileInfo.size();
				//  QMessageBox::information(this, QString::number(size), QString::number(length));
			  }
	}

		break;
	case 1:
	{
			  QFileInfo fileInfo(outputPath);
			  size = fileInfo.size();
	}
		break;
	}
	sizea = size;
	double rate = ((double)(sizep - sizea)) / (double)sizep;
	if (size < 1000)
	{
		ui.label_CompresSize->setText(QString::number(size) + QString("B"));
	}
	else if (size < 1000000)
	{
		ui.label_CompresSize->setText(QString::number(size/1000) + QString("KB"));
	}
	else if (size < 1000000000)
	{
		ui.label_CompresSize->setText(QString::number(size / 1000000) + QString("MB"));
	}
	else if (size < 1000000000000)
	{
		ui.label_CompresSize->setText(QString::number(size / 1000000000) + QString("GB"));
	}
	
	ui.label_CompresRate->setText(QString::number(rate*100) + QString("%"));
}
void Smart_Zip_QT::showImgByIndex()
{

	QPushButton * b = (QPushButton *)sender();
	int i = 0;
	if (b->objectName() == QString("pushButton_UpPage"))
	{
		i = -1;
	}
	if (b->objectName() == QString("pushButton_DownPage"))
	{
		i = 1;
	}
	showImgIndex += i;
	if (showImgIndex >= qImagesProcessed.size() || showImgIndex < 0)
	{
		return;
	}

	ui.label_Page->setText(QString(QString::number(showImgIndex + 1) + QString("/") + QString::number(qImagesProcessed.size())));
	QImage* img_1 = new QImage;
	QImage* img_2 = new QImage;

	if (!(img_1->load(QString::fromLocal8Bit(qImagesProcessed.at(showImgIndex).src.c_str())))) //加载图像
	{
		QMessageBox::information(this,
			tr("打开图像失败"),
			QString(qImagesProcessed.at(showImgIndex).src.c_str()));
		delete img_1;
		return;
	}
	if (!(img_2->load(QString::fromLocal8Bit(qImagesProcessed.at(showImgIndex).dst.c_str())))) //加载图像
	{
		QMessageBox::information(this,
			tr("打开图像失败"),
			QString(qImagesProcessed.at(showImgIndex).dst.c_str()));
		delete img_2;
		return;
	}
	//ui.label_inputImage->resize(img->size());
	ui.label_inputImage->setPixmap(QPixmap::fromImage(*img_1));
	// ui.label_outputImage->resize(img2->size());
	ui.label_outputImage->setPixmap(QPixmap::fromImage(*img_2));

}
void Smart_Zip_QT::progress(int rate)
{
	ui.progressBar->setValue(rate);
	//获取系统当前时间    
	//QMessageBox::information(this, "", "");
	int mss = startTime.elapsed();
	//设置晶体管控件QLCDNumber上显示的内容   
	int days = mss / (1000 * 60 * 60 * 24);
	int hours = (mss % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60);
	int minutes = (mss % (1000 * 60 * 60)) / (1000 * 60);
	int seconds = (mss % (1000 * 60)) / 1000;
	//ui.lcdNumber->display(seconds);
	ui.lcdNumber->display(QString(QString::number(hours) + QString(":") + QString::number(minutes) + QString(":") + QString::number(seconds)));
}

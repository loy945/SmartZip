#ifndef SMART_ZIP_QT_H
#define SMART_ZIP_QT_H

#include <QtWidgets/QMainWindow>
#include "ui_smart_zip_qt.h"
#include "Compressor.h"
#include "MultiRunning.h"
#include <QString>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QTimer>
#include <QTime>
class Smart_Zip_QT : public QMainWindow, public MultiRunning
{
	Q_OBJECT

public:
	Smart_Zip_QT(QWidget *parent = 0);
	~Smart_Zip_QT();
	QString inputPath;
	QString outputPath;
	int score;
	int showImgIndex;//在窗口中展示图片序号
	int sizep;
	int sizea;
public:
	void progress(int rate);
	QTime  startTime;
private:
	Ui::Smart_Zip_QTClass ui;
private slots:
	void openInputPath();
	void openOuputPath();
	void compressStart();
private slots:
	void showImgByIndex();

};

#endif // SMART_ZIP_QT_H

/********************************************************************************
** Form generated from reading UI file 'smart_zip_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMART_ZIP_QT_H
#define UI_SMART_ZIP_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Smart_Zip_QTClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_intput;
    QPushButton *pushButton_run;
    QLabel *lable_inputPath;
    QTextEdit *textEdit_inputPath;
    QPushButton *pushButton_output;
    QLabel *lable_inputPath_2;
    QTextEdit *textEdit_outputPath;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;
    QLabel *label_Qulity;
    QComboBox *combobox_choose;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_inputImage;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_outputImage;
    QGroupBox *groupBox_2;
    QProgressBar *progressBar;
    QLabel *label_PreSize;
    QLabel *label_CompresSize;
    QLabel *label_8;
    QLCDNumber *lcdNumber;
    QLabel *label_PreSize_3;
    QLabel *label_PreSize_4;
    QLabel *label_PreSize_5;
    QLabel *label_CompresRate;
    QPushButton *pushButton_UpPage;
    QPushButton *pushButton_DownPage;
    QLabel *label_Page;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Smart_Zip_QTClass)
    {
        if (Smart_Zip_QTClass->objectName().isEmpty())
            Smart_Zip_QTClass->setObjectName(QStringLiteral("Smart_Zip_QTClass"));
        Smart_Zip_QTClass->resize(1196, 882);
        centralWidget = new QWidget(Smart_Zip_QTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 571, 131));
        pushButton_intput = new QPushButton(groupBox);
        pushButton_intput->setObjectName(QStringLiteral("pushButton_intput"));
        pushButton_intput->setGeometry(QRect(360, 16, 75, 30));
        pushButton_run = new QPushButton(groupBox);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        pushButton_run->setGeometry(QRect(470, 50, 71, 61));
        lable_inputPath = new QLabel(groupBox);
        lable_inputPath->setObjectName(QStringLiteral("lable_inputPath"));
        lable_inputPath->setGeometry(QRect(10, 15, 100, 30));
        textEdit_inputPath = new QTextEdit(groupBox);
        textEdit_inputPath->setObjectName(QStringLiteral("textEdit_inputPath"));
        textEdit_inputPath->setGeometry(QRect(110, 20, 231, 20));
        textEdit_inputPath->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit_inputPath->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton_output = new QPushButton(groupBox);
        pushButton_output->setObjectName(QStringLiteral("pushButton_output"));
        pushButton_output->setGeometry(QRect(360, 50, 75, 30));
        lable_inputPath_2 = new QLabel(groupBox);
        lable_inputPath_2->setObjectName(QStringLiteral("lable_inputPath_2"));
        lable_inputPath_2->setGeometry(QRect(10, 50, 100, 30));
        textEdit_outputPath = new QTextEdit(groupBox);
        textEdit_outputPath->setObjectName(QStringLiteral("textEdit_outputPath"));
        textEdit_outputPath->setGeometry(QRect(110, 55, 231, 20));
        textEdit_outputPath->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit_outputPath->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 90, 231, 22));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(80);
        horizontalSlider->setSliderPosition(80);
        horizontalSlider->setOrientation(Qt::Horizontal);
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(360, 90, 71, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);
        spinBox->setValue(80);
        label_Qulity = new QLabel(groupBox);
        label_Qulity->setObjectName(QStringLiteral("label_Qulity"));
        label_Qulity->setGeometry(QRect(10, 85, 100, 30));
        combobox_choose = new QComboBox(groupBox);
        combobox_choose->setObjectName(QStringLiteral("combobox_choose"));
        combobox_choose->setGeometry(QRect(470, 20, 69, 22));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 200, 571, 551));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 552, 532));
        label_inputImage = new QLabel(scrollAreaWidgetContents);
        label_inputImage->setObjectName(QStringLiteral("label_inputImage"));
        label_inputImage->setGeometry(QRect(0, 0, 54, 12));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_inputImage->sizePolicy().hasHeightForWidth());
        label_inputImage->setSizePolicy(sizePolicy);
        label_inputImage->setTextFormat(Qt::PlainText);
        label_inputImage->setScaledContents(false);
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(610, 200, 571, 551));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 552, 532));
        label_outputImage = new QLabel(scrollAreaWidgetContents_2);
        label_outputImage->setObjectName(QStringLiteral("label_outputImage"));
        label_outputImage->setGeometry(QRect(0, 0, 54, 12));
        sizePolicy.setHeightForWidth(label_outputImage->sizePolicy().hasHeightForWidth());
        label_outputImage->setSizePolicy(sizePolicy);
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(610, 20, 571, 131));
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 100, 571, 23));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setAutoFillBackground(false);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        label_PreSize = new QLabel(groupBox_2);
        label_PreSize->setObjectName(QStringLiteral("label_PreSize"));
        label_PreSize->setGeometry(QRect(130, 20, 101, 30));
        label_CompresSize = new QLabel(groupBox_2);
        label_CompresSize->setObjectName(QStringLiteral("label_CompresSize"));
        label_CompresSize->setGeometry(QRect(130, 50, 100, 30));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(260, 20, 51, 30));
        lcdNumber = new QLCDNumber(groupBox_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(340, 20, 111, 23));
        label_PreSize_3 = new QLabel(groupBox_2);
        label_PreSize_3->setObjectName(QStringLiteral("label_PreSize_3"));
        label_PreSize_3->setGeometry(QRect(50, 20, 71, 30));
        label_PreSize_4 = new QLabel(groupBox_2);
        label_PreSize_4->setObjectName(QStringLiteral("label_PreSize_4"));
        label_PreSize_4->setGeometry(QRect(50, 50, 71, 30));
        label_PreSize_5 = new QLabel(groupBox_2);
        label_PreSize_5->setObjectName(QStringLiteral("label_PreSize_5"));
        label_PreSize_5->setGeometry(QRect(260, 50, 71, 30));
        label_CompresRate = new QLabel(groupBox_2);
        label_CompresRate->setObjectName(QStringLiteral("label_CompresRate"));
        label_CompresRate->setGeometry(QRect(340, 50, 100, 30));
        label_CompresRate->setAlignment(Qt::AlignCenter);
        pushButton_UpPage = new QPushButton(centralWidget);
        pushButton_UpPage->setObjectName(QStringLiteral("pushButton_UpPage"));
        pushButton_UpPage->setGeometry(QRect(450, 160, 61, 31));
        pushButton_DownPage = new QPushButton(centralWidget);
        pushButton_DownPage->setObjectName(QStringLiteral("pushButton_DownPage"));
        pushButton_DownPage->setGeometry(QRect(520, 160, 61, 31));
        label_Page = new QLabel(centralWidget);
        label_Page->setObjectName(QStringLiteral("label_Page"));
        label_Page->setGeometry(QRect(620, 170, 71, 16));
        Smart_Zip_QTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Smart_Zip_QTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1196, 23));
        Smart_Zip_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Smart_Zip_QTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Smart_Zip_QTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Smart_Zip_QTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Smart_Zip_QTClass->setStatusBar(statusBar);

        retranslateUi(Smart_Zip_QTClass);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(Smart_Zip_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *Smart_Zip_QTClass)
    {
        Smart_Zip_QTClass->setWindowTitle(QApplication::translate("Smart_Zip_QTClass", "\346\231\272\350\203\275\345\216\213\347\274\251\345\267\245\345\205\267", 0));
        groupBox->setTitle(QString());
        pushButton_intput->setText(QApplication::translate("Smart_Zip_QTClass", "\346\265\217\350\247\210", 0));
        pushButton_run->setText(QApplication::translate("Smart_Zip_QTClass", "\350\277\220\350\241\214", 0));
        lable_inputPath->setText(QApplication::translate("Smart_Zip_QTClass", "\350\276\223\345\205\245\345\233\276\347\211\207\350\267\257\345\276\204\357\274\232", 0));
        pushButton_output->setText(QApplication::translate("Smart_Zip_QTClass", "\346\265\217\350\247\210", 0));
        lable_inputPath_2->setText(QApplication::translate("Smart_Zip_QTClass", "\350\276\223\345\207\272\345\233\276\347\211\207\350\267\257\345\276\204\357\274\232", 0));
        label_Qulity->setText(QApplication::translate("Smart_Zip_QTClass", "\345\233\276\347\211\207\350\264\250\351\207\217", 0));
        label_inputImage->setText(QString());
        label_outputImage->setText(QString());
        groupBox_2->setTitle(QString());
        label_PreSize->setText(QApplication::translate("Smart_Zip_QTClass", "0B", 0));
        label_CompresSize->setText(QApplication::translate("Smart_Zip_QTClass", "0B", 0));
        label_8->setText(QApplication::translate("Smart_Zip_QTClass", "\345\216\213\347\274\251\350\200\227\346\227\266", 0));
        label_PreSize_3->setText(QApplication::translate("Smart_Zip_QTClass", "\345\216\213\347\274\251\345\211\215\345\244\247\345\260\217\357\274\232", 0));
        label_PreSize_4->setText(QApplication::translate("Smart_Zip_QTClass", "\345\216\213\347\274\251\345\220\216\345\244\247\345\260\217\357\274\232", 0));
        label_PreSize_5->setText(QApplication::translate("Smart_Zip_QTClass", "\345\216\213\347\274\251\347\216\207\357\274\232", 0));
        label_CompresRate->setText(QApplication::translate("Smart_Zip_QTClass", "0", 0));
        pushButton_UpPage->setText(QApplication::translate("Smart_Zip_QTClass", "\344\270\212\344\270\200\351\241\265", 0));
        pushButton_DownPage->setText(QApplication::translate("Smart_Zip_QTClass", "\344\270\213\344\270\200\351\241\265", 0));
        label_Page->setText(QApplication::translate("Smart_Zip_QTClass", "0/0", 0));
    } // retranslateUi

};

namespace Ui {
    class Smart_Zip_QTClass: public Ui_Smart_Zip_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMART_ZIP_QT_H

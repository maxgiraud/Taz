/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_loading;
    QLabel *label;
    QComboBox *comboBox_load_model;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_saving;
    QLabel *label_3;
    QComboBox *comboBox_save_filename;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QFrame *line_2;
    QFormLayout *formLayout;
    QLabel *numEpochsLabel;
    QLabel *trainingBatchSizeLabel;
    QLineEdit *trainingBatchSizeLineEdit;
    QLabel *displayEpochsLabel;
    QLineEdit *displayEpochsLineEdit;
    QLabel *testingBatchSizeLabel;
    QLineEdit *testingBatchSizeLineEdit;
    QLineEdit *numEpochsLineEdit;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_training;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_9;
    QFormLayout *formLayout_2;
    QLabel *learningRateLabel;
    QLineEdit *learningRateLineEdit;
    QLabel *kpLabel;
    QLineEdit *kpLineEdit;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBox_sec_kp;
    QComboBox *comboBox_sec_kp;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QFrame *line_4;
    QLabel *label_6;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_13;
    QFrame *line_6;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *horizontalSpacer_3;
    QTextBrowser *textBrowser_log;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGraphicsView *graphicsView;
    QWidget *tab_2_test;
    QGraphicsView *graphicsView_2;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_keep_refreshing;
    QSlider *horizontalSlider_snap;
    QLabel *label_slider;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_run;
    QPushButton *pushButton_stop;
    QProgressBar *progressBar;
    QLabel *label_status;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_quit;
    QMenuBar *menuBar;
    QMenu *menuOptions;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1342, 707);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 1321, 671));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMouseTracking(false);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        line = new QFrame(verticalLayoutWidget_2);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox_loading = new QCheckBox(verticalLayoutWidget_2);
        checkBox_loading->setObjectName(QStringLiteral("checkBox_loading"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_loading->sizePolicy().hasHeightForWidth());
        checkBox_loading->setSizePolicy(sizePolicy2);
        checkBox_loading->setLayoutDirection(Qt::LeftToRight);
        checkBox_loading->setTristate(false);

        horizontalLayout->addWidget(checkBox_loading);

        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        comboBox_load_model = new QComboBox(verticalLayoutWidget_2);
        comboBox_load_model->setObjectName(QStringLiteral("comboBox_load_model"));
        comboBox_load_model->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox_load_model->sizePolicy().hasHeightForWidth());
        comboBox_load_model->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(comboBox_load_model);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_saving = new QCheckBox(verticalLayoutWidget_2);
        checkBox_saving->setObjectName(QStringLiteral("checkBox_saving"));
        checkBox_saving->setEnabled(true);
        sizePolicy2.setHeightForWidth(checkBox_saving->sizePolicy().hasHeightForWidth());
        checkBox_saving->setSizePolicy(sizePolicy2);
        checkBox_saving->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_saving);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        comboBox_save_filename = new QComboBox(verticalLayoutWidget_2);
        comboBox_save_filename->setObjectName(QStringLiteral("comboBox_save_filename"));
        comboBox_save_filename->setEnabled(true);
        comboBox_save_filename->setEditable(true);

        horizontalLayout_4->addWidget(comboBox_save_filename);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMouseTracking(false);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_4);

        line_2 = new QFrame(verticalLayoutWidget_2);
        line_2->setObjectName(QStringLiteral("line_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy5);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        numEpochsLabel = new QLabel(verticalLayoutWidget_2);
        numEpochsLabel->setObjectName(QStringLiteral("numEpochsLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, numEpochsLabel);

        trainingBatchSizeLabel = new QLabel(verticalLayoutWidget_2);
        trainingBatchSizeLabel->setObjectName(QStringLiteral("trainingBatchSizeLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, trainingBatchSizeLabel);

        trainingBatchSizeLineEdit = new QLineEdit(verticalLayoutWidget_2);
        trainingBatchSizeLineEdit->setObjectName(QStringLiteral("trainingBatchSizeLineEdit"));
        sizePolicy2.setHeightForWidth(trainingBatchSizeLineEdit->sizePolicy().hasHeightForWidth());
        trainingBatchSizeLineEdit->setSizePolicy(sizePolicy2);

        formLayout->setWidget(1, QFormLayout::FieldRole, trainingBatchSizeLineEdit);

        displayEpochsLabel = new QLabel(verticalLayoutWidget_2);
        displayEpochsLabel->setObjectName(QStringLiteral("displayEpochsLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, displayEpochsLabel);

        displayEpochsLineEdit = new QLineEdit(verticalLayoutWidget_2);
        displayEpochsLineEdit->setObjectName(QStringLiteral("displayEpochsLineEdit"));
        sizePolicy2.setHeightForWidth(displayEpochsLineEdit->sizePolicy().hasHeightForWidth());
        displayEpochsLineEdit->setSizePolicy(sizePolicy2);

        formLayout->setWidget(2, QFormLayout::FieldRole, displayEpochsLineEdit);

        testingBatchSizeLabel = new QLabel(verticalLayoutWidget_2);
        testingBatchSizeLabel->setObjectName(QStringLiteral("testingBatchSizeLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, testingBatchSizeLabel);

        testingBatchSizeLineEdit = new QLineEdit(verticalLayoutWidget_2);
        testingBatchSizeLineEdit->setObjectName(QStringLiteral("testingBatchSizeLineEdit"));
        sizePolicy2.setHeightForWidth(testingBatchSizeLineEdit->sizePolicy().hasHeightForWidth());
        testingBatchSizeLineEdit->setSizePolicy(sizePolicy2);

        formLayout->setWidget(3, QFormLayout::FieldRole, testingBatchSizeLineEdit);

        numEpochsLineEdit = new QLineEdit(verticalLayoutWidget_2);
        numEpochsLineEdit->setObjectName(QStringLiteral("numEpochsLineEdit"));
        sizePolicy2.setHeightForWidth(numEpochsLineEdit->sizePolicy().hasHeightForWidth());
        numEpochsLineEdit->setSizePolicy(sizePolicy2);

        formLayout->setWidget(0, QFormLayout::FieldRole, numEpochsLineEdit);


        verticalLayout_4->addLayout(formLayout);


        verticalLayout->addLayout(verticalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        checkBox_training = new QCheckBox(verticalLayoutWidget_2);
        checkBox_training->setObjectName(QStringLiteral("checkBox_training"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(checkBox_training->sizePolicy().hasHeightForWidth());
        checkBox_training->setSizePolicy(sizePolicy6);
        checkBox_training->setChecked(true);

        horizontalLayout_8->addWidget(checkBox_training);

        line_5 = new QFrame(verticalLayoutWidget_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        sizePolicy5.setHeightForWidth(line_5->sizePolicy().hasHeightForWidth());
        line_5->setSizePolicy(sizePolicy5);
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_5);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        learningRateLabel = new QLabel(verticalLayoutWidget_2);
        learningRateLabel->setObjectName(QStringLiteral("learningRateLabel"));
        learningRateLabel->setEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, learningRateLabel);

        learningRateLineEdit = new QLineEdit(verticalLayoutWidget_2);
        learningRateLineEdit->setObjectName(QStringLiteral("learningRateLineEdit"));
        learningRateLineEdit->setEnabled(true);
        sizePolicy6.setHeightForWidth(learningRateLineEdit->sizePolicy().hasHeightForWidth());
        learningRateLineEdit->setSizePolicy(sizePolicy6);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, learningRateLineEdit);

        kpLabel = new QLabel(verticalLayoutWidget_2);
        kpLabel->setObjectName(QStringLiteral("kpLabel"));
        kpLabel->setEnabled(true);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, kpLabel);

        kpLineEdit = new QLineEdit(verticalLayoutWidget_2);
        kpLineEdit->setObjectName(QStringLiteral("kpLineEdit"));
        kpLineEdit->setEnabled(true);
        sizePolicy6.setHeightForWidth(kpLineEdit->sizePolicy().hasHeightForWidth());
        kpLineEdit->setSizePolicy(sizePolicy6);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, kpLineEdit);


        horizontalLayout_9->addLayout(formLayout_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        checkBox_sec_kp = new QCheckBox(verticalLayoutWidget_2);
        checkBox_sec_kp->setObjectName(QStringLiteral("checkBox_sec_kp"));
        checkBox_sec_kp->setEnabled(true);
        sizePolicy6.setHeightForWidth(checkBox_sec_kp->sizePolicy().hasHeightForWidth());
        checkBox_sec_kp->setSizePolicy(sizePolicy6);

        verticalLayout_6->addWidget(checkBox_sec_kp);

        comboBox_sec_kp = new QComboBox(verticalLayoutWidget_2);
        comboBox_sec_kp->setObjectName(QStringLiteral("comboBox_sec_kp"));
        comboBox_sec_kp->setEnabled(false);
        sizePolicy6.setHeightForWidth(comboBox_sec_kp->sizePolicy().hasHeightForWidth());
        comboBox_sec_kp->setSizePolicy(sizePolicy6);

        verticalLayout_6->addWidget(comboBox_sec_kp);


        horizontalLayout_9->addLayout(verticalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        line_4 = new QFrame(verticalLayoutWidget_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line_4);

        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(label_6);

        line_3 = new QFrame(verticalLayoutWidget_2);
        line_3->setObjectName(QStringLiteral("line_3"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy7);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line_3);


        verticalLayout_9->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));

        horizontalLayout_11->addLayout(verticalLayout_10);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));

        horizontalLayout_11->addLayout(verticalLayout_13);

        line_6 = new QFrame(verticalLayoutWidget_2);
        line_6->setObjectName(QStringLiteral("line_6"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy8);
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_11->addWidget(line_6);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));

        horizontalLayout_11->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));

        horizontalLayout_11->addLayout(verticalLayout_11);


        verticalLayout_9->addLayout(horizontalLayout_11);


        verticalLayout->addLayout(verticalLayout_9);


        verticalLayout_8->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(400, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        verticalLayout_8->addItem(horizontalSpacer_3);

        textBrowser_log = new QTextBrowser(verticalLayoutWidget_2);
        textBrowser_log->setObjectName(QStringLiteral("textBrowser_log"));
        sizePolicy5.setHeightForWidth(textBrowser_log->sizePolicy().hasHeightForWidth());
        textBrowser_log->setSizePolicy(sizePolicy5);
        textBrowser_log->setFrameShape(QFrame::Box);
        textBrowser_log->setFrameShadow(QFrame::Sunken);
        textBrowser_log->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textBrowser_log->setTabStopWidth(8);
        textBrowser_log->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_8->addWidget(textBrowser_log);


        horizontalLayout_6->addLayout(verticalLayout_8);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidget = new QTabWidget(verticalLayoutWidget_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setGeometry(QRect(0, 0, 911, 581));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(20);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy9);
        graphicsView->setFrameShadow(QFrame::Sunken);
        graphicsView->setInteractive(false);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tabWidget->addTab(tab, QString());
        tab_2_test = new QWidget();
        tab_2_test->setObjectName(QStringLiteral("tab_2_test"));
        graphicsView_2 = new QGraphicsView(tab_2_test);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setEnabled(false);
        graphicsView_2->setGeometry(QRect(0, 0, 911, 581));
        sizePolicy7.setHeightForWidth(graphicsView_2->sizePolicy().hasHeightForWidth());
        graphicsView_2->setSizePolicy(sizePolicy7);
        graphicsView_2->setInteractive(false);
        graphicsView_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tabWidget->addTab(tab_2_test, QString());

        verticalLayout_5->addWidget(tabWidget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBox_keep_refreshing = new QCheckBox(verticalLayoutWidget_2);
        checkBox_keep_refreshing->setObjectName(QStringLiteral("checkBox_keep_refreshing"));
        checkBox_keep_refreshing->setChecked(true);

        horizontalLayout_7->addWidget(checkBox_keep_refreshing);

        horizontalSlider_snap = new QSlider(verticalLayoutWidget_2);
        horizontalSlider_snap->setObjectName(QStringLiteral("horizontalSlider_snap"));
        horizontalSlider_snap->setEnabled(false);
        QSizePolicy sizePolicy10(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(horizontalSlider_snap->sizePolicy().hasHeightForWidth());
        horizontalSlider_snap->setSizePolicy(sizePolicy10);
        horizontalSlider_snap->setMaximum(100);
        horizontalSlider_snap->setTracking(true);
        horizontalSlider_snap->setOrientation(Qt::Horizontal);
        horizontalSlider_snap->setInvertedAppearance(false);
        horizontalSlider_snap->setInvertedControls(false);
        horizontalSlider_snap->setTickPosition(QSlider::NoTicks);
        horizontalSlider_snap->setTickInterval(20);

        horizontalLayout_7->addWidget(horizontalSlider_snap);

        label_slider = new QLabel(verticalLayoutWidget_2);
        label_slider->setObjectName(QStringLiteral("label_slider"));

        horizontalLayout_7->addWidget(label_slider);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_7);


        horizontalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_run = new QPushButton(verticalLayoutWidget_2);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));

        horizontalLayout_5->addWidget(pushButton_run);

        pushButton_stop = new QPushButton(verticalLayoutWidget_2);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setEnabled(false);

        horizontalLayout_5->addWidget(pushButton_stop);

        progressBar = new QProgressBar(verticalLayoutWidget_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setValue(0);

        horizontalLayout_5->addWidget(progressBar);

        label_status = new QLabel(verticalLayoutWidget_2);
        label_status->setObjectName(QStringLiteral("label_status"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(label_status->sizePolicy().hasHeightForWidth());
        label_status->setSizePolicy(sizePolicy11);

        horizontalLayout_5->addWidget(label_status);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton_quit = new QPushButton(verticalLayoutWidget_2);
        pushButton_quit->setObjectName(QStringLiteral("pushButton_quit"));

        horizontalLayout_5->addWidget(pushButton_quit);


        verticalLayout_7->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1342, 18));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(checkBox_loading, comboBox_load_model);
        QWidget::setTabOrder(comboBox_load_model, checkBox_saving);
        QWidget::setTabOrder(checkBox_saving, comboBox_save_filename);
        QWidget::setTabOrder(comboBox_save_filename, numEpochsLineEdit);
        QWidget::setTabOrder(numEpochsLineEdit, trainingBatchSizeLineEdit);
        QWidget::setTabOrder(trainingBatchSizeLineEdit, displayEpochsLineEdit);
        QWidget::setTabOrder(displayEpochsLineEdit, testingBatchSizeLineEdit);
        QWidget::setTabOrder(testingBatchSizeLineEdit, checkBox_training);
        QWidget::setTabOrder(checkBox_training, learningRateLineEdit);
        QWidget::setTabOrder(learningRateLineEdit, kpLineEdit);
        QWidget::setTabOrder(kpLineEdit, checkBox_sec_kp);
        QWidget::setTabOrder(checkBox_sec_kp, comboBox_sec_kp);
        QWidget::setTabOrder(comboBox_sec_kp, textBrowser_log);
        QWidget::setTabOrder(textBrowser_log, pushButton_run);
        QWidget::setTabOrder(pushButton_run, pushButton_stop);
        QWidget::setTabOrder(pushButton_stop, pushButton_quit);

        menuBar->addAction(menuOptions->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(checkBox_loading, SIGNAL(toggled(bool)), label, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_loading, SIGNAL(toggled(bool)), comboBox_load_model, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), learningRateLabel, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), learningRateLineEdit, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), kpLabel, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), kpLineEdit, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_sec_kp, SIGNAL(toggled(bool)), comboBox_sec_kp, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), checkBox_sec_kp, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_training, SIGNAL(toggled(bool)), comboBox_sec_kp, SLOT(setEnabled(bool)));
        QObject::connect(comboBox_load_model, SIGNAL(currentIndexChanged(QString)), comboBox_save_filename, SLOT(setEditText(QString)));
        QObject::connect(checkBox_saving, SIGNAL(toggled(bool)), label_3, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_saving, SIGNAL(toggled(bool)), comboBox_save_filename, SLOT(setEnabled(bool)));
        QObject::connect(comboBox_load_model, SIGNAL(activated(QString)), comboBox_save_filename, SLOT(setEditText(QString)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Initialization", nullptr));
        checkBox_loading->setText(QApplication::translate("MainWindow", "Load model", nullptr));
        label->setText(QApplication::translate("MainWindow", "Filename", nullptr));
        checkBox_saving->setText(QApplication::translate("MainWindow", "Save as", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Filename", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Dataset", nullptr));
        numEpochsLabel->setText(QApplication::translate("MainWindow", "num epochs", nullptr));
        trainingBatchSizeLabel->setText(QApplication::translate("MainWindow", "training batch size", nullptr));
        trainingBatchSizeLineEdit->setText(QApplication::translate("MainWindow", "10", nullptr));
        displayEpochsLabel->setText(QApplication::translate("MainWindow", "display/epochs", nullptr));
        displayEpochsLineEdit->setText(QApplication::translate("MainWindow", "10", nullptr));
        testingBatchSizeLabel->setText(QApplication::translate("MainWindow", "testing batch size", nullptr));
        testingBatchSizeLineEdit->setText(QApplication::translate("MainWindow", "10", nullptr));
        numEpochsLineEdit->setText(QApplication::translate("MainWindow", "100", nullptr));
        checkBox_training->setText(QApplication::translate("MainWindow", "Training", nullptr));
        learningRateLabel->setText(QApplication::translate("MainWindow", "learning rate", nullptr));
        learningRateLineEdit->setText(QApplication::translate("MainWindow", "0.001", nullptr));
        kpLabel->setText(QApplication::translate("MainWindow", "keep prob", nullptr));
        kpLineEdit->setText(QApplication::translate("MainWindow", "0.75", nullptr));
        checkBox_sec_kp->setText(QApplication::translate("MainWindow", "secondary keep prob", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Monitoring", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2_test), QApplication::translate("MainWindow", "Tab 2", nullptr));
        checkBox_keep_refreshing->setText(QApplication::translate("MainWindow", "keep refreshing", nullptr));
        label_slider->setText(QApplication::translate("MainWindow", "0 / 0", nullptr));
        pushButton_run->setText(QApplication::translate("MainWindow", "Run", nullptr));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        label_status->setText(QApplication::translate("MainWindow", "Waiting...", nullptr));
        pushButton_quit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

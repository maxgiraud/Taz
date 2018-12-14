#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QFileSystemWatcher>
#include <QScrollBar>
#include <QLabel>
#include <QDir>

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <cmath>

// **** SET PATH MANUALLY ****
#define MAIN_PATH "/home/max/projets/python/tensorflow/autoencoder/"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Welcome();
    void InitFolderVars();
    void CleanFolderSystem();
    void DestroyMonitorLabels();
    void RefreshProjectList();
    void LoadImage(std::string filename);
    void LoadImage2(std::string filename);
    void run();
    void abort();

    void EpochChanged(std::string epoch);
    void TrainingBegin();
    void TrainingOver();
    void EvaluationBegin();
    void EvaluationOver();
    void ProcessComplete();
    void LoadWorkingDirectory();
    void SaveWorkingDirectory();

    void log(std::string text);
    void FileMonitoring();
    void SetStatusLabel(std::string text);
    void RefreshMonitoring(int pos, std::string label_name, std::__cxx11::string label_text);
    void RefreshSliderLabel(int value);
    void CreateMonitorLabel(int pos, std::string name, std::string text);
    void RefreshMonitorLabel(int pos, std::string text);
    bool IsLabelStored(int pos, std::string name);
    std::string ReadQuote(std::ifstream &stream);

private slots:
    void on_pushButton_quit_clicked();
    void on_pushButton_run_clicked();
    void on_pushButton_stop_clicked();
    void on_horizontalSlider_snap_valueChanged(int value);
    void on_checkBox_keep_refreshing_toggled(bool checked);
    void info_from_process();

private:
    Ui::MainWindow *ui;

    const std::string main_path = MAIN_PATH;
    std::string _log;

    std::vector<QLabel*> m_mon_label_r;
    std::vector<QLabel*> m_mon_text_r;
    std::vector<QLabel*> m_mon_label_l;
    std::vector<QLabel*> m_mon_text_l;

    bool m_waiting_to_close;
    bool m_keep_refresh;
    bool m_aborting;

    bool f_running;
    bool f_training;
    bool f_loading;
    bool f_saving;
    std::string f_load_foldername;
    std::string f_save_foldername;
    int f_num_epoch;
    int f_curr_epoch;
    int f_display_step;
    int f_num_packet;
    std::string m_log_screen_path;
};

void task(std::string run_cmd);



#endif // MAINWINDOW_H

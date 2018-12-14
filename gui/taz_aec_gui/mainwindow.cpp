#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _log = "";

    InitFolderVars();

    m_aborting = false;
    m_keep_refresh = true;
    m_log_screen_path = "";
    m_waiting_to_close = false;

    CleanFolderSystem();
    RefreshProjectList();

    FileMonitoring();

    Welcome();

}

MainWindow::~MainWindow()
{
    CleanFolderSystem();
    delete ui;
}

void MainWindow::Welcome() {

    log("[welcome] TAZ autoencoder engine\n\n");

    LoadImage(main_path+"data/gui/welcome_image.png");
}

void MainWindow::InitFolderVars() {

    f_num_packet = 0;
    f_running = false;
    f_training = false;
    f_loading = false;
    f_saving = false;
    f_save_foldername = "";
    f_load_foldername = "";
}

void MainWindow::CleanFolderSystem() {

    f_num_packet = 0;
    string cmd = "rm -rv ";
    cmd += main_path+"data/temp/* "+main_path+"data/io/* "+main_path+"save/temp/*";
    system(cmd.c_str());
    cmd = "touch ";
    cmd += main_path+"data/io/run_ifile.txt "+main_path+"data/io/run_ofile.txt";
    system(cmd.c_str());

}

void MainWindow::DestroyMonitorLabels() {

    for (uint i(0); i < m_mon_label_l.size(); i++) {
        ui->verticalLayout_10->removeWidget(m_mon_label_l[i]);
        ui->verticalLayout_13->removeWidget(m_mon_text_l[i]);
        m_mon_label_l[i]->close();
        m_mon_text_l[i]->close();
    }
    for (uint i(0); i < m_mon_label_r.size(); i++) {
        ui->verticalLayout_12->removeWidget(m_mon_label_r[i]);
        ui->verticalLayout_11->removeWidget(m_mon_text_r[i]);
        m_mon_label_r[i]->close();
        m_mon_text_r[i]->close();
    }
    m_mon_label_l.clear();
    m_mon_text_l.clear();
    m_mon_label_r.clear();
    m_mon_text_r.clear();
}

void MainWindow::on_pushButton_quit_clicked() {

    m_waiting_to_close = true;
    if (f_running && !m_aborting) { abort(); }
    else { close(); }
}

void MainWindow::on_pushButton_run_clicked() {

    run();
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_run->setEnabled(false);
}

void MainWindow::on_pushButton_stop_clicked() { abort(); }

void MainWindow::abort() {

    ui->pushButton_stop->setEnabled(false);
    string filepath = main_path;
    filepath += "data/io/run_ifile.txt";
    ofstream file(filepath.c_str());
    file << "abort\n";
    file.close();

    log("[thread] abort\n");
    m_aborting = true;
}

void MainWindow::on_horizontalSlider_snap_valueChanged(int value) {

    value = round(value/(f_display_step+0.))*f_display_step;
    if (value > f_curr_epoch) { value = f_curr_epoch; }
    ui->horizontalSlider_snap->setValue(value);

    if (!m_keep_refresh) {

        RefreshSliderLabel(value);
        string snap = main_path;
        if (value <= f_num_epoch) { snap += "data/temp/instants/instant_"+to_string(value)+".png"; }
        else { snap += "data/temp/instants/instant_"+to_string(f_curr_epoch)+".png"; }
        LoadImage(snap);

        snap = main_path;
        if (value <= f_num_epoch) { snap += "data/temp/instants/instant_"+to_string(value)+"_2.png"; }
        else { snap += "data/temp/instants/instant_"+to_string(f_curr_epoch)+"_2.png"; }
        LoadImage2(snap);
    }
}

void MainWindow::on_checkBox_keep_refreshing_toggled(bool checked) {

    m_keep_refresh = checked;
    string snap = main_path;

    if (checked) {

        ui->horizontalSlider_snap->setEnabled(false);
        ui->horizontalSlider_snap->setValue(f_curr_epoch);
        RefreshSliderLabel(f_curr_epoch);
        LoadImage(m_log_screen_path);
    } else if (m_log_screen_path != ""){
        ui->horizontalSlider_snap->setEnabled(true);
        snap += "data/temp/instants/instant_"+to_string(ui->horizontalSlider_snap->value())+".png";
        LoadImage(snap);
        snap = main_path+"data/temp/instants/instant_"+to_string(ui->horizontalSlider_snap->value())+"_2.png";
        LoadImage2(snap);
    }
}

void MainWindow::LoadImage(string filename) {

    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap image(filename.c_str());
    scene->setBackgroundBrush(image.scaled(938,607,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::LoadImage2(string filename) {

    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap image(filename.c_str());
    scene->setBackgroundBrush(image.scaled(938,607,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->show();
}

void task(string run_cmd) {

    system(run_cmd.c_str());
}

void MainWindow::run() {

    f_running = true;

    f_save_foldername = ui->comboBox_save_filename->currentText().toStdString();
    f_load_foldername = ui->comboBox_load_model->currentText().toStdString();

    // Checking options
    if (ui->checkBox_saving->isChecked() && f_save_foldername == "") {
        log("[error] missing saving folder name\n");
        return;
    }

    SetStatusLabel("Initializing thread");
    log("[init] writing option file...");

    ofstream out_file((main_path+"data/gui/params.py").c_str());

    if (f_save_foldername != "") { f_save_foldername = main_path+"save/"+f_save_foldername; }
    if (f_load_foldername != "") { f_load_foldername = main_path+"save/"+f_load_foldername; }

    f_training = ui->checkBox_training->isChecked();
    f_loading = ui->checkBox_loading->isChecked();
    f_saving = ui->checkBox_saving->isChecked();

    f_num_epoch = stoi(ui->numEpochsLineEdit->text().toStdString());
    f_display_step = stoi(ui->displayEpochsLineEdit->text().toStdString());

    if (f_loading)  { LoadWorkingDirectory(); }
    else {
        QString path = (main_path+"data/temp/instants/").c_str();
        QDir().mkdir(path);
    }

    ui->horizontalSlider_snap->setMinimum(f_display_step);
    ui->horizontalSlider_snap->setMaximum(f_num_epoch);
    ui->horizontalSlider_snap->setSingleStep(f_num_epoch/f_display_step);

    string training, loading, saving;
    if (f_training) { training = "True"; }
    else            { training = "False"; }
    if (f_saving)   { saving = "True";}
    else            { saving = "False"; }
    if (f_loading)  { loading = "True"; }
    else            { loading = "False"; }

    out_file << "training = " << training << endl;
    out_file << "loading = " << loading << endl;
    out_file << "saving = " << saving << endl;
    out_file << "load_foldername = \"" << f_load_foldername << "\"" << endl;
    out_file << "save_foldername = \"" << f_save_foldername << "\"" << endl;
    out_file << "num_steps = " << f_num_epoch << endl;
    out_file << "batch_size = " << ui->trainingBatchSizeLineEdit->text().toStdString() << endl;
    out_file << "display_steps = " << f_display_step << endl;
    out_file << "test_dataset_size = " << ui->testingBatchSizeLineEdit->text().toStdString() << endl;
    out_file << "learning_rate = " << ui->learningRateLineEdit->text().toStdString() << endl;
    out_file << "kp = " << ui->kpLineEdit->text().toStdString() << endl;
    out_file.close();
    log("done\n");

    log("[init] merging parameter and autoencoder files...");
    string merge_cmd = "cp -v ";
    merge_cmd += main_path+"data/gui/tools.py "+main_path+"data/temp/tools.py";
    system(merge_cmd.c_str());
    merge_cmd = "cp -v ";
    merge_cmd += main_path+"data/gui/models.py "+main_path+"data/temp/models.py";
    system(merge_cmd.c_str());
    merge_cmd = "cp -v ";
    merge_cmd += main_path+"data/gui/imports.py "+main_path+"data/temp/main.py";
    system(merge_cmd.c_str());
    merge_cmd = "cat ";
    merge_cmd += main_path+"data/gui/pathfinder.py >> "+main_path+"data/temp/main.py";
    system(merge_cmd.c_str());
    merge_cmd = "cat ";
    merge_cmd += main_path+"data/gui/params.py >> "+main_path+"data/temp/main.py";
    system(merge_cmd.c_str());
    merge_cmd = "cat ";
    merge_cmd += main_path+"data/gui/autoenc_gui.py >> "+main_path+"data/temp/main.py";
    system(merge_cmd.c_str());
    merge_cmd = "chmod +x ";
    merge_cmd += main_path+"data/temp/main.py";
    system(merge_cmd.c_str());
    log("done\n");

    log("[init] running computing thread\n\n");
    string run_cmd = "";
    run_cmd += main_path+"data/temp/main.py &";
    std::thread th_compute(task,run_cmd);
    th_compute.join();
}

void MainWindow::RefreshProjectList() {

    ui->comboBox_load_model->clear();
    ui->comboBox_save_filename->clear();

    string cmd = "ls ";
    cmd += main_path+"save > "+main_path+"data/gui/save_list.dat";
    system(cmd.c_str());

    string temp;
    string filepath = main_path+"data/gui/save_list.dat";
    ifstream save_file(filepath.c_str());
    if (!ui->checkBox_loading->isChecked()) {
        ui->comboBox_load_model->addItem(tr(""));
    }
    //ui->comboBox_save_filename->addItem(tr("temp"));
    while (save_file >> temp) {
        if (temp != "backup") {
            ui->comboBox_load_model->addItem(tr(temp.c_str()));
            ui->comboBox_save_filename->addItem(tr(temp.c_str()));
        }
    }
    save_file.close();
}

void MainWindow::log(string text) {

    _log += text;
    QString out = QString::fromStdString(_log);
    ui->textBrowser_log->setText(out);
    QScrollBar* vsb = ui->textBrowser_log->verticalScrollBar();
    vsb->setValue(vsb->maximum());
}

void MainWindow::EpochChanged(string epoch) {

    f_curr_epoch = stoi(epoch);
    log("[thread] Epoch \t"+epoch+"\t/ \t"+to_string(f_num_epoch)+"\r");
    ui->progressBar->setValue(stod(epoch)/(f_num_epoch+0.)*100);
    if (m_keep_refresh) {
        RefreshSliderLabel(stoi(epoch));
        ui->horizontalSlider_snap->setValue(stoi(epoch));
    }
    //DestroyMonitorLabels();
}

void MainWindow::TrainingBegin() {

    SetStatusLabel("Training...");
    log("[thread] begin training\n");
    ui->progressBar->setValue(0);
    ui->pushButton_stop->setEnabled(true);
    ui->progressBar->setEnabled(true);
}

void MainWindow::TrainingOver() {

    log("[thread] training done\n");
    ui->pushButton_stop->setEnabled(false);
}

void MainWindow::EvaluationBegin() {

    SetStatusLabel("Evaluating...");
    log("[thread] begin evaluation\n");
    ui->pushButton_stop->setEnabled(false);
}

void MainWindow::EvaluationOver() {

    log("[thread] evaluation done\n");
}

void MainWindow::ProcessComplete() {

    if (f_saving) { SaveWorkingDirectory(); }

    InitFolderVars();
    RefreshProjectList();

    log("[thread] Complete\n\n");
    ui->pushButton_run->setEnabled(true);
    f_running = false;

    if (m_waiting_to_close) { close(); }
    SetStatusLabel("Done");
}

void MainWindow::info_from_process() {

    string filepath = main_path;
    filepath += "data/io/run_ofile.txt";
    ifstream file(filepath.c_str());

    int num_packet;
    file >> num_packet;
    if (num_packet != f_num_packet) {
        return;
    }

    string key, value;
    while (file >> key) {
        file >> value;

        if (key == "epoch")                 { EpochChanged(value); }
        else if (key == "screen_log")       { m_log_screen_path = value;
                                            if (m_keep_refresh) LoadImage(value); }
        else if (key == "training_begin")   { TrainingBegin(); }
        else if (key == "training_done")    { TrainingOver(); }
        else if (key == "testing_begin")    { EvaluationBegin(); }
        else if (key == "testing_done")     { EvaluationOver(); }
        else if (key == "finish")           { ProcessComplete(); }
        else if (key == "monitoring") {
            int pos = stoi(value);
            string label_name, label_text;
            label_name = ReadQuote(file);
            label_text = ReadQuote(file);

            RefreshMonitoring(pos, label_name, label_text);
        }
    }
    file.close();

    f_num_packet++;
}


void MainWindow::LoadWorkingDirectory() {

    ifstream save_file((f_load_foldername+"/gui_savestate.txt").c_str());
    save_file >> f_curr_epoch;
    f_num_epoch += f_curr_epoch;
    save_file.close();

    string cmd = "rm -rv ";
    cmd += main_path+"data/temp/instants/";
    system(cmd.c_str());
    cmd = "cp -rv ";
    cmd += f_load_foldername+"/instants/ "+main_path+"data/temp/";
    system(cmd.c_str());
}

void MainWindow::SaveWorkingDirectory() {

    ofstream save_file((f_save_foldername+"/gui_savestate.txt").c_str());
    save_file << f_curr_epoch;
    save_file.close();

    string cmd = "cp -rv ";
    cmd += main_path+"data/temp/instants/ "+f_save_foldername+"/";
    system(cmd.c_str());
    cout << "caca" << endl;

}

void MainWindow::SetStatusLabel(string text) {

    ui->label_status->setText(text.c_str());
}

void MainWindow::RefreshMonitoring(int pos, string label_name, string label_text) {

    if (!IsLabelStored(pos,label_name)) {
        CreateMonitorLabel(pos, label_name, label_text);
    } else {
        RefreshMonitorLabel(pos, label_text);
    }
}

void MainWindow::CreateMonitorLabel(int pos, string name, string text) {

    QLabel *label_name = new QLabel(name.c_str(),this);
    QLabel *label_text = new QLabel(text.c_str(),this);
    if (pos%2 == 0) {
        m_mon_label_l.push_back(label_name);
        m_mon_text_l.push_back(label_text);
        ui->verticalLayout_10->addWidget(label_name);
        ui->verticalLayout_13->addWidget(label_text);
    } else {
        m_mon_label_r.push_back(label_name);
        m_mon_text_r.push_back(label_text);
        ui->verticalLayout_12->addWidget(label_name);
        ui->verticalLayout_11->addWidget(label_text);
    }
}

void MainWindow::RefreshMonitorLabel(int pos, string text) {

    if (pos%2==0)   { m_mon_text_l[pos/2]->setText(text.c_str()); }
    else            { m_mon_text_r[pos/2]->setText(text.c_str()); }
}

bool MainWindow::IsLabelStored(int pos, string name) {

    bool out = false;
    if (pos%2==0) {
        for (uint i(0); i < m_mon_label_l.size(); i++) {
            if (m_mon_label_l[i]->text() == name.c_str()) {
                out = true;
            }
        }
    } else {
        for (uint i(0); i < m_mon_label_r.size(); i++) {
            if (m_mon_label_r[i]->text() == name.c_str()) {
                out = true;
            }
        }
    }

    return out;
}

string MainWindow::ReadQuote(ifstream &stream) {

    string out(""), temp;
    stream >> temp;
    temp.erase(0,1);
    while (temp[temp.size()-1] != '"') {
        out += " "+temp;
        stream >> temp;
    }
    out += " "+temp;
    out.resize(out.size()-1);

    return out;
}

void MainWindow::FileMonitoring() {

    QFileSystemWatcher *ioWatcher = new QFileSystemWatcher(this);
    QString monitor_path = (main_path+"data/io/run_ofile.txt").c_str();
    ioWatcher->addPath(monitor_path);
    QObject::connect(ioWatcher, SIGNAL(fileChanged(QString)), this, SLOT(info_from_process()));
}

void MainWindow::RefreshSliderLabel(int value) {

    string label_slider_text= to_string(value)+" / "+to_string(f_num_epoch);
    ui->label_slider->setText(label_slider_text.c_str());
}




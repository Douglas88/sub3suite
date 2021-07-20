#include "Brute.h"
#include "ui_Brute.h"

/*

  add an advanced option that resolves an item on wordlist with all nameservers..
  first obtains the server from the domain name, then uses those nameservers as default nameservers
  for the scan...

*/

/*

  add a function to first test if the domain you are testing is an active one
  to reduce un-necessary lookups

*/

/*

 create a notes tab that takes all notes for the related scans of the project...
 each new domain enumerated and its x-stics are to be recorded...
 use of wildcard in each phase...
*/

/*
 *
 * must be project base, on launch asks if you want a quick scan or launch a project base...
 *
 */

// initiate everything in the constructor...

/*************************** Class Constructor & Deconstructor *************************/
Brute::Brute(QWidget *parent, ResultsModel *resultsModel) : BaseClass(parent), ui(new Ui::Brute),
      m_resultsModel(resultsModel),
      m_scanStatus(new ScanStatus),
      m_scanConfig(new ScanConfig),
      m_scanArguments(new brute::ScanArguments)
{
    ui->setupUi(this);
    //...
    ui->lineEdit_target->setPlaceholderText("Enter Target eg. example.com");
    ui->lineEdit_wordlist->setPlaceholderText("Enter a new Wordlist...");
    ui->lineEdit_multipleTargets->setPlaceholderText("Enter a new Target...");
    //...
    ui->pushButton_stop->setDisabled(true);
    ui->pushButton_pause->setDisabled(true);
    //...
    ui->frame_targets->hide();
    ui->progressBar->hide();
    //...
    ui->splitter->setSizes(QList<int>()<<200<<100);
    //...
    m_resultsModel->brute->setHorizontalHeaderLabels({"Subdomain Name:", "IpAddress"});
    ui->tableView_results->setModel(m_resultsModel->brute);
    //...
    m_scanArguments->wordlist = ui->listWidget_wordlist;
}
Brute::~Brute(){
    delete m_scanStatus;
    delete m_scanConfig;
    delete m_scanArguments;
    //...
    delete ui;
}

/*********************************** START Enumeration **********************************/
void Brute::on_pushButton_start_clicked(){
    ///
    /// checking if all requirements are satisfied before scan if not prompt error
    /// then exit function...
    ///
    if(ui->comboBox_target->currentIndex() == 0 && ui->lineEdit_target->text().isEmpty()){
        QMessageBox::warning(this, TITLE_ERROR, "Please Enter the Target for Enumeration!");
        return;
    }
    if(ui->comboBox_target->currentIndex() == 1 && ui->listWidget_targets->count() < 1){
        QMessageBox::warning(this, TITLE_ERROR, "Please Enter the Targets for Enumeration!");
        return;
    }
    if(ui->listWidget_wordlist->count() < 1){
        QMessageBox::warning(this, TITLE_ERROR, "Please Enter the Wordlist for Enumeration!");
        return;
    }
    ///
    /// disabling & Enabling widgets...
    ///
    ui->pushButton_start->setDisabled(true);
    ui->pushButton_pause->setEnabled(true);
    ui->pushButton_stop->setEnabled(true);
    ui->progressBar->show();
    ///
    /// Resetting the scan arguments values...
    ///
    m_scanArguments->currentWordlistToEnumerate = 0;
    m_scanArguments->currentTargetToEnumerate = 0;
    m_scanArguments->targetList.clear();
    ui->progressBar->reset();
    m_scanArguments->progress = 0;

    /****** Processing targets if user chooses subdomain bruteForcing *******/
    if(ui->radioButton_subBrute->isChecked())
    {
        m_scanArguments->subBrute = true;
        m_scanArguments->tldBrute = false;

        if(ui->comboBox_target->currentIndex() == SINGLE_TARGET)
        {
            m_scanArguments->targetList.append(TargetNameFilter(ui->lineEdit_target->text(), ENGINE::SUBBRUTE));
            ///
            /// for a single target, progress equals to the total number of wordlist...
            ///
            ui->progressBar->setMaximum(ui->listWidget_wordlist->count());
        }
        if(ui->comboBox_target->currentIndex() == MULTIPLE_TARGETS)
        {
            for(int i = 0; i < ui->listWidget_targets->count(); i++)
            {
                m_scanArguments->targetList.append(TargetNameFilter(ui->listWidget_targets->item(i)->text(), ENGINE::SUBBRUTE));
            }
            ///
            /// for multiple targets, progress equals to the total number of wordlist times the total number of targets...
            ///
            ui->progressBar->setMaximum(ui->listWidget_wordlist->count()*m_scanArguments->targetList.count());
        }
    }

    /****** Processing targets if user chooses TLD bruteForcing *******/
    if(ui->radioButton_tldBrute->isChecked())
    {
        m_scanArguments->tldBrute = true;
        m_scanArguments->subBrute = false;

        if(ui->comboBox_target->currentIndex() == SINGLE_TARGET)
        {
            m_scanArguments->targetList.append(TargetNameFilter(ui->lineEdit_target->text(), ENGINE::TLDBRUTE));
            ///
            /// for a single target, progress equals to the total number of wordlist...
            ///
            ui->progressBar->setMaximum(ui->listWidget_wordlist->count());
        }
        if(ui->comboBox_target->currentIndex() == MULTIPLE_TARGETS)
        {
            for(int i = 0; i < ui->listWidget_targets->count(); i++)
            {
                m_scanArguments->targetList.append(TargetNameFilter(ui->listWidget_targets->item(i)->text(), ENGINE::TLDBRUTE));
            }
            ///
            /// for multiple targets, progress equals to the total number of wordlist times the total number of targets...
            ///
            ui->progressBar->setMaximum(ui->listWidget_wordlist->count()*m_scanArguments->targetList.count());
        }
    }
    ///
    /// Starting the scan...
    ///
    startScan();
    //...
    sendStatus("[START] Started Subdomain Enumeration!");
    logs("[START] Started Subdomain Enumeration!");
}
void Brute::on_lineEdit_target_returnPressed(){
    on_pushButton_start_clicked();
}

/************************************* Pause/Stop Enumeration *************************************/
void Brute::on_pushButton_pause_clicked(){
    ///
    /// if the scan was already paused, then this current click is to
    /// Resume the scan, just call the startScan, with the same arguments and
    /// it will continue at where it ended...
    ///
    if(m_scanStatus->isPaused){
        ui->pushButton_pause->setText("Pause");
        m_scanStatus->isPaused = false;
        //...
        startScan();
        //...
        sendStatus("[START] Resumed Subdomain Enumeration!");
        logs("[START] Resumed Subdomain Enumeration!");
    }
    else
    {
        m_scanStatus->isPaused = true;
        emit stop();
    }
}

void Brute::on_pushButton_stop_clicked(){
    emit stop();
    m_scanStatus->isStopped = true;
}

/************************************ Enumeration Method *********************************/

void Brute::startScan(){
    ///
    /// if the numner of threads is greater than the number of wordlists, set the
    /// number of threads to use to the number of wordlists available to avoid
    /// creating more threads than needed...
    ///
    int wordlistCount = ui->listWidget_wordlist->count();
    int threadsCount = m_scanConfig->threadsCount;
    if(threadsCount > wordlistCount)
    {
        threadsCount = wordlistCount;
    }
    m_activeThreads = threadsCount;
    ///
    /// loop to create threads for scan...
    ///
    for(int i = 0; i < threadsCount; i++)
    {
        QThread *cThread = new QThread;
        BruteEnumerator *Enumerator = new BruteEnumerator(m_scanConfig, m_scanArguments);
        Enumerator->enumerate(cThread);
        Enumerator->moveToThread(cThread);
        //...
        connect(Enumerator, SIGNAL(scanResult(QString, QString)), this, SLOT(scanResult(QString, QString)));
        connect(Enumerator, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));
        connect(Enumerator, SIGNAL(scanLog(QString)), this, SLOT(logs(QString)));
        connect(cThread, SIGNAL(finished()), this, SLOT(scanThreadEnded()));
        connect(cThread, SIGNAL(finished()), Enumerator, SLOT(deleteLater()));
        connect(cThread, SIGNAL(finished()), cThread, SLOT(deleteLater()));
        connect(this, SIGNAL(stop()), Enumerator, SLOT(onStop()));
        //...
        cThread->start();
    }
    m_scanStatus->isRunning = true;
}

/************************************ Receiving Results ***********************************/
void Brute::scanResult(QString subdomain, QString ipAddress){
    m_resultsModel->brute->setItem(m_resultsModel->brute->rowCount(), 0, new QStandardItem(subdomain));
    m_resultsModel->brute->setItem(m_resultsModel->brute->rowCount()-1, 1, new QStandardItem(ipAddress));
    ui->label_resultsCount->setNum(m_resultsModel->brute->rowCount());
}

/********************************* Enumeration thread ended ********************************/
void Brute::scanThreadEnded(){
    m_activeThreads--;
    ///
    /// if all Scan Threads have finished...
    ///
    if(m_activeThreads == 0)
    {
        if(m_scanStatus->isPaused)
        {
            ui->pushButton_pause->setText("Resume");
            m_scanStatus->isRunning = false;
            //...
            sendStatus("[*] Scan Paused!");
            logs("[*] Scan Paused!\n");
            return;
        }
        else
        {
            m_scanArguments->targetList.clear();
            m_scanStatus->isPaused = false;
            m_scanStatus->isStopped = false;
            m_scanStatus->isRunning = false;
            //...
            ui->pushButton_start->setEnabled(true);
            ui->pushButton_pause->setDisabled(true);
            ui->pushButton_stop->setDisabled(true);
            //...
            sendStatus("[*] Enumeration Complete!");
            logs("[END] Enumeration Complete!\n");
        }
    }
}

/********************* Change Btn Subdomain & TLD Enumerations ****************************/
void Brute::on_radioButton_tldBrute_clicked(){
    ui->label_mainTitle->setText("(TLD)Top Level Domain(example.*) Enumeration By BruteForcing...");
}

void Brute::on_radioButton_subBrute_clicked(){
    ui->label_mainTitle->setText("Subdomain(*.example.com) Enumeration By BruteForcing...");
}

/******************************** Scan Config Dialog ***************************************/
void Brute::on_toolButton_config_clicked(){
    ConfigDialog *scanConfig = new ConfigDialog(this, m_scanConfig);
    scanConfig->setAttribute( Qt::WA_DeleteOnClose, true );
    scanConfig->show();
}

void Brute::on_comboBox_target_currentIndexChanged(int index){
    // index == 1 (Multiple-targets)..
    if(index){
        ui->frame_targets->show();
    }
    // index == 0 (Single targets)..
    else{
        ui->frame_targets->hide();
    }
}

/**************************** Clear the Enumerated Subdomains *****************************/
void Brute::on_pushButton_clearResults_clicked(){
    ///
    /// if the current tab is subdomains clear subdomains...
    ///
    if(ui->tabWidget_results->currentIndex() == 0)
    {
        m_resultsModel->brute->clear();
        ui->label_resultsCount->clear();
        //...
        ui->progressBar->reset();
        ui->progressBar->hide();
        //...
        m_resultsModel->brute->setHorizontalHeaderLabels({"Subdomain Name", "IpAddress"});
    }
    ///
    /// if the current tab is logs clear logs...
    ///
    else
    {
        ui->listWidget_logs->clear();
    }
}

/*****************************************************************************************
                            Multiple Targets
*****************************************************************************************/
void Brute::on_pushButton_removeTargets_clicked(){
    int selectionCount = ui->listWidget_targets->selectedItems().count();
    if(selectionCount){
        qDeleteAll(ui->listWidget_targets->selectedItems());
    }
    ui->label_targetsCount->setNum(ui->listWidget_targets->count());
}

void Brute::on_pushButton_clearTargets_clicked(){
    ui->listWidget_targets->clear();
    ui->label_targetsCount->clear();
}

void Brute::on_pushButton_loadTargets_clicked(){
    QString filename = QFileDialog::getOpenFileName(this, INFO_LOADFILE, CURRENT_PATH);
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            ui->listWidget_targets->addItem(in.readLine());
        }
        ui->label_targetsCount->setNum(ui->listWidget_targets->count());
        file.close();
    }else{
        QMessageBox::warning(this, TITLE_ERROR, "Failed To Open the File!");
    }
}

void Brute::on_pushButton_addTargets_clicked(){
    if(ui->lineEdit_multipleTargets->text() != EMPTY){
        ui->listWidget_targets->addItem(ui->lineEdit_multipleTargets->text());
        ui->lineEdit_multipleTargets->clear();
        ui->label_targetsCount->setNum(ui->listWidget_targets->count());
    }
}

void Brute::on_lineEdit_multipleTargets_returnPressed(){
 on_pushButton_addTargets_clicked();
}

/******************************************************************************************
                                Wordlists
*******************************************************************************************/

/******************************* Generate Wordlist (Dialog) ******************************/
void Brute::on_pushButton_generateWordlist_clicked(){
    WordListGeneratorDialog *wordlistgenerator = new WordListGeneratorDialog(this);
    wordlistgenerator->setAttribute( Qt::WA_DeleteOnClose, true );
    wordlistgenerator->show();
}

/**************************** Choose Wordlist To Use (Dialog) ****************************/
void Brute::on_toolButton_wordlist_clicked(){
    WordListDialog *wordlistDialog;
    if(ui->radioButton_subBrute->isChecked()){
        wordlistDialog = new WordListDialog(this, ENGINE::SUBBRUTE);
    }
    if(ui->radioButton_tldBrute->isChecked()){
        wordlistDialog = new WordListDialog(this, ENGINE::TLDBRUTE);
    }
    wordlistDialog->setAttribute( Qt::WA_DeleteOnClose, true );
    //...
    connect(wordlistDialog, SIGNAL(choosenWordlist(QString)), this, SLOT(choosenWordlist(QString)));
    wordlistDialog->show();
}

/********************* Receiving the Wordlist that the user choose ***************************/
void Brute::choosenWordlist(QString wordlistFilename){
    QFile file(wordlistFilename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            ui->listWidget_wordlist->addItem(in.readLine());
        }
        file.close();
    }
    ui->label_wordlistCount->setNum(ui->listWidget_wordlist->count());
}

/************************************ Loading Wordlist ***********************************/
void Brute::on_pushButton_loadWordlist_clicked(){
    QString filename = QFileDialog::getOpenFileName(this, INFO_LOADFILE, CURRENT_PATH);
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            ui->listWidget_wordlist->addItem(in.readLine());
        }
        ui->label_wordlistCount->setNum(ui->listWidget_wordlist->count());
        file.close();
    }else{
        QMessageBox::warning(this, TITLE_ERROR, "Failed To Open the File!");
    }
}

/******************************** Add Item on the Wordlist *********************************/
void Brute::on_pushButton_addWordlist_clicked(){
    if(ui->lineEdit_wordlist->text() != EMPTY){
        ui->listWidget_wordlist->addItem(ui->lineEdit_wordlist->text());
        ui->lineEdit_wordlist->clear();
        ui->label_wordlistCount->setNum(ui->listWidget_wordlist->count());
    }
}
void Brute::on_lineEdit_wordlist_returnPressed(){
    on_pushButton_addWordlist_clicked();
}

/******************************** Clear The Wordlist **************************************/
void Brute::on_pushButton_clearWordlist_clicked(){
    ui->listWidget_wordlist->clear();
    ui->label_wordlistCount->clear();
}

/***************************** Removing Item From Wordlist *********************************/
void Brute::on_pushButton_removeWordlist_clicked(){
    int selectionCount = ui->listWidget_wordlist->selectedItems().count();
    if(selectionCount){
        qDeleteAll(ui->listWidget_wordlist->selectedItems());
    }
    ui->label_wordlistCount->setNum(ui->listWidget_wordlist->count());
}

/****************************** Save And Display logs *********************************/
void Brute::logs(QString log){
    sendLog(log);
    ui->listWidget_logs->addItem(log);
    if (log.startsWith("[ERROR]")){
        ui->listWidget_logs->item(ui->listWidget_logs->count()-1)->setForeground(Qt::red);
        return;
    }
    if(log.startsWith("[START]") || log.startsWith("[END]")){
        ui->listWidget_logs->item(ui->listWidget_logs->count()-1)->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
        return;
    }
}


/***************************************************************************************
                                    Context Menus
****************************************************************************************/

void Brute::on_pushButton_action_clicked(){
    ///
    /// getting the position of the action button to place the context menu and
    /// showing the context menu right by the side of the action button...
    ///
    QPoint pos = ui->pushButton_action->mapToGlobal(QPoint(0,0));
    //...
    QMenu *contextMenu_actionButton = new QMenu(this);
    contextMenu_actionButton->setAttribute( Qt::WA_DeleteOnClose, true );
    contextMenu_actionButton->setObjectName("actionButtonMenu");
    //...
    QAction actionSendToIp("Send IpAddresses To Ip");
    QAction actionSendToActive("Send Subdomains To Active");
    QAction actionSendToBrute("Send Subdomains To Brute");
    QAction actionSendToSave("Send Subdomains To Save");
    QAction actionSendToLevel("Send Subdomains To Level");
    QAction actionSendToRecords("Send Subdomains To Records");
    //...
    connect(&actionSendToIp, SIGNAL(triggered()), this, SLOT(actionSendToIp(ENGINE::BRUTE)));
    connect(&actionSendToSave, SIGNAL(triggered()), this, SLOT(actionSendToSave(ENGINE::BRUTE)));
    connect(&actionSendToBrute, SIGNAL(triggered()), this, SLOT(actionSendToBrute(ENGINE::BRUTE)));
    connect(&actionSendToActive, SIGNAL(triggered()), this, SLOT([=](){actionSendToActive(ENGINE::BRUTE)}));
    connect(&actionSendToRecords, SIGNAL(triggered()), this, SLOT(actionSendToRecords(ENGINE::BRUTE)));
    connect(&actionSendToLevel, SIGNAL(triggered()), this, SLOT(actionSendToLevel(ENGINE::BRUTE)));
    //...
    contextMenu_actionButton->addAction(&actionSendToIp);
    contextMenu_actionButton->addAction(&actionSendToBrute);
    contextMenu_actionButton->addAction(&actionSendToActive);
    contextMenu_actionButton->addAction(&actionSendToRecords);
    contextMenu_actionButton->addAction(&actionSendToLevel);
    contextMenu_actionButton->addAction(&actionSendToSave);
    //...
    contextMenu_actionButton->move(QPoint(pos.x()+76, pos.y()));
    contextMenu_actionButton->exec();;
}

void Brute::on_tableView_results_customContextMenuRequested(const QPoint &pos){
    Q_UNUSED(pos);
    ///
    /// check if user right clicked on items else dont show the context menu...
    ///
    if(!ui->tableView_results->selectionModel()->isSelected(ui->tableView_results->currentIndex())){
        return;
    }
    ///
    /// getting the position of the cursor to place the context menu...
    ///
    QPoint globalCursorPos = QCursor::pos();
    QRect mouseScreenGeometry = qApp->desktop()->screen(qApp->desktop()->screenNumber(globalCursorPos))->geometry();
    QPoint localCursorPosition = globalCursorPos - mouseScreenGeometry.topLeft();
    //...
    QMenu *contextMenu_rightClick = new QMenu(this);
    contextMenu_rightClick->setAttribute( Qt::WA_DeleteOnClose, true );
    contextMenu_rightClick->setObjectName("rightClickMenu");
    //...
    QAction actionSendToSave("Send Selected To Save", this);
    QAction actionSendToRecords("Send Selected To Records");
    QAction actionOpenInBrowser("Open Selected in Browser");
    //...
    connect(&actionOpenInBrowser, SIGNAL(triggered()), this, SLOT(cursorOpenInBrowser()));
    connect(&actionSendToSave, SIGNAL(triggered()), this, SLOT(cursorSendToSave()));
    connect(&actionSendToRecords, SIGNAL(triggered()), this, SLOT(cursorSendToRecords()));
    //...
    contextMenu_rightClick->addAction(&actionOpenInBrowser);
    contextMenu_rightClick->addSeparator();
    contextMenu_rightClick->addAction(&actionSendToRecords);
    contextMenu_rightClick->addAction(&actionSendToSave);
    //...
    contextMenu_rightClick->move(localCursorPosition);
    contextMenu_rightClick->exec();
}

/********************************* Other Actions *****************************/
void Brute::cursorOpenInBrowser(){
    // iterate and open each selected item in a browser...
    foreach(const QModelIndex &index, ui->tableView_results->selectionModel()->selectedIndexes()){
        QDesktopServices::openUrl(QUrl("https://"+index.data().toString(), QUrl::TolerantMode));
    }
}

/*
 Copyright 2020-2022 Enock Nicholaus <3nock@protonmail.com>. All rights reserved.
 Use of this source code is governed by GPL-3.0 LICENSE that can be found in the LICENSE file.

 @brief :
*/

#ifndef ACTIVECONFIGDIALOG_H
#define ACTIVECONFIGDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "src/modules/active/BruteScanner.h"
#include "src/modules/active/HostScanner.h"
#include "src/modules/active/DNSScanner.h"
#include "src/modules/active/SSLScanner.h"
#include "src/modules/active/URLScanner.h"
#include "src/modules/active/IPScanner.h"


namespace Ui {
class ActiveConfigDialog;
}

class ActiveConfigDialog : public QDialog{
        Q_OBJECT

    public:
        ActiveConfigDialog(QWidget *parent = nullptr, brute::ScanConfig *config = nullptr);
        ActiveConfigDialog(QWidget *parent = nullptr, host::ScanConfig *config = nullptr);
        ActiveConfigDialog(QWidget *parent = nullptr, dns::ScanConfig *config = nullptr);
        ActiveConfigDialog(QWidget *parent = nullptr, ssl::ScanConfig *config = nullptr);
        ActiveConfigDialog(QWidget *parent = nullptr, url::ScanConfig *config = nullptr);
        ActiveConfigDialog(QWidget *parent = nullptr, ip::ScanConfig *config = nullptr);
        ~ActiveConfigDialog();

    private slots:
        void on_buttonCancel_clicked();
        void on_buttonOk_clicked();

    private:
        Ui::ActiveConfigDialog *ui;

        bool brute = false;
        bool host = false;
        bool dns = false;
        bool ssl = false;
        bool url = false;
        bool ip = false;

        brute::ScanConfig *m_configBrute = nullptr;
        host::ScanConfig *m_configHost = nullptr;
        dns::ScanConfig *m_configDns = nullptr;
        ssl::ScanConfig *m_configSSL = nullptr;
        url::ScanConfig *m_configURL = nullptr;
        ip::ScanConfig *m_configIP = nullptr;

        QStringListModel *m_customNameserverListModel;

        void m_initWidgets();

        void m_loadConfigBrute();
        void m_loadConfigHost();
        void m_loadConfigDns();
        void m_loadConfigSSL();
        void m_loadConfigURL();
        void m_loadConfigIP();

        void m_saveBrute();
        void m_saveHost();
        void m_saveDns();
        void m_saveSSL();
        void m_saveURL();
        void m_saveIP();
};

#endif // ACTIVECONFIGDIALOG_H

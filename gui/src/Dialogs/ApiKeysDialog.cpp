#include "ApiKeysDialog.h"
#include "ui_ApiKeysDialog.h"
//...
#include "src/utils/Config.h"
#include <QUrl>
#include <QDesktopServices>

/*
 * TODO: fix hunter..
 *       add more api keys..
 *       modify such that more info can be shown eg(api calls left)
 *       save the urls in the .ini file instead of hardcoding them...
 *       also add a widget to display those url so they can be modifiable
 */

ApiKeysDialog::ApiKeysDialog(QWidget *parent): QDialog(parent),ui(new Ui::ApiKeysDialog)
{
    ui->setupUi(this);
    loadApiKeys();
}
ApiKeysDialog::~ApiKeysDialog(){
    delete ui;
}

void ApiKeysDialog::on_buttonSave_clicked(){
    Config::generalConfig().beginGroup("api-keys");
    //....
    Config::generalConfig().setValue("bing", ui->lineEditBing->text());
    Config::generalConfig().setValue("censys_id", ui->lineEditCensysId->text());
    Config::generalConfig().setValue("censys_secret", ui->lineEditCensysSecret->text());
    Config::generalConfig().setValue("certspotter", ui->lineEditCertspotter->text());
    Config::generalConfig().setValue("cloudflare", ui->lineEditCloudflare->text());
    Config::generalConfig().setValue("github", ui->lineEditGithub->text());
    Config::generalConfig().setValue("google", ui->lineEditGoogle->text());
    Config::generalConfig().setValue("hunter", ui->lineEditHunter->text());
    Config::generalConfig().setValue("huntersearch", ui->lineEditHunter->text());
    Config::generalConfig().setValue("intelx", ui->lineEditIntelX->text());
    Config::generalConfig().setValue("pentesttools", ui->lineEditPentestTools->text());
    Config::generalConfig().setValue("projectdiscovery", ui->lineEditProjectDiscovery->text());
    Config::generalConfig().setValue("riskiq_key", ui->lineEditRiskIqKey->text());
    Config::generalConfig().setValue("riskiq_username", ui->lineEditRiskIqUsername->text());
    Config::generalConfig().setValue("securitytrails", ui->lineEditSecurityTrails->text());
    Config::generalConfig().setValue("shodan", ui->lineEditShodan->text());
    Config::generalConfig().setValue("spyse", ui->lineEditSpyse->text());
    Config::generalConfig().setValue("virustotalapi", ui->lineEditVirusTotal->text());
    Config::generalConfig().setValue("binaryedge", ui->lineEditBinaryEdge->text());
    Config::generalConfig().setValue("c99", ui->lineEditC99->text());
    //...
    Config::generalConfig().endGroup();
    accept();
}

void ApiKeysDialog::on_buttonCancel_clicked(){
    accept();
}

void ApiKeysDialog::loadApiKeys(){
    QString key;
    Config::generalConfig().beginGroup("api-keys");
    ///
    /// loading the keys....
    ///
    key= Config::generalConfig().value("bing").toString();
    if(!key.isEmpty()){
        ui->lineEditBing->setText(key);
        ui->buttonGetBing->hide();
    }
    key = Config::generalConfig().value("censys_id").toString();
    if(!key.isEmpty()){
        ui->lineEditCensysId->setText(key);
        ui->buttonGetCensys->hide();
    }
    key = Config::generalConfig().value("censys_secret").toString();
    if(!key.isEmpty()){
        ui->lineEditCensysSecret->setText(key);
        ui->buttonGetCensys->hide();
    }
    key = Config::generalConfig().value("certspotter").toString();
    if(!key.isEmpty()){
        ui->lineEditCertspotter->setText(key);
        ui->buttonGetCertspotter->hide();
    }
    key = Config::generalConfig().value("cloudflare").toString();
    if(!key.isEmpty()){
        ui->lineEditCloudflare->setText(key);
        ui->buttonGetCloudflare->hide();
    }
    key = Config::generalConfig().value("github").toString();
    if(!key.isEmpty()){
        ui->lineEditGithub->setText(key);
        ui->buttonGetGithub->hide();
    }
    key = Config::generalConfig().value("google").toString();
    if(!key.isEmpty()){
        ui->lineEditGoogle->setText(key);
        ui->buttonGetGoogle->hide();
    }
    key = Config::generalConfig().value("hunter").toString();
    if(!key.isEmpty()){
        ui->lineEditHunter->setText(key);
        ui->buttonGetHunter->hide();
    }
    key = Config::generalConfig().value("huntersearch").toString();
    if(!key.isEmpty()){
        ui->lineEditHunter->setText(key);
        ui->buttonGetHunter->hide();
    }
    key = Config::generalConfig().value("intelx").toString();
    if(!key.isEmpty()){
        ui->lineEditIntelX->setText(key);
        ui->buttonGetIntelX->hide();
    }
    key = Config::generalConfig().value("pentesttools").toString();
    if(!key.isEmpty()){
        ui->lineEditPentestTools->setText(key);
        ui->buttonGetPentestTools->hide();
    }
    key = Config::generalConfig().value("projectdiscovery").toString();
    if(!key.isEmpty()){
        ui->lineEditProjectDiscovery->setText(key);
        ui->buttonGetProjectDiscovery->hide();
    }
    key = Config::generalConfig().value("riskiq_key").toString();
    if(!key.isEmpty()){
        ui->lineEditRiskIqKey->setText(key);
    }
    key = Config::generalConfig().value("riskiq_username").toString();
    if(!key.isEmpty()){
        ui->lineEditRiskIqUsername->setText(key);
        ui->buttonGetRiskIq->hide();
    }
    key = Config::generalConfig().value("securitytrails").toString();
    if(!key.isEmpty()){
        ui->lineEditSecurityTrails->setText(key);
        ui->buttonGetSecurityTrails->hide();
    }
    key = Config::generalConfig().value("shodan").toString();
    if(!key.isEmpty()){
        ui->lineEditShodan->setText(key);
        ui->buttonGetShodan->hide();
    }
    key = Config::generalConfig().value("spyse").toString();
    if(!key.isEmpty()){
        ui->lineEditSpyse->setText(key);
        ui->buttonGetSpyse->hide();
    }
    key = Config::generalConfig().value("virustotalapi").toString();
    if(!key.isEmpty()){
        ui->lineEditVirusTotal->setText(key);
        ui->buttonGetVirusTotal->hide();
    }
    key = Config::generalConfig().value("binaryedge").toString();
    if(!key.isEmpty()){
        ui->lineEditBinaryEdge->setText(key);
        ui->buttonGetBinaryEdge->hide();
    }
    key = Config::generalConfig().value("c99").toString();
    if(!key.isEmpty()){
        ui->lineEditC99->setText(key);
        ui->buttonGetC99->hide();
    }
    Config::generalConfig().endGroup();
}


void ApiKeysDialog::on_buttonGetCensys_clicked(){
    QDesktopServices::openUrl(QUrl("https://censys.io/login", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetVirusTotal_clicked(){
     QDesktopServices::openUrl(QUrl("https://www.virustotal.com/gui/join-us", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetGithub_clicked(){
    QDesktopServices::openUrl(QUrl("https://github.com/settings/tokens", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetShodan_clicked(){
    QDesktopServices::openUrl(QUrl("https://developer.shodan.io/api/requirements", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetCloudflare_clicked(){
    QDesktopServices::openUrl(QUrl("https://dash.cloudflare.com/profile/api-tokens", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetBing_clicked(){
    QDesktopServices::openUrl(QUrl("https://www.microsoft.com/en-us/bing/apis/bing-web-search-api", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetGoogle_clicked(){
    QDesktopServices::openUrl(QUrl("https://developers.google.com/maps/documentation/places/web-service/get-api-key", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetHunter_clicked(){
    QDesktopServices::openUrl(QUrl("https://hunter.io/api", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetCertspotter_clicked(){
    QDesktopServices::openUrl(QUrl("https://sslmate.com/certspotter/api/", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetIntelX_clicked(){
    QDesktopServices::openUrl(QUrl("https://intelx.io/signup", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetSecurityTrails_clicked(){
    QDesktopServices::openUrl(QUrl("https://securitytrails.com/corp/api", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetSpyse_clicked(){
    QDesktopServices::openUrl(QUrl("https://spyse.com/user/registration", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetRiskIq_clicked(){
    QDesktopServices::openUrl(QUrl("https://api.riskiq.net/api/", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetPentestTools_clicked(){
    QDesktopServices::openUrl(QUrl("https://pentest-tools.com/pricing", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetProjectDiscovery_clicked(){
    QDesktopServices::openUrl(QUrl("https://chaos.projectdiscovery.io/", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetBinaryEdge_clicked(){
    QDesktopServices::openUrl(QUrl("https://www.binaryedge.io/pricing.html", QUrl::TolerantMode));
}

void ApiKeysDialog::on_buttonGetC99_clicked(){
    QDesktopServices::openUrl(QUrl("http://api.c99.nl/dashboard/shop", QUrl::TolerantMode));
}

#include "Project.h"
#include "ui_Project.h"

#include <QDesktopServices>
#include <QFileDialog>
#include <QClipboard>


void Project::action_clear(){
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
        model->activeHost->clear();
        model->map_activeHost.clear();
        break;
    case ExplorerType::activeWildcard:
        model->activeWildcard->clear();
        model->map_activeWildcard.clear();
        break;
    case ExplorerType::activeDNS:
        model->activeDNS->clear();
        model->map_activeDNS.clear();
        break;
    case ExplorerType::activeDNS_A:
        model->activeA->clear();
        break;
    case ExplorerType::activeDNS_AAAA:
        model->activeAAAA->clear();
        break;
    case ExplorerType::activeDNS_NS:
        model->activeNS->clear();
        break;
    case ExplorerType::activeDNS_MX:
        model->activeMX->clear();
        break;
    case ExplorerType::activeDNS_TXT:
        model->activeTXT->clear();
        break;
    case ExplorerType::activeDNS_CNAME:
        model->activeCNAME->clear();
        break;
    case ExplorerType::activeSSL:
        model->activeSSL->clear();
        model->map_activeSSL.clear();
        break;
    case ExplorerType::activeSSL_sha1:
        model->activeSSL_sha1->clear();
        break;
    case ExplorerType::activeSSL_sha256:
        model->activeSSL_sha256->clear();
        break;
    case ExplorerType::activeSSL_altNames:
        model->activeSSL_altNames->clear();
        break;
    case ExplorerType::activeURL:
        model->activeURL->clear();
        model->map_activeURL.clear();
        break;
    case ExplorerType::passive_subdomainIp:
        model->passiveSubdomainIp->clear();
        break;
    case ExplorerType::passive_subdomain:
        model->passiveSubdomain->clear();
        break;
    case ExplorerType::passive_A:
        model->passiveA->clear();
        break;
    case ExplorerType::passive_AAAA:
        model->passiveAAAA->clear();
        break;
    case ExplorerType::passive_NS:
        model->passiveNS->clear();
        break;
    case ExplorerType::passive_MX:
        model->passiveMX->clear();
        break;
    case ExplorerType::passive_TXT:
        model->passiveTXT->clear();
        break;
    case ExplorerType::passive_CNAME:
        model->passiveCNAME->clear();
        break;
    case ExplorerType::passive_Email:
        model->passiveEmail->clear();
        break;
    case ExplorerType::passive_URL:
        model->passiveURL->clear();
        break;
    case ExplorerType::passive_ASN:
        model->passiveASN->clear();
        break;
    case ExplorerType::passive_SSL:
        model->passiveSSL->clear();
        break;
    case ExplorerType::enum_IP:
        model->enumIP->clear();
        model->map_enumIP.clear();
        break;
    case ExplorerType::enum_ASN:
        model->enumASN->clear();
        model->map_enumASN.clear();
        break;
    case ExplorerType::enum_CIDR:
        model->enumCIDR->clear();
        model->map_enumCIDR.clear();
        break;
    case ExplorerType::enum_NS:
        model->enumNS->clear();
        model->map_enumNS.clear();
        break;
    case ExplorerType::enum_MX:
        model->enumMX->clear();
        model->map_enumMX.clear();
        break;
    case ExplorerType::enum_Email:
        model->enumEmail->clear();
        model->map_enumEmail.clear();
        break;
    case ExplorerType::enum_SSL:
        model->enumSSL->clear();
        model->map_enumSSL.clear();
        break;
    case ExplorerType::raw:
        model->raw->clear();
        break;
    }

    model->setHeaderLabels();
    ui->labelCount->setNum(proxyModel->rowCount());
    model->modified = true;
}

void Project::action_remove_duplicates(){
    QStandardItemModel *choosen_model;
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_A:
        choosen_model = model->activeA;
        break;
    case ExplorerType::activeDNS_AAAA:
        choosen_model = model->activeAAAA;
        break;
    case ExplorerType::activeDNS_NS:
        choosen_model = model->activeNS;
        break;
    case ExplorerType::activeDNS_MX:
        choosen_model = model->activeMX;
        break;
    case ExplorerType::activeDNS_TXT:
        choosen_model = model->activeTXT;
        break;
    case ExplorerType::activeDNS_CNAME:
        choosen_model = model->activeCNAME;
        break;
    case ExplorerType::activeSSL_sha1:
        choosen_model = model->activeSSL_sha1;
        break;
    case ExplorerType::activeSSL_sha256:
        choosen_model = model->activeSSL_sha256;
        break;
    case ExplorerType::activeSSL_altNames:
        choosen_model = model->activeSSL_altNames;
        break;
    case ExplorerType::passive_subdomainIp:
        choosen_model = model->passiveSubdomainIp;
        break;
    case ExplorerType::passive_subdomain:
        choosen_model = model->passiveSubdomain;
        break;
    case ExplorerType::passive_A:
        choosen_model = model->passiveA;
        break;
    case ExplorerType::passive_AAAA:
        choosen_model = model->passiveAAAA;
        break;
    case ExplorerType::passive_NS:
        choosen_model = model->passiveNS;
        break;
    case ExplorerType::passive_MX:
        choosen_model = model->passiveMX;
        break;
    case ExplorerType::passive_TXT:
        choosen_model = model->passiveTXT;
        break;
    case ExplorerType::passive_CNAME:
        choosen_model = model->passiveCNAME;
        break;
    case ExplorerType::passive_Email:
        choosen_model = model->passiveEmail;
        break;
    case ExplorerType::passive_URL:
        choosen_model = model->passiveURL;
        break;
    case ExplorerType::passive_ASN:
        choosen_model = model->passiveASN;
        break;
    case ExplorerType::passive_SSL:
        choosen_model = model->passiveSSL;
        break;
    default:
        return;
    }

    QSet<QString> set;
    for(int i = 0; i < choosen_model->rowCount(); i++){
        if(set.contains(choosen_model->item(i,0)->text())){
            choosen_model->removeRow(i);
            i--;
        }
        else
            set.insert(choosen_model->item(i,0)->text());
    }
    ui->labelCount->setNum(proxyModel->rowCount());
    model->modified = true;
}

void Project::action_save(const RESULT_TYPE &result_type){
    if(proxyModel->rowCount() == 0){
        qWarning() << "PROJECT:  Nothing to save";
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, tr("Save To File"), "./");
    if(filename.isEmpty()){
        qWarning() << "PROJECT: Failed to getSaveFileName";
        return;
    }

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file.isOpen()){
        qWarning() << "PROJECT: Failed to open " << filename << " For saving Results";
        return;
    }

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_A:
    case ExplorerType::activeDNS_AAAA:
    case ExplorerType::activeDNS_NS:
    case ExplorerType::activeDNS_MX:
    case ExplorerType::activeDNS_TXT:
    case ExplorerType::activeDNS_CNAME:
    case ExplorerType::activeSSL_sha1:
    case ExplorerType::activeSSL_sha256:
    case ExplorerType::activeSSL_altNames:
    case ExplorerType::passive_subdomain:
    case ExplorerType::passive_A:
    case ExplorerType::passive_AAAA:
    case ExplorerType::passive_NS:
    case ExplorerType::passive_MX:
    case ExplorerType::passive_TXT:
    case ExplorerType::passive_CNAME:
    case ExplorerType::passive_Email:
    case ExplorerType::passive_URL:
    case ExplorerType::passive_ASN:
    case ExplorerType::passive_SSL:
        for(int i = 0; i != proxyModel->rowCount(); ++i)
            file.write(proxyModel->index(i, 0).data().toString().append(NEWLINE).toUtf8());
        break;

    case ExplorerType::passive_subdomainIp:
        switch (result_type) {
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ip(proxyModel->index(i, 1).data().toString());

                if(!ip.isEmpty())
                    host.append(",").append(ip);

                file.write(host.append(NEWLINE).toUtf8());
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 0).data().toString().append(NEWLINE).toUtf8());
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 1).data().toString().append(NEWLINE).toUtf8());
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeDNS_SRV:
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QString name(proxyModel->index(i, 0).data().toString());
            QString target(proxyModel->index(i, 1).data().toString());
            QString port(proxyModel->index(i, 2).data().toString());

            if(!target.isEmpty())
                name.append(",").append(target);
            if(!port.isEmpty())
                name.append(",").append(port);

            file.write(name.append(NEWLINE).toUtf8());
        }
        break;
    case ExplorerType::activeHost:
        switch (result_type) {
        case RESULT_TYPE::JSON:
        {
            QJsonArray array;
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
                s3s_item::HOST *item = static_cast<s3s_item::HOST*>(model->activeHost->itemFromIndex(model_index));
                array.append(host_to_json(item));
            }
            QJsonDocument document;
            document.setArray(array);
            file.write(document.toJson());
        }
            break;
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());
                QString port(proxyModel->index(i, 3).data().toString());

                if(!ipv4.isEmpty())
                    host.append(",").append(ipv4);
                if(!ipv6.isEmpty())
                    host.append(",").append(ipv6);
                if(!port.isEmpty())
                    host.append(",").append(port);

                file.write(host.append(NEWLINE).toUtf8());
            }
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    file.write(ipv4.append(NEWLINE).toUtf8());
                if(!ipv6.isEmpty())
                    file.write(ipv6.append(NEWLINE).toUtf8());
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 0).data().toString().append(NEWLINE).toUtf8());
            break;
        case RESULT_TYPE::IPV4:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 1).data().toString().append(NEWLINE).toUtf8());
            break;
        case RESULT_TYPE::IPV6:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 2).data().toString().append(NEWLINE).toUtf8());
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeWildcard:
        switch (result_type) {
        case RESULT_TYPE::JSON:
        {
            QJsonArray array;
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
                s3s_item::Wildcard *item = static_cast<s3s_item::Wildcard*>(model->activeWildcard->itemFromIndex(model_index));
                array.append(wildcard_to_json(item));
            }
            QJsonDocument document;
            document.setArray(array);
            file.write(document.toJson());
        }
            break;
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    host.append(",").append(ipv4);
                if(!ipv6.isEmpty())
                    host.append(",").append(ipv6);

                file.write(host.append(NEWLINE).toUtf8());
            }
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    file.write(ipv4.append(NEWLINE).toUtf8());
                if(!ipv6.isEmpty())
                    file.write(ipv6.append(NEWLINE).toUtf8());
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 0).data().toString().append(NEWLINE).toUtf8());
            break;
        case RESULT_TYPE::IPV4:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 1).data().toString().append(NEWLINE).toUtf8());
            break;
        case RESULT_TYPE::IPV6:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                file.write(proxyModel->index(i, 2).data().toString().append(NEWLINE).toUtf8());
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeDNS:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));
            array.append(dns_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::activeSSL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(model_index));
            array.append(ssl_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::activeURL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::URL *item = static_cast<s3s_item::URL*>(model->activeURL->itemFromIndex(model_index));
            array.append(url_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_IP:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::IP *item = static_cast<s3s_item::IP*>(model->activeHost->itemFromIndex(model_index));
            array.append(ip_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_ASN:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));
            array.append(asn_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_CIDR:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));
            array.append(cidr_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_NS:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(model_index));
            array.append(ns_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_MX:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(model_index));
            array.append(mx_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_Email:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::Email *item = static_cast<s3s_item::Email*>(model->enumEmail->itemFromIndex(model_index));
            array.append(email_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::enum_SSL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(model_index));
            array.append(ssl_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    case ExplorerType::raw:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::RAW *item = static_cast<s3s_item::RAW*>(model->raw->itemFromIndex(model_index));
            array.append(raw_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        file.write(document.toJson());
    }
        break;
    }

    file.close();
}

void Project::action_copy(const RESULT_TYPE &result_type){
    if(proxyModel->rowCount() == 0){
        qWarning() << "PROJECT:  Nothing to copy";
        return;
    }

    QString clipboardData;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_A:
    case ExplorerType::activeDNS_AAAA:
    case ExplorerType::activeDNS_NS:
    case ExplorerType::activeDNS_MX:
    case ExplorerType::activeDNS_TXT:
    case ExplorerType::activeDNS_CNAME:
    case ExplorerType::activeSSL_sha1:
    case ExplorerType::activeSSL_sha256:
    case ExplorerType::activeSSL_altNames:
    case ExplorerType::passive_subdomain:
    case ExplorerType::passive_A:
    case ExplorerType::passive_AAAA:
    case ExplorerType::passive_NS:
    case ExplorerType::passive_MX:
    case ExplorerType::passive_TXT:
    case ExplorerType::passive_CNAME:
    case ExplorerType::passive_Email:
    case ExplorerType::passive_URL:
    case ExplorerType::passive_ASN:
    case ExplorerType::passive_SSL:
        for(int i = 0; i != proxyModel->rowCount(); ++i)
            clipboardData.append(proxyModel->index(i, 0).data().toString().append(NEWLINE));
        break;

    case ExplorerType::passive_subdomainIp:
        switch (result_type) {
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ip(proxyModel->index(i, 1).data().toString());

                if(!ip.isEmpty())
                    host.append(",").append(ip);

                clipboardData.append(host.append(NEWLINE));
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 0).data().toString().append(NEWLINE));
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 1).data().toString().append(NEWLINE));
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeDNS_SRV:
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QString name(proxyModel->index(i, 0).data().toString());
            QString target(proxyModel->index(i, 1).data().toString());
            QString port(proxyModel->index(i, 2).data().toString());

            if(!target.isEmpty())
                name.append(",").append(target);
            if(!port.isEmpty())
                name.append(",").append(port);

            clipboardData.append(name.append(NEWLINE));
        }
        break;
    case ExplorerType::activeHost:
        switch (result_type) {
        case RESULT_TYPE::JSON:
        {
            QJsonArray array;
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
                s3s_item::HOST *item = static_cast<s3s_item::HOST*>(model->activeHost->itemFromIndex(model_index));
                array.append(host_to_json(item));
            }
            QJsonDocument document;
            document.setArray(array);
            clipboardData.append(document.toJson());
        }
            break;
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());
                QString port(proxyModel->index(i, 3).data().toString());

                if(!ipv4.isEmpty())
                    host.append(",").append(ipv4);
                if(!ipv6.isEmpty())
                    host.append(",").append(ipv6);
                if(!port.isEmpty())
                    host.append(",").append(port);

                clipboardData.append(host.append(NEWLINE));
            }
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    clipboardData.append(ipv4.append(NEWLINE));
                if(!ipv6.isEmpty())
                    clipboardData.append(ipv6.append(NEWLINE));
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 0).data().toString().append(NEWLINE));
            break;
        case RESULT_TYPE::IPV4:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 1).data().toString().append(NEWLINE));
            break;
        case RESULT_TYPE::IPV6:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 2).data().toString().append(NEWLINE));
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeWildcard:
        switch (result_type) {
        case RESULT_TYPE::JSON:
        {
            QJsonArray array;
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
                s3s_item::Wildcard *item = static_cast<s3s_item::Wildcard*>(model->activeWildcard->itemFromIndex(model_index));
                array.append(wildcard_to_json(item));
            }
            QJsonDocument document;
            document.setArray(array);
            clipboardData.append(document.toJson());
        }
            break;
        case RESULT_TYPE::CSV:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString host(proxyModel->index(i, 0).data().toString());
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    host.append(",").append(ipv4);
                if(!ipv6.isEmpty())
                    host.append(",").append(ipv6);

                clipboardData.append(host.append(NEWLINE));
            }
            break;
        case RESULT_TYPE::IP:
            for(int i = 0; i != proxyModel->rowCount(); ++i){
                QString ipv4(proxyModel->index(i, 1).data().toString());
                QString ipv6(proxyModel->index(i, 2).data().toString());

                if(!ipv4.isEmpty())
                    clipboardData.append(ipv4.append(NEWLINE));
                if(!ipv6.isEmpty())
                    clipboardData.append(ipv6.append(NEWLINE));
            }
            break;
        case RESULT_TYPE::SUBDOMAIN:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 0).data().toString().append(NEWLINE));
            break;
        case RESULT_TYPE::IPV4:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 1).data().toString().append(NEWLINE));
            break;
        case RESULT_TYPE::IPV6:
            for(int i = 0; i != proxyModel->rowCount(); ++i)
                clipboardData.append(proxyModel->index(i, 2).data().toString().append(NEWLINE));
            break;
        default:
            break;
        }
        break;
    case ExplorerType::activeDNS:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));
            array.append(dns_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::activeSSL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(model_index));
            array.append(ssl_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::activeURL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::URL *item = static_cast<s3s_item::URL*>(model->activeURL->itemFromIndex(model_index));
            array.append(url_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_IP:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::IP *item = static_cast<s3s_item::IP*>(model->activeHost->itemFromIndex(model_index));
            array.append(ip_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_ASN:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));
            array.append(asn_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_CIDR:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));
            array.append(cidr_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_NS:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(model_index));
            array.append(ns_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_MX:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(model_index));
            array.append(mx_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_Email:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::Email *item = static_cast<s3s_item::Email*>(model->enumEmail->itemFromIndex(model_index));
            array.append(email_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::enum_SSL:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(model_index));
            array.append(ssl_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    case ExplorerType::raw:
    {
        QJsonArray array;
        for(int i = 0; i != proxyModel->rowCount(); ++i){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::RAW *item = static_cast<s3s_item::RAW*>(model->raw->itemFromIndex(model_index));
            array.append(raw_to_json(item));
        }
        QJsonDocument document;
        document.setArray(array);
        clipboardData.append(document.toJson());
    }
        break;
    }

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(clipboardData.trimmed());
}

///
/// Send...
///

void Project::action_sendToEngine(const ENGINE &engine, const RESULT_TYPE &result_type){
    QSet<QString> targets;
    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        targets.insert(index.data().toString());

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(targets, result_type);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(targets, result_type);
        emit changeTabToRaw();
        break;
    case ENGINE::BRUTE:
        emit sendToBrute(targets, result_type);
        emit changeTabToBrute();
        break;
    case ENGINE::ACTIVE:
        emit sendToActive(targets, result_type);
        emit changeTabToActive();
        break;
    case ENGINE::DNS:
        emit sendToDns(targets, result_type);
        emit changeTabToDns();
        break;
    case ENGINE::SSL:
        emit sendToSsl(targets, result_type);
        emit changeTabToSSL();
        break;
    case ENGINE::URL:
        emit sendToUrl(targets, result_type);
        emit changeTabToURL();
        break;
    default:
        break;
    }
}

void Project::action_sendToEnum(const ENUMERATOR &tool, const RESULT_TYPE &result_type){
    QSet<QString> targets;
    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        targets.insert(index.data().toString());

    switch (tool) {
    case ENUMERATOR::IP:
        emit sendToIpEnum(targets, result_type);
        emit changeTabToIpEnum();
        break;
    case ENUMERATOR::ASN:
        emit sendToAsnEnum(targets, result_type);
        emit changeTabToAsnEnum();
        break;
    case ENUMERATOR::CIDR:
        emit sendToCidrEnum(targets, result_type);
        emit changeTabToCidrEnum();
        break;
    case ENUMERATOR::NS:
        emit sendToNSEnum(targets, result_type);
        emit changeTabToNSEnum();
        break;
    case ENUMERATOR::MX:
        emit sendToMXEnum(targets, result_type);
        emit changeTabToMXEnum();
        break;
    case ENUMERATOR::EMAIL:
        emit sendToEmailEnum(targets, result_type);
        emit changeTabToEmailEnum();
        break;
    case ENUMERATOR::SSL:
        emit sendToSSLEnum(targets, result_type);
        emit changeTabToSSLEnum();
        break;
    }
}

void Project::action_send_host(const ENGINE &engine){
    QSet<QString> hostnames;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
    case ExplorerType::activeDNS_NS:
    case ExplorerType::activeDNS_MX:
    case ExplorerType::activeDNS_CNAME:
    case ExplorerType::activeSSL_altNames:
    case ExplorerType::passive_subdomainIp:
    case ExplorerType::passive_subdomain:
    case ExplorerType::passive_NS:
    case ExplorerType::passive_MX:
    case ExplorerType::passive_CNAME:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            hostnames.insert(proxyModel->index(i,0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->CNAME->rowCount(); j++)
                hostnames.insert(item->CNAME->child(i, 1)->text());
            for(int j = 0; j < item->NS->rowCount(); j++)
                hostnames.insert(item->NS->child(i, 1)->text());
            for(int j = 0; j < item->MX->rowCount(); j++)
                hostnames.insert(item->MX->child(i, 1)->text());
        }
        break;
    case ExplorerType::activeSSL:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(model_index));

            for(int j = 0; j < item->subjectAltNames->rowCount(); j++)
                hostnames.insert(item->subjectAltNames->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_MX:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(model_index));

            for(int j = 0; j < item->domains->rowCount(); j++)
                hostnames.insert(item->domains->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(model_index));

            for(int j = 0; j < item->domains->rowCount(); j++)
                hostnames.insert(item->domains->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_SSL:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(model_index));

            for(int j = 0; j < item->subjectAltNames->rowCount(); j++)
                hostnames.insert(item->subjectAltNames->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToRaw();
        break;
    case ENGINE::BRUTE:
        emit sendToBrute(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToBrute();
        break;
    case ENGINE::ACTIVE:
        emit sendToActive(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToActive();
        break;
    case ENGINE::DNS:
        emit sendToDns(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToDns();
        break;
    case ENGINE::SSL:
        emit sendToSsl(hostnames, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToSSL();
        break;
    default:
        break;
    }
}

void Project::action_send_ip(const ENGINE &engine){
    QSet<QString> ip;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_A:
    case ExplorerType::activeDNS_AAAA:
    case ExplorerType::passive_A:
    case ExplorerType::passive_AAAA:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ip.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeHost:
    case ExplorerType::activeWildcard:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            ip.insert(proxyModel->index(i, 1).data().toString());
            ip.insert(proxyModel->index(i, 2).data().toString());
        }
        break;
    case ExplorerType::passive_subdomainIp:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ip.insert(proxyModel->index(i, 1).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->A->rowCount(); j++)
                ip.insert(item->A->child(i, 1)->text());
            for(int j = 0; j < item->AAAA->rowCount(); j++)
                ip.insert(item->AAAA->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(ip, RESULT_TYPE::IP);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(ip, RESULT_TYPE::IP);
        emit changeTabToRaw();
        break;
    default:
        break;
    }
}

void Project::action_send_url(const ENGINE &engine){
    QSet<QString> url;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeURL:
    case ExplorerType::passive_URL:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            url.insert(proxyModel->index(i, 0).data().toString());
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(url, RESULT_TYPE::URL);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(url, RESULT_TYPE::URL);
        emit changeTabToRaw();
        break;
    case ENGINE::URL:
        emit sendToUrl(url, RESULT_TYPE::URL);
        emit changeTabToURL();
        break;
    default:
        break;
    }
}

void Project::action_send_email(const ENGINE &engine){
    QSet<QString> emails;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_Email:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            emails.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->abuseContacts->rowCount(); j++)
                emails.insert(item->abuseContacts->child(i, 1)->text());
            for(int j = 0; j < item->emailContacts->rowCount(); j++)
                emails.insert(item->emailContacts->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));

            for(int j = 0; j < item->abuseContacts->rowCount(); j++)
                emails.insert(item->abuseContacts->child(i, 1)->text());
            for(int j = 0; j < item->emailContacts->rowCount(); j++)
                emails.insert(item->emailContacts->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(emails, RESULT_TYPE::EMAIL);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(emails, RESULT_TYPE::EMAIL);
        emit changeTabToRaw();
        break;
    default:
        break;
    }
}

void Project::action_send_asn(const ENGINE &engine){
    QSet<QString> asn;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            asn.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->peers->rowCount(); j++)
                asn.insert(item->peers->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));

            for(int j = 0; j < item->asns->rowCount(); j++)
                asn.insert(item->asns->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(asn, RESULT_TYPE::ASN);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(asn, RESULT_TYPE::ASN);
        emit changeTabToRaw();
        break;
    default:
        break;
    }
}

void Project::action_send_cidr(const ENGINE &engine){
    QSet<QString> cidr;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            cidr.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->prefixes->rowCount(); j++)
                cidr.insert(item->prefixes->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(cidr, RESULT_TYPE::CIDR);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(cidr, RESULT_TYPE::CIDR);
        emit changeTabToRaw();
        break;
    default:
        break;
    }
}

void Project::action_send_ssl(const ENGINE &engine){
    QSet<QString> ssl;
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_SSL:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ssl.insert(proxyModel->index(i, 0).data().toString());
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(ssl, RESULT_TYPE::CERT_ID);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(ssl, RESULT_TYPE::CERT_ID);
        emit changeTabToRaw();
        break;
    default:
        break;
    }
}

void Project::action_send_ns(const ENGINE &engine){
    QSet<QString> ns;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_NS:
    case ExplorerType::passive_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ns.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->NS->rowCount(); j++)
                ns.insert(item->NS->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToRaw();
        break;
    case ENGINE::BRUTE:
        emit sendToBrute(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToBrute();
        break;
    case ENGINE::ACTIVE:
        emit sendToActive(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToActive();
        break;
    case ENGINE::DNS:
        emit sendToDns(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToDns();
        break;
    case ENGINE::SSL:
        emit sendToSsl(ns, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToSSL();
        break;
    default:
        break;
    }
}

void Project::action_send_mx(const ENGINE &engine){
    QSet<QString> mx;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_MX:
    case ExplorerType::passive_MX:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            mx.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->MX->rowCount(); j++)
                mx.insert(item->MX->child(i, 1)->text());
        }
        break;
    }

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToRaw();
        break;
    case ENGINE::BRUTE:
        emit sendToBrute(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToBrute();
        break;
    case ENGINE::ACTIVE:
        emit sendToActive(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToActive();
        break;
    case ENGINE::DNS:
        emit sendToDns(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToDns();
        break;
    case ENGINE::SSL:
        emit sendToSsl(mx, RESULT_TYPE::SUBDOMAIN);
        emit changeTabToSSL();
        break;
    default:
        break;
    }
}

void Project::action_send_ip(){
    QSet<QString> ip;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_A:
    case ExplorerType::activeDNS_AAAA:
    case ExplorerType::passive_A:
    case ExplorerType::passive_AAAA:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ip.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeHost:
    case ExplorerType::activeWildcard:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            ip.insert(proxyModel->index(i, 1).data().toString());
            ip.insert(proxyModel->index(i, 2).data().toString());
        }
        break;
    case ExplorerType::passive_subdomainIp:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ip.insert(proxyModel->index(i, 1).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->A->rowCount(); j++)
                ip.insert(item->A->child(i, 1)->text());
            for(int j = 0; j < item->AAAA->rowCount(); j++)
                ip.insert(item->AAAA->child(i, 1)->text());
        }
        break;
    }

    emit sendToIpEnum(ip, RESULT_TYPE::IP);
    emit changeTabToIpEnum();
}

void Project::action_send_email(){
    QSet<QString> emails;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_Email:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            emails.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->abuseContacts->rowCount(); j++)
                emails.insert(item->abuseContacts->child(i, 1)->text());
            for(int j = 0; j < item->emailContacts->rowCount(); j++)
                emails.insert(item->emailContacts->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));

            for(int j = 0; j < item->abuseContacts->rowCount(); j++)
                emails.insert(item->abuseContacts->child(i, 1)->text());
            for(int j = 0; j < item->emailContacts->rowCount(); j++)
                emails.insert(item->emailContacts->child(i, 1)->text());
        }
        break;
    }

    emit sendToEmailEnum(emails, RESULT_TYPE::EMAIL);
    emit changeTabToEmailEnum();
}

void Project::action_send_asn(){
    QSet<QString> asn;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            asn.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_ASN:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->peers->rowCount(); j++)
                asn.insert(item->peers->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));

            for(int j = 0; j < item->asns->rowCount(); j++)
                asn.insert(item->asns->child(i, 1)->text());
        }
        break;
    }

    emit sendToAsnEnum(asn, RESULT_TYPE::ASN);
    emit changeTabToAsnEnum();
}

void Project::action_send_cidr(){
    QSet<QString> cidr;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_CIDR:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            cidr.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::enum_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));

            for(int j = 0; j < item->prefixes->rowCount(); j++)
                cidr.insert(item->prefixes->child(i, 1)->text());
        }
        break;
    }

    emit sendToCidrEnum(cidr, RESULT_TYPE::CIDR);
    emit changeTabToCidrEnum();
}

void Project::action_send_ssl(){
    QSet<QString> ssl;
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::passive_SSL:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ssl.insert(proxyModel->index(i, 0).data().toString());
        break;
    }

    emit sendToSSLEnum(ssl, RESULT_TYPE::CERT_ID);
    emit changeTabToSSLEnum();
}

void Project::action_send_ns(){
    QSet<QString> ns;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_NS:
    case ExplorerType::passive_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            ns.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->NS->rowCount(); j++)
                ns.insert(item->NS->child(i, 1)->text());
        }
        break;
    }

    emit sendToNSEnum(ns, RESULT_TYPE::NS);
    emit changeTabToNSEnum();
}

void Project::action_send_mx(){
    QSet<QString> mx;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeDNS_MX:
    case ExplorerType::passive_MX:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            mx.insert(proxyModel->index(i, 0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->MX->rowCount(); j++)
                mx.insert(item->MX->child(i, 1)->text());
        }
        break;
    }

    emit sendToMXEnum(mx, RESULT_TYPE::MX);
    emit changeTabToMXEnum();
}

void Project::action_openInBrowser(){
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeURL:
    case ExplorerType::passive_URL:
        foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
            QDesktopServices::openUrl(QUrl(index.data().toString(), QUrl::TolerantMode));
        break;
    default:
        foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
            QDesktopServices::openUrl(QUrl("https://"+index.data().toString(), QUrl::TolerantMode));
        break;
    }
}

void Project::action_save_selected(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save To File"), "./");
    if(filename.isEmpty()){
        qWarning() << "PROJECT: Failed to getSaveFileName";
        return;
    }

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file.isOpen()){
        qWarning() << "PROJECT: Failed to open " << filename << " For saving Results";
        return;
    }

    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        file.write(index.data().toString().append(NEWLINE).toUtf8());
    file.close();
}

void Project::action_copy_selected(){
    QString clipboardData;
    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        clipboardData.append(index.data().toString().append(NEWLINE));

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(clipboardData.trimmed());
}

void Project::action_send_selected_toEnum(const ENUMERATOR &tool){
    QSet<QString> targets;
    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        targets.insert(index.data().toString());

    switch (tool) {
    case ENUMERATOR::IP:
        emit sendToIpEnum(targets, RESULT_TYPE::IP);
        emit changeTabToIpEnum();
        break;
    case ENUMERATOR::ASN:
        emit sendToAsnEnum(targets, RESULT_TYPE::ASN);
        emit changeTabToAsnEnum();
        break;
    case ENUMERATOR::CIDR:
        emit sendToCidrEnum(targets, RESULT_TYPE::CIDR);
        emit changeTabToCidrEnum();
        break;
    case ENUMERATOR::NS:
        emit sendToNSEnum(targets, RESULT_TYPE::NS);
        emit changeTabToNSEnum();
        break;
    case ENUMERATOR::MX:
        emit sendToMXEnum(targets, RESULT_TYPE::MX);
        emit changeTabToMXEnum();
        break;
    case ENUMERATOR::SSL:
        emit sendToSSLEnum(targets, RESULT_TYPE::CERT_ID);
        emit changeTabToSSLEnum();
        break;
    case ENUMERATOR::EMAIL:
        emit sendToEmailEnum(targets, RESULT_TYPE::EMAIL);
        emit changeTabToEmailEnum();
        break;
    }
}

void Project::action_send_selected_toEngine(const ENGINE &engine, const RESULT_TYPE &result_type){
    QSet<QString> targets;
    foreach(const QModelIndex &index, m_selectionModel->selectedIndexes())
        targets.insert(index.data().toString());

    switch (engine) {
    case ENGINE::OSINT:
        emit sendToOsint(targets, result_type);
        emit changeTabToOsint();
        break;
    case ENGINE::RAW:
        emit sendToRaw(targets, result_type);
        emit changeTabToRaw();
        break;
    case ENGINE::BRUTE:
        emit sendToBrute(targets, result_type);
        emit changeTabToBrute();
        break;
    case ENGINE::ACTIVE:
        emit sendToActive(targets, result_type);
        emit changeTabToActive();
        break;
    case ENGINE::DNS:
        emit sendToDns(targets, result_type);
        emit changeTabToDns();
        break;
    case ENGINE::SSL:
        emit sendToSsl(targets, result_type);
        emit changeTabToSSL();
        break;
    case ENGINE::URL:
        emit sendToUrl(targets, result_type);
        emit changeTabToURL();
        break;
    default:
        break;
    }
}

void Project::action_remove_selected(){
    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            if(proxyIndex.column())
                model->map_activeHost.remove(proxyModel->index(proxyIndex.row(), 0).data().toString());
            else
                model->map_activeHost.remove(proxyIndex.data().toString());

            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeHost->removeRow(index.row());
        }
        break;
    case ExplorerType::activeWildcard:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            if(proxyIndex.column())
                model->map_activeWildcard.remove(proxyModel->index(proxyIndex.row(), 0).data().toString());
            else
                model->map_activeWildcard.remove(proxyIndex.data().toString());

            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeWildcard->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->activeDNS->invisibleRootItem()->index()){
                model->map_activeDNS.remove(proxyIndex.data().toString());
                model->activeDNS->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::activeDNS_A:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeA->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS_AAAA:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeAAAA->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS_NS:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeNS->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS_MX:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeHost->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS_TXT:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeTXT->removeRow(index.row());
        }
        break;
    case ExplorerType::activeDNS_CNAME:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeCNAME->removeRow(index.row());
        }
        break;
    case ExplorerType::activeSSL:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->activeSSL->invisibleRootItem()->index())
                model->activeSSL->removeRow(index.row());
        }
        break;
    case ExplorerType::activeSSL_sha1:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeSSL_sha1->removeRow(index.row());
        }
        break;
    case ExplorerType::activeSSL_sha256:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeSSL_sha256->removeRow(index.row());
        }
        break;
    case ExplorerType::activeSSL_altNames:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeSSL_altNames->removeRow(index.row());
        }
        break;
    case ExplorerType::activeURL:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            if(proxyIndex.column())
                model->map_activeURL.remove(proxyModel->index(proxyIndex.row(), 0).data().toString());
            else
                model->map_activeURL.remove(proxyIndex.data().toString());

            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->activeURL->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_subdomainIp:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveSubdomainIp->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_subdomain:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveSubdomain->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_A:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveA->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_AAAA:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveAAAA->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_NS:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveNS->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_MX:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveMX->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_TXT:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveTXT->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_CNAME:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveCNAME->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_Email:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveEmail->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_URL:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveURL->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_ASN:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveASN->removeRow(index.row());
        }
        break;
    case ExplorerType::passive_SSL:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            model->passiveSSL->removeRow(index.row());
        }
        break;
    case ExplorerType::enum_IP:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumIP->invisibleRootItem()->index()){
                model->map_enumIP.remove(proxyIndex.data().toString());
                model->enumIP->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_ASN:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumASN->invisibleRootItem()->index()){
                model->map_enumASN.remove(proxyIndex.data().toString());
                model->enumASN->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_CIDR:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumCIDR->invisibleRootItem()->index()){
                model->map_enumCIDR.remove(proxyIndex.data().toString());
                model->enumCIDR->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_NS:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumNS->invisibleRootItem()->index()){
                model->map_enumNS.remove(proxyIndex.data().toString());
                model->enumNS->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_MX:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumMX->invisibleRootItem()->index()){
                model->map_enumMX.remove(proxyIndex.data().toString());
                model->enumMX->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_Email:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumEmail->invisibleRootItem()->index()){
                model->map_enumEmail.remove(proxyIndex.data().toString());
                model->enumEmail->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::enum_SSL:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->enumSSL->invisibleRootItem()->index()){
                model->map_enumSSL.remove(proxyIndex.data().toString());
                model->enumSSL->removeRow(index.row());
            }
        }
        break;
    case ExplorerType::raw:
        foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes()){
            QModelIndex index = proxyModel->mapToSource(proxyIndex);
            if(index.parent() == model->raw->invisibleRootItem()->index())
                model->raw->removeRow(index.row());
        }
        break;
    }

    ui->labelCount->setNum(proxyModel->rowCount());
    model->modified = true;
}

void Project::action_extract(bool subdomain, bool tld, bool url){
    QSet<QString> items;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
    case ExplorerType::activeURL:
    case ExplorerType::activeDNS_NS:
    case ExplorerType::activeDNS_MX:
    case ExplorerType::activeDNS_CNAME:
    case ExplorerType::activeSSL_altNames:
    case ExplorerType::passive_subdomainIp:
    case ExplorerType::passive_subdomain:
    case ExplorerType::passive_NS:
    case ExplorerType::passive_MX:
    case ExplorerType::passive_CNAME:
    case ExplorerType::passive_URL:
        for(int i = 0; i < proxyModel->rowCount(); i++)
            items.insert(proxyModel->index(i,0).data().toString());
        break;
    case ExplorerType::activeDNS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));

            for(int j = 0; j < item->CNAME->rowCount(); j++)
                items.insert(item->CNAME->child(i, 1)->text());
            for(int j = 0; j < item->NS->rowCount(); j++)
                items.insert(item->NS->child(i, 1)->text());
            for(int j = 0; j < item->MX->rowCount(); j++)
                items.insert(item->MX->child(i, 1)->text());
        }
        break;
    case ExplorerType::activeSSL:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(model_index));

            for(int j = 0; j < item->subjectAltNames->rowCount(); j++)
                items.insert(item->subjectAltNames->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_MX:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(model_index));

            for(int j = 0; j < item->domains->rowCount(); j++)
                items.insert(item->domains->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_NS:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(model_index));

            for(int j = 0; j < item->domains->rowCount(); j++)
                items.insert(item->domains->child(i, 1)->text());
        }
        break;
    case ExplorerType::enum_SSL:
        for(int i = 0; i < proxyModel->rowCount(); i++){
            QModelIndex model_index = proxyModel->mapToSource(proxyModel->index(i, 0));
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(model_index));

            for(int j = 0; j < item->subjectAltNames->rowCount(); j++)
                items.insert(item->subjectAltNames->child(i, 1)->text());
        }
        break;
    }

    /* extracting and saving to a set to avoid repeatition */
    QSet<QString> extracts;
    foreach(const QString &item, items){
        if(subdomain)
            extracts.insert(item.split(".").at(0));
        if(tld)
            extracts.insert(item.split(".").last());
        if(url){
            QString _url = item;
            extracts.insert(_url.remove("https://").remove("http://").split("/").at(0));
        }
    }

    /* setting the data to clipboard */
    QString data;
    foreach(const QString &extract, extracts)
        data.append(extract).append(NEWLINE);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(data.trimmed());
}

void Project::action_extract_selected(bool subdomain, bool tld, bool url){
    QSet<QString> items;
    foreach(const QModelIndex &proxyIndex, m_selectionModel->selectedIndexes())
        items.insert(proxyIndex.data().toString());

    /* extracting and saving to a set to avoid repeatition */
    QSet<QString> extracts;
    foreach(const QString &item, items){
        if(subdomain)
            extracts.insert(item.split(".").at(0));
        if(tld)
            extracts.insert(item.split(".").last());
        if(url){
            QString _url = item;
            extracts.insert(_url.remove("https://").remove("http://").split("/").at(0));
        }
    }

    /* setting the data to clipboard */
    QString data;
    foreach(const QString &extract, extracts)
        data.append(extract).append(NEWLINE);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(data.trimmed());
}

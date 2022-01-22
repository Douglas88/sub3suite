#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include "src/models/ProjectModel.h"


namespace Ui {
class Project;
}

class Project : public QWidget{
        Q_OBJECT

    public:
        Project(QWidget *parent = nullptr, ProjectModel *projectModel = nullptr);
        ~Project();

        void initProject(QString projectFile);

    private slots:
        void on_treeViewProjectExplorer_clicked(const QModelIndex &index);

        void on_lineEditFilter_textChanged(const QString &arg1);

private:
        Ui::Project *ui;
        QString m_projectFile;
        ProjectModel *m_projectModel;
        QSortFilterProxyModel *m_proxyModel;

        void m_initUI();
        void m_openProject();
        void m_saveProject();
        void m_closeProject();
        void m_setupProjetct();
};

#endif // S3SPROJECT_H

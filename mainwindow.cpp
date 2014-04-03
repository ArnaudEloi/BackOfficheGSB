#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent,QString loginIn) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    login=loginIn;
    ui->setupUi(this);
    this->showMaximized();

    QSqlQuery res("select nom, prenom from userBackOffice where login=\""+login+"\";");
    res.first();
    ui->labelBienvenue->setText("Bienvenue "+res.value(1).toString()+" "+res.value(0).toString());

    /// PRATICIEN >>>
    this->ui->comboBoxPraticienType->addItem("choix du praticien ...",-1);
    this->ui->comboBoxPraticienTypeFiltre->addItem("choix du praticien ...",-1);
    this->chargerComboBoxTypePraticien();
    this->on_pushButtonPraticienNouveau_clicked();
    ui->pushButtonPraticientAjout->setEnabled(false);
    ui->pushButtonPraticientModifier->setEnabled(false);
    ui->pushButtonPraticientSupprimer->setEnabled(false);
    ui->labelPraticieInfos->setText("");
    ui->lineEditPraticientCoeff->setValidator(new QDoubleValidator(this));

    /// MEDICAMENT >>>
    this->on_pushButtonMedocNouveau_clicked();
    this->ui->comboBoxMedocFamille->addItem("choix de la famille ...",-1);
    this->ui->comboBoxMedocFamilleFiltre->addItem("choix de la famille ...",-1);
    this->chargerComboBoxFamilleMedoc();
    ui->lineEditMedocPrix->setValidator(new QDoubleValidator(this));

    /// VISITEUR >>>
    this->ui->comboBoxVisiteurSecteur->addItem("choix du secteur ...",-1);
    this->ui->comboBoxVisiteurSecteurFiltre->addItem("choix du secteur ...",-1);
    this->ui->comboBoxVisiteurLabo->addItem("choix du laboratoire ...",-1);
    this->chargerComboBoxSecteurVisiteur();
    this->chargerComboBoxLaboVisiteur();
    this->on_pushButtonVisiteurNouveau_clicked();
    ui->dateEditVisiteurDateEmbauche->setCalendarPopup(true);
    ui->dateEditVisiteurDateEmbauche->setDisplayFormat("dd/MM/yyyy");
    ui->labelVisiteurInfos->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/// MENU >>>
void MainWindow::on_pushButtonVisiteurs_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButtonPraticiens_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonMedoc_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButtonQuitter_clicked()
{

            this->close();

}

void MainWindow::closeEvent(QCloseEvent * event)
{
    int confirm = QMessageBox::critical(this, "Confirmation", "Voulez vous vraiment quitter ?", QMessageBox::Yes | QMessageBox::No);

        if(confirm == QMessageBox::Yes)
        {
            // Fermer le programme
            event->accept();
        }
        else
        {
            event->ignore();
        }
}


/// PRATICIEN >>>
void MainWindow::chargerListePraticiens()
{
    ui->listWidgetPraticiens->clear();
        vecteurPraticien.clear();
        QSqlQuery req("select PRA_CODE, PRA_NOM, PRA_PRENOM from praticien natural join type_praticien where TYP_LIBELLE like \"%"+ui->comboBoxPraticienTypeFiltre->currentText()+"%\" and (PRA_NOM like \"%"+ui->lineEditPraticienFiltre->text()+"%\" or PRA_PRENOM like \"%"+ui->lineEditPraticienFiltre->text()+"%\") order by PRA_NOM;");
        int i=0;
        while(req.next())
        {
            QListWidgetItem* newItem= new QListWidgetItem(req.value(1).toString()+" "+req.value(2).toString());
            QLinearGradient degrad;
            degrad.setStart(0,ui->listWidgetPraticiens->y());
            degrad.setFinalStop(ui->listWidgetPraticiens->width(),ui->listWidgetPraticiens->y());
            if(i%2==0)
            {
                degrad.setColorAt(0,QColor(170, 204, 255));
                degrad.setColorAt(1,Qt::white);
            }
            else
            {
                degrad.setColorAt(0,QColor(210, 244, 255));
                degrad.setColorAt(1,Qt::white);
            }
            i++;

            QBrush mabrush(degrad);
            newItem->setBackground(mabrush);

            ui->listWidgetPraticiens->addItem(newItem);
            vecteurPraticien.push_back(req.value(0).toInt());
        }
}

void MainWindow::chargerComboBoxTypePraticien()
{
    vecteurTypePraticien.clear();
    QSqlQuery req("select TYP_CODE, TYP_LIBELLE, TYP_LIEU from type_praticien");
    while(req.next())
    {
        ui->comboBoxPraticienType->addItem(req.value(1).toString());
        ui->comboBoxPraticienTypeFiltre->addItem(req.value(1).toString());
        vecteurTypePraticien.push_back(req.value(1).toString());
    }
}

void MainWindow::on_lineEditPraticienFiltre_textEdited(QString )
{
    this->chargerListePraticiens();
}

void MainWindow::on_pushButtonPraticientAjout_clicked()
{
    if(ui->lineEditPraticientNom->text()!="" && ui->lineEditPraticientPrenom->text()!="" && ui->lineEditPraticientCoeff->text()!="" && ui->comboBoxPraticienType->currentIndex()!=0)
    {
        QSqlQuery reqNew("select max(PRA_CODE) from praticien");
        reqNew.first();
        ui->lineEditPraticientCode->setText(QString::number(reqNew.value(0).toInt()+1));

        //réccupération du TYP_CODE
        QSqlQuery res("select TYP_CODE from type_praticien where TYP_LIBELLE=\""+ui->comboBoxPraticienType->currentText()+"\";");
        res.first();
        QSqlQuery req("insert into praticien values("+ui->lineEditPraticientCode->text()+",\""+ui->lineEditPraticientNom->text()+"\",\""+ui->lineEditPraticientPrenom->text()+"\",\""+ui->lineEditPraticientAdresse->text()+"\",\""+ui->lineEditPraticientCP->text()+"\",\""+ui->lineEditPraticientVille->text()+"\","+ui->lineEditPraticientCoeff->text()+",\""+res.value(0).toString()+"\");");
        req.exec();
        //recharger la liste
        this->chargerListePraticiens();
        ui->pushButtonPraticientAjout->setEnabled(false);
        ui->pushButtonPraticientModifier->setEnabled(false);
        ui->pushButtonPraticientSupprimer->setEnabled(true);
        ui->labelPraticieInfos->setText("Praticien ajouté");
    }
    else
    {
        ui->labelPraticieInfos->setText("* champs obligatoire");
    }
}

void MainWindow::on_listWidgetPraticiens_clicked(QModelIndex index)
{
    int codePraticien=vecteurPraticien.at(ui->listWidgetPraticiens->currentRow());

    QSqlQuery req("select PRA_CODE, PRA_NOM, PRA_PRENOM, PRA_ADRESSE, PRA_CP, PRA_VILLE, PRA_COEFNOTORIETE, TYP_LIBELLE from praticien natural join type_praticien where PRA_CODE="+QString::number(codePraticien)+";");
    req.first();
    ui->lineEditPraticientCode->setText(req.value(0).toString());
    ui->lineEditPraticientNom->setText(req.value(1).toString());
    ui->lineEditPraticientPrenom->setText(req.value(2).toString());
    ui->lineEditPraticientAdresse->setText(req.value(3).toString());
    ui->lineEditPraticientCP->setText(req.value(4).toString());
    ui->lineEditPraticientVille->setText(req.value(5).toString());
    ui->lineEditPraticientCoeff->setText(req.value(6).toString());
    ui->comboBoxPraticienType->setCurrentIndex(vecteurTypePraticien.lastIndexOf(req.value(7).toString())+1);

    ui->pushButtonPraticientModifier->setEnabled(false);
    ui->pushButtonPraticientSupprimer->setEnabled(true);
    //ui->pushButtonPraticienCopier->setEnabled(true);
    ui->pushButtonPraticientAjout->setEnabled(false);
    ui->labelPraticieInfos->setText("");
}

void MainWindow::on_pushButtonPraticienNouveau_clicked()
{
    QSqlQuery req("select max(PRA_CODE) from praticien");
    req.first();
    ui->lineEditPraticientCode->setText(QString::number(req.value(0).toInt()+1));
    ui->lineEditPraticientNom->clear();
    ui->lineEditPraticientPrenom->clear();
    ui->lineEditPraticientAdresse->clear();
    ui->lineEditPraticientCP->clear();
    ui->lineEditPraticientVille->clear();
    ui->lineEditPraticientCoeff->clear();
    ui->comboBoxPraticienType->setCurrentIndex(0);
    ui->lineEditPraticienFiltre->clear();
    this->chargerListePraticiens();
    ui->labelPraticieInfos->setText("");
    ui->pushButtonPraticientAjout->setEnabled(true);
    ui->pushButtonPraticientSupprimer->setEnabled(false);
}

void MainWindow::on_pushButtonPraticientSupprimer_clicked()
{
    //confirmation ?

    QSqlQuery req("delete from praticien where PRA_CODE="+ui->lineEditPraticientCode->text()+";");
    this->chargerListePraticiens();
    // on permet à l\"utilisateur de recréer le praticien en conservant ses données dans les champs de saisi (en cas de fausse manip par exemple)
    ui->pushButtonPraticientAjout->setEnabled(true);
    ui->pushButtonPraticientModifier->setEnabled(false);
    ui->pushButtonPraticientSupprimer->setEnabled(false);
    //ui->pushButtonPraticienCopier->setEnabled(false);
    ui->labelPraticieInfos->setText("Praticien supprimé");
}

void MainWindow::on_pushButtonPraticientModifier_clicked()
{
    if(ui->lineEditPraticientNom->text()!="" && ui->lineEditPraticientPrenom->text()!="" && ui->lineEditPraticientCoeff->text()!="" && ui->comboBoxPraticienType->currentIndex()!=0)
    {
        //réccupération du TYP_CODE
        QSqlQuery res("select TYP_CODE from type_praticien where TYP_LIBELLE=\""+ui->comboBoxPraticienType->currentText()+"\";");
        res.first();

        QSqlQuery req("update praticien set PRA_NOM=\""+ui->lineEditPraticientNom->text()+"\", PRA_PRENOM=\""+ui->lineEditPraticientPrenom->text()+"\", PRA_ADRESSE=\""+ui->lineEditPraticientAdresse->text()+"\", PRA_CP=\""+ui->lineEditPraticientCP->text()+"\", PRA_VILLE=\""+ui->lineEditPraticientVille->text()+"\", PRA_COEFNOTORIETE="+ui->lineEditPraticientCoeff->text()+", TYP_CODE=\""+res.value(0).toString()+"\" where PRA_CODE="+ui->lineEditPraticientCode->text()+";");
        req.exec();

        ui->labelPraticieInfos->setText("Modification éffectuée");
    }
    else
    {
        ui->labelPraticieInfos->setText("* champs obligatoire");
    }
    ui->pushButtonPraticientModifier->setEnabled(false);
    this->chargerListePraticiens();
}

/* BOUTON COPIER
void MainWindow::on_pushButtonPraticienCopier_clicked()
{
    QSqlQuery req("select max(PRA_CODE) from praticien");
    req.first();
    ui->lineEditPraticientCode->setText(QString::number(req.value(0).toInt()+1));
    this->chargerListePraticiens();
    ui->pushButtonPraticientAjout->setEnabled(true);
    ui->pushButtonPraticienCopier->setEnabled(false);
    ui->pushButtonPraticientModifier->setEnabled(false);
    ui->pushButtonPraticientSupprimer->setEnabled(false);
    ui->labelPraticieInfos->setText("Praticien copié");
}*/

void MainWindow::on_comboBoxPraticienTypeFiltre_currentIndexChanged(int index)
{
        this->chargerListePraticiens();
}

void MainWindow::modificationExistantePraticien()
{
    QSqlQuery reqCheckNew("select max(PRA_CODE) from praticien");
    reqCheckNew.first();
    if(ui->lineEditPraticientCode->text()!=QString::number(reqCheckNew.value(0).toInt()+1))
    {
        int codePraticien=ui->lineEditPraticientCode->text().toInt();
        QSqlQuery req("select PRA_NOM, PRA_PRENOM, PRA_ADRESSE, PRA_CP, PRA_VILLE, PRA_COEFNOTORIETE, TYP_LIBELLE from praticien natural join type_praticien where PRA_CODE="+QString::number(codePraticien)+";");
        req.first();
        if(ui->lineEditPraticientNom->text()!=req.value(0).toString() || ui->lineEditPraticientPrenom->text()!=req.value(1).toString() || ui->lineEditPraticientAdresse->text()!=req.value(2).toString() || ui->lineEditPraticientCP->text()!=req.value(3).toString() || ui->lineEditPraticientVille->text()!=req.value(4).toString() || ui->lineEditPraticientCoeff->text()!=req.value(5).toString() || ui->comboBoxPraticienType->currentIndex()!=vecteurTypePraticien.lastIndexOf(req.value(6).toString())+1)
        {
            ui->pushButtonPraticientModifier->setEnabled(true);
            ui->pushButtonPraticientAjout->setEnabled(true);
        }
        else
        {
            ui->pushButtonPraticientModifier->setEnabled(false);
            ui->pushButtonPraticientAjout->setEnabled(false);
        }
    }
    else
    {
        ui->pushButtonPraticientAjout->setEnabled(true); // si c'est un nouveau praticien
    }
}

void MainWindow::on_lineEditPraticientNom_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_lineEditPraticientPrenom_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_lineEditPraticientAdresse_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_lineEditPraticientCP_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_lineEditPraticientVille_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_lineEditPraticientCoeff_textEdited(QString )
{
    this->modificationExistantePraticien();
}

void MainWindow::on_comboBoxPraticienType_currentIndexChanged(int index)
{

    this->modificationExistantePraticien();
}


/// MEDICAMENT >>>
void MainWindow::chargerListeMedicaments()
{
    ui->listWidgetMedoc->clear();
        vecteurMedoc.clear();
        QSqlQuery req("select MED_DEPOTLEGAL, MED_NOMCOMMERCIAL from medicament natural join famille where MED_NOMCOMMERCIAL like \"%"+ui->lineEditMedocFiltre->text()+"%\" and FAM_LIBELLE like \"%"+ui->comboBoxMedocFamilleFiltre->currentText()+"%\" order by MED_DEPOTLEGAL;");
    int i=0;
    while(req.next())
    {
        QListWidgetItem* newItem= new QListWidgetItem(req.value(1).toString());
        QLinearGradient degrad;
        degrad.setStart(0,ui->listWidgetMedoc->y());
        degrad.setFinalStop(ui->listWidgetMedoc->width(),ui->listWidgetMedoc->y());
        if(i%2==0)
        {
            degrad.setColorAt(0,QColor(170, 204, 255));
            degrad.setColorAt(1,Qt::white);
        }
        else
        {
            degrad.setColorAt(0,QColor(210, 244, 255));
            degrad.setColorAt(1,Qt::white);
        }
        i++;

        QBrush mabrush(degrad);
        newItem->setBackground(mabrush);

        ui->listWidgetMedoc->addItem(newItem);
        vecteurMedoc.push_back(req.value(0).toString());
    }
}

void MainWindow::modificationExistanteMedoc()
{
    QSqlQuery reqCheckNew("select MED_DEPOTLEGAL, MED_NOMCOMMERCIAL from medicament");
    while(reqCheckNew.next())
    {
        if(ui->lineEditMedocDepotLegal->text()==reqCheckNew.value(0).toString())
        {
            ui->pushButtonMedocAjout->setEnabled(false);
            ui->pushButtonMedocModifier->setEnabled(true);
        }
        if(ui->lineEditMedocNom->text()==reqCheckNew.value(1).toString())
        {
            ui->pushButtonMedocAjout->setEnabled(false);
            ui->pushButtonMedocModifier->setEnabled(true);
        }
    }
    if(nouveauMedoc==false)
    {
        QSqlQuery req("select MED_DEPOTLEGAL, MED_NOMCOMMERCIAL, MED_COMPOSITION, MED_EFFETS, MED_CONTREINDIC, MED_PRIXECHANTILLON, FAM_LIBELLE from medicament natural join famille where MED_NOMCOMMERCIAL=\""+ui->listWidgetMedoc->currentItem()->text()+"\" order by medicament.FAM_CODE;");
        req.first();
        if(ui->textEditMedocComposition->toPlainText()!=req.value(2).toString() || ui->textEditMedocEffet->toPlainText()!=req.value(3).toString() || ui->textEditMedocContreIndication->toPlainText()!=req.value(4).toString() || ui->lineEditMedocPrix->text()!=req.value(5).toString() || ui->comboBoxMedocFamille->currentIndex()!=vecteurFamilleMedoc.lastIndexOf(req.value(6).toString())+1)
        {
            ui->pushButtonMedocModifier->setEnabled(true);
            ui->pushButtonMedocAjout->setEnabled(false);
        }
        else
        {
            ui->pushButtonMedocModifier->setEnabled(false);
            ui->pushButtonMedocAjout->setEnabled(false);
        }
        if(ui->lineEditMedocDepotLegal->text()!=req.value(0).toString() || ui->lineEditMedocNom->text()!=req.value(1).toString())
        {
            ui->pushButtonMedocModifier->setEnabled(false);
            ui->pushButtonMedocAjout->setEnabled(true);
        }
    }
    else // si c'est un nouveau médoc
    {
        ui->pushButtonMedocAjout->setEnabled(true);
        ui->pushButtonMedocModifier->setEnabled(false);
    }
}

void MainWindow::chargerComboBoxFamilleMedoc()
{
    vecteurFamilleMedoc.clear();
    QSqlQuery req("select FAM_CODE, FAM_LIBELLE from famille");
    while(req.next())
    {
        ui->comboBoxMedocFamille->addItem(req.value(1).toString());
        ui->comboBoxMedocFamilleFiltre->addItem(req.value(1).toString());
        vecteurFamilleMedoc.push_back(req.value(1).toString());
    }
}

void MainWindow::on_lineEditMedocFiltre_textEdited(QString )
{
    this->chargerListeMedicaments();
}

void MainWindow::on_listWidgetMedoc_clicked(QModelIndex index)
{
    nouveauMedoc=false;
    QSqlQuery req("select MED_DEPOTLEGAL, MED_NOMCOMMERCIAL, medicament.FAM_CODE, MED_COMPOSITION, MED_EFFETS, MED_CONTREINDIC, MED_PRIXECHANTILLON, FAM_LIBELLE from medicament natural join famille where MED_NOMCOMMERCIAL=\""+ui->listWidgetMedoc->currentItem()->text()+"\" order by medicament.FAM_CODE;");
    req.first();
    ui->lineEditMedocDepotLegal->setText(req.value(0).toString());
    ui->lineEditMedocNom->setText(req.value(1).toString());
    ui->textEditMedocComposition->setText(req.value(3).toString());
    ui->textEditMedocEffet->setText(req.value(4).toString());
    ui->textEditMedocContreIndication->setText(req.value(5).toString());
    ui->lineEditMedocPrix->setText(req.value(6).toString());
    ui->comboBoxMedocFamille->setCurrentIndex(vecteurFamilleMedoc.lastIndexOf(req.value(7).toString())+1);
    ui->pushButtonMedocModifier->setEnabled(false);
    ui->pushButtonMedocSupprimer->setEnabled(true);
    ui->pushButtonMedocAjout->setEnabled(false);
    ui->labelMedocInfos->setText("");
    this->modificationExistanteMedoc();
}

void MainWindow::on_comboBoxMedocFamilleFiltre_currentIndexChanged(int index)
{
    this->chargerListeMedicaments();
}

void MainWindow::on_pushButtonMedocNouveau_clicked()
{
    ui->lineEditMedocDepotLegal->clear();
    ui->lineEditMedocFiltre->clear();
    ui->lineEditMedocNom->clear();
    ui->lineEditMedocPrix->clear();
    if(ui->textEditMedocComposition->toPlainText()!="" && ui->textEditMedocEffet->toPlainText()!="" && ui->textEditMedocContreIndication->toPlainText()!="")
    {
        ui->textEditMedocComposition->clear();
        ui->textEditMedocContreIndication->clear();
        ui->textEditMedocEffet->clear();
    }
    ui->comboBoxMedocFamille->setCurrentIndex(0);

    this->chargerListeMedicaments();
    ui->labelMedocInfos->setText("");
    nouveauMedoc=true;
    ui->pushButtonMedocSupprimer->setEnabled(false);
    ui->pushButtonMedocModifier->setEnabled(false);
}

void MainWindow::on_pushButtonMedocAjout_clicked()
{
    if(ui->lineEditMedocDepotLegal->text()!="" && ui->lineEditMedocNom->text()!="" && ui->comboBoxMedocFamille->currentIndex()!=0)
    {
            //réccupération du FAM_CODE
            QSqlQuery res("select FAM_CODE from famille where FAM_LIBELLE=\""+ui->comboBoxMedocFamille->currentText()+"\";");
            res.first();

            QSqlQuery req("insert into medicament values(\""+ui->lineEditMedocDepotLegal->text()+"\",\""+ui->lineEditMedocNom->text()+"\",\""+res.value(0).toString()+"\",\""+ui->textEditMedocComposition->toPlainText()+"\",\""+ui->textEditMedocEffet->toPlainText()+"\",\""+ui->textEditMedocContreIndication->toPlainText()+"\",\""+ui->lineEditMedocPrix->text()+"\");");
            ui->pushButtonMedocAjout->setEnabled(false);
            ui->pushButtonMedocModifier->setEnabled(false);
            ui->pushButtonMedocSupprimer->setEnabled(true);
            this->chargerListeMedicaments();
            ui->labelMedocInfos->setText("Médicament ajouté");
    }
    else
    {
        ui->labelMedocInfos->setText("* champs obligatoire");
    }
}

void MainWindow::on_pushButtonMedocModifier_clicked()
{
    if(ui->lineEditMedocDepotLegal->text()!="" && ui->lineEditMedocNom->text()!="" && ui->comboBoxMedocFamille->currentIndex()!=0)
    {
        //réccupération du FAM_CODE
        QSqlQuery res("select FAM_CODE from famille where FAM_LIBELLE=\""+ui->comboBoxMedocFamille->currentText()+"\";");
        res.first();
        //réccupération du MED_DEPOTLEGAL ancien
        QSqlQuery resMedOld("select MED_DEPOTLEGAL from medicament where MED_NOMCOMMERCIAL=\""+ui->listWidgetMedoc->currentItem()->text()+"\";");
        resMedOld.first();

        QSqlQuery req("update medicament set MED_DEPOTLEGAL=\""+ui->lineEditMedocDepotLegal->text()+"\",MED_NOMCOMMERCIAL=\""+ui->lineEditMedocNom->text()+"\", FAM_CODE=\""+res.value(0).toString()+"\", MED_COMPOSITION=\""+ui->textEditMedocComposition->toPlainText()+"\", MED_EFFETS=\""+ui->textEditMedocEffet->toPlainText()+"\", MED_CONTREINDIC=\""+ui->textEditMedocContreIndication->toPlainText()+"\", MED_PRIXECHANTILLON=\""+ui->lineEditMedocPrix->text()+"\" where MED_DEPOTLEGAL=\""+resMedOld.value(0).toString()+"\";");
        req.exec();
        ui->labelMedocInfos->setText("Modification éffectuée");
    }
    else
    {
        ui->labelMedocInfos->setText("* champs obligatoire");
    }
    ui->pushButtonMedocModifier->setEnabled(false);
    this->chargerListeMedicaments();
}

void MainWindow::on_pushButtonMedocSupprimer_clicked()
{
    //confirmation ?

    //réccupération du MED_DEPOTLEGAL ancien
    QSqlQuery resMedOld("select MED_DEPOTLEGAL from medicament where MED_NOMCOMMERCIAL=\""+ui->listWidgetMedoc->currentItem()->text()+"\";");
    resMedOld.first();

    QSqlQuery req("delete from medicament where MED_DEPOTLEGAL="+resMedOld.value(0).toString()+";");
    this->chargerListeMedicaments();
    // on permet à l'utilisateur de recréer le praticien en conservant ses données dans les champs de saisi (en cas de fausse manip par exemple)
    ui->pushButtonMedocAjout->setEnabled(true);
    ui->pushButtonMedocModifier->setEnabled(false);
    ui->pushButtonMedocSupprimer->setEnabled(false);
    ui->labelMedocInfos->setText("Médicament supprimé");
}

void MainWindow::on_comboBoxMedocFamille_currentIndexChanged(int index)
{
    this->modificationExistanteMedoc();
}

void MainWindow::on_lineEditMedocDepotLegal_textEdited(QString )
{
    this->modificationExistanteMedoc();
}

void MainWindow::on_lineEditMedocNom_textEdited(QString )
{
    this->modificationExistanteMedoc();
}

void MainWindow::on_textEditMedocComposition_textChanged()
{
    this->modificationExistanteMedoc();
}

void MainWindow::on_textEditMedocContreIndication_textChanged()
{
//    this->modificationExistanteMedoc();
}

void MainWindow::on_textEditMedocEffet_textChanged()
{
//    this->modificationExistanteMedoc();
}

void MainWindow::on_lineEditMedocPrix_textEdited(QString )
{
    this->modificationExistanteMedoc();
}


/// VISITEUR >>>
void MainWindow::chargerListeVisiteur()
{
    ui->listWidgetVisiteur->clear();
        vecteurVisiteur.clear();
        QString libelle = ui->comboBoxVisiteurSecteurFiltre->currentText();
        QSqlQuery req0("select SEC_CODE from secteur where SEC_LIBELLE like \""+libelle+"\"");
        req0.first();
        QString secteurCode=req0.value(0).toString();
        QString res="SEC_CODE=\""+secteurCode+"\"";
        if(secteurCode=="" && ui->comboBoxVisiteurSecteurFiltre->currentIndex()!=0)
        {
            res="SEC_CODE is NULL";
        }
        QSqlQuery req("select VIS_MATRICULE, VIS_NOM, VIS_PRENOM from visiteur natural left outer join secteur where "+res+" and (VIS_NOM like \"%"+ui->lineEditVisiteurFiltre->text()+"%\" or VIS_PRENOM like \"%"+ui->lineEditVisiteurFiltre->text()+"%\") order by VIS_NOM;");
        int i=0;
        while(req.next())
        {
            QListWidgetItem* newItem= new QListWidgetItem(req.value(1).toString()+" "+req.value(2).toString());
            QLinearGradient degrad;
            degrad.setStart(0,ui->listWidgetVisiteur->y());
            degrad.setFinalStop(ui->listWidgetVisiteur->width(),ui->listWidgetVisiteur->y());
            if(i%2==0)
            {
                degrad.setColorAt(0,QColor(170, 204, 255));
                degrad.setColorAt(1,Qt::white);
            }
            else
            {
                degrad.setColorAt(0,QColor(210, 244, 255));
                degrad.setColorAt(1,Qt::white);
            }
            i++;

            QBrush mabrush(degrad);
            newItem->setBackground(mabrush);

            ui->listWidgetVisiteur->addItem(newItem);
            vecteurVisiteur.push_back(req.value(0).toString());
        }
}

void MainWindow::chargerComboBoxSecteurVisiteur()
{
    vecteurSecteurVisiteur.clear();
    QSqlQuery req("select SEC_CODE, SEC_LIBELLE from secteur");
    while(req.next())
    {
        ui->comboBoxVisiteurSecteur->addItem(req.value(1).toString());
        ui->comboBoxVisiteurSecteurFiltre->addItem(req.value(1).toString());
        vecteurSecteurVisiteur.push_back(req.value(1).toString());
    }
    ui->comboBoxVisiteurSecteur->addItem("Autre");
    ui->comboBoxVisiteurSecteurFiltre->addItem("Autre");
    vecteurSecteurVisiteur.push_back("Autre");
}

void MainWindow::chargerComboBoxLaboVisiteur()
{
    vecteurLaboVisiteur.clear();
    QSqlQuery req("select LAB_CODE, LAB_NOM from labo");
    while(req.next())
    {
        ui->comboBoxVisiteurLabo->addItem(req.value(1).toString());
        vecteurLaboVisiteur.push_back(req.value(1).toString());
    }
}

void MainWindow::on_comboBoxVisiteurSecteurFiltre_currentIndexChanged(int index)
{
    this->chargerListeVisiteur();
}

void MainWindow::on_lineEditVisiteurFiltre_textEdited(QString )
{
    this->chargerListeVisiteur();
}

void MainWindow::on_listWidgetVisiteur_clicked(QModelIndex index)
{
    QString matriculeVisiteur=vecteurVisiteur.at(ui->listWidgetVisiteur->currentRow());
    QSqlQuery req("select VIS_MATRICULE, VIS_NOM, VIS_PRENOM, VIS_ADRESSE, VIS_CP, VIS_VILLE, VIS_DATEEMBAUCHE, SEC_LIBELLE, LAB_NOM from visiteur natural left outer join secteur natural left outer join labo where VIS_MATRICULE=\""+matriculeVisiteur+"\";");
    req.first();
    ui->lineEditVisiteurMatricule->setText(req.value(0).toString());
    ui->lineEditVisiteurNom->setText(req.value(1).toString());
    ui->lineEditVisiteurPrenom->setText(req.value(2).toString());
    ui->lineEditVisiteurAdresse->setText(req.value(3).toString());
    ui->lineEditVisiteurCP->setText(req.value(4).toString());
    ui->lineEditVisiteurVille->setText(req.value(5).toString());
    ui->dateEditVisiteurDateEmbauche->setDate(QDate::fromString(req.value(6).toString(),"yyyy-MM-dd"));
    ui->comboBoxVisiteurSecteur->setCurrentIndex(vecteurSecteurVisiteur.lastIndexOf(req.value(7).toString())+1);
    ui->comboBoxVisiteurLabo->setCurrentIndex(vecteurLaboVisiteur.lastIndexOf(req.value(8).toString())+1);

    ui->pushButtonVisiteurModifier->setEnabled(false);
    ui->pushButtonVisiteurSupprimer->setEnabled(true);
    ui->pushButtonVisiteurAjout->setEnabled(false);
    ui->labelVisiteurInfos->setText("");
}

void MainWindow::on_pushButtonVisiteurNouveau_clicked()
{
    ui->lineEditVisiteurMatricule->clear();
    ui->lineEditVisiteurNom->clear();
    ui->lineEditVisiteurPrenom->clear();
    ui->lineEditVisiteurAdresse->clear();
    ui->lineEditVisiteurCP->clear();
    ui->lineEditVisiteurVille->clear();
    ui->comboBoxVisiteurLabo->setCurrentIndex(0);
    ui->comboBoxVisiteurSecteur->setCurrentIndex(0);
    ui->dateEditVisiteurDateEmbauche->setDate(QDate::currentDate());

    ui->pushButtonVisiteurAjout->setEnabled(true);
    ui->pushButtonVisiteurModifier->setEnabled(false);
    ui->pushButtonVisiteurSupprimer->setEnabled(false);
    ui->labelVisiteurInfos->setText("");
}

void MainWindow::on_pushButtonVisiteurAjout_clicked()
{
    if(ui->lineEditVisiteurNom->text()!="" && ui->lineEditVisiteurPrenom->text()!="" && ui->lineEditVisiteurMatricule->text()!="" && ui->comboBoxVisiteurSecteur->currentIndex()!=0 && ui->comboBoxVisiteurLabo->currentIndex()!=0)
    {
        //récuppération du SEC_CODE
        QSqlQuery reqSec("select SEC_CODE from secteur where SEC_LIBELLE=\""+ui->comboBoxVisiteurSecteur->currentText()+"\"");
        reqSec.first();

        //récuppération du LAB_CODE
        QSqlQuery reqLab("select LAB_CODE from labo where LAB_NOM=\""+ui->comboBoxVisiteurLabo->currentText()+"\"");
        reqLab.first();

        //vérification que VIS_MATRICULE est unique
        QSqlQuery reqVerif("select VIS_MATRICULE from visiteur where VIS_MATRICULE=\""+ui->lineEditVisiteurMatricule->text()+"\";");
        if(!(reqVerif.first()))// si la requete ne renvoi rien c'est bon
        {
            QSqlQuery req("insert into visiteur values(\""+ui->lineEditVisiteurMatricule->text()+"\",\""+ui->lineEditVisiteurNom->text()+"\",\""+ui->lineEditVisiteurPrenom->text()+"\",\""+ui->lineEditVisiteurAdresse->text()+"\",\""+ui->lineEditVisiteurCP->text()+"\",\""+ui->lineEditVisiteurVille->text()+"\","+ui->dateEditVisiteurDateEmbauche->date().toString("yyyy-MM-dd")+",\""+reqSec.value(0).toString()+"\",\""+reqLab.value(0).toString()+"\",NULL);");
            ui->labelVisiteurInfos->setText("Visiteur ajouté");
        }
        else
        {
            ui->labelVisiteurInfos->setText("Ce matricule est déjà utilisé");
        }
        //recharger la liste
        this->chargerListeVisiteur();
//
//        ui->pushButtonPraticientAjout->setEnabled(false);
//        ui->pushButtonPraticientModifier->setEnabled(false);
//        ui->pushButtonPraticientSupprimer->setEnabled(true);
//        ui->labelPraticieInfos->setText("Praticien ajouté");
    }
    else
    {
        ui->labelVisiteurInfos->setText("* champs obligatoire");
    }
}

void MainWindow::on_pushButtonVisiteurSupprimer_clicked()
{
    //confirmation ?
    QSqlQuery req("delete from visiteur where VIS_MATRICULE=\""+ui->lineEditVisiteurMatricule->text()+"\";");    
    this->chargerListeVisiteur();
    // on permet à l\"utilisateur de recréer le visiteur en conservant ses données dans les champs de saisi (en cas de fausse manip par exemple)
//    ui->pushButtonPraticientAjout->setEnabled(true);
//    ui->pushButtonPraticientModifier->setEnabled(false);
//    ui->pushButtonPraticientSupprimer->setEnabled(false);
//    //ui->pushButtonPraticienCopier->setEnabled(false);
    ui->labelVisiteurInfos->setText("Visiteur supprimé");
    ui->pushButtonVisiteurModifier->setEnabled(true);
    ui->pushButtonVisiteurModifier->setEnabled(false);
}

void MainWindow::on_pushButtonVisiteurModifier_clicked()
{
    if(ui->lineEditVisiteurNom->text()!="" && ui->lineEditVisiteurPrenom->text()!="" && ui->lineEditVisiteurMatricule->text()!="" && ui->comboBoxVisiteurSecteur->currentIndex()!=0 && ui->comboBoxVisiteurLabo->currentIndex()!=0)
    {
        //récuppération du SEC_CODE
        QSqlQuery reqSec("select SEC_CODE from secteur where SEC_LIBELLE=\""+ui->comboBoxVisiteurSecteur->currentText()+"\"");
        reqSec.first();

        //récuppération du LAB_CODE
        QSqlQuery reqLab("select LAB_CODE from labo where LAB_NOM=\""+ui->comboBoxVisiteurLabo->currentText()+"\"");
        reqLab.first();

        //vérification que VIS_MATRICULE existe
        QSqlQuery reqVerif("select VIS_MATRICULE from visiteur where VIS_MATRICULE=\""+ui->lineEditVisiteurMatricule->text()+"\";");
        if(reqVerif.first())// si la requete renvoi quelque chose c'est bon
        {
            QSqlQuery req("update visiteur set VIS_NOM=\""+ui->lineEditVisiteurNom->text()+"\",VIS_PRENOM=\""+ui->lineEditVisiteurPrenom->text()+"\",VIS_ADRESSE=\""+ui->lineEditVisiteurAdresse->text()+"\",VIS_CP=\""+ui->lineEditVisiteurCP->text()+"\",VIS_VILLE=\""+ui->lineEditVisiteurVille->text()+"\",VIS_DATEEMBAUCHE="+ui->dateEditVisiteurDateEmbauche->date().toString("yyyy-MM-dd")+",SEC_CODE=\""+reqSec.value(0).toString()+"\",LAB_CODE=\""+reqLab.value(0).toString()+"\" where VIS_MATRICULE=\""+ui->lineEditVisiteurMatricule->text()+"\";");
            ui->labelVisiteurInfos->setText("Visiteur modifié");
        }
        else
        {
            ui->labelVisiteurInfos->setText("Ce matricule n'existe pas");
        }
        //recharger la liste
        this->chargerListeVisiteur();
//
//        ui->pushButtonPraticientAjout->setEnabled(false);
//        ui->pushButtonPraticientModifier->setEnabled(false);
//        ui->pushButtonPraticientSupprimer->setEnabled(true);
//        ui->labelPraticieInfos->setText("Praticien ajouté");
    }
    else
    {
        ui->labelVisiteurInfos->setText("* champs obligatoire");
    }
}

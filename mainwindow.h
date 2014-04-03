#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QVector>
#include <QModelIndex>
#include <QCloseEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent, QString loginIn);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    void closeEvent(QCloseEvent * event);
    Ui::MainWindow *ui;
    QString login;
    /// PRATICIEN >>
    QVector <int> vecteurPraticien;
    QVector <QString> vecteurTypePraticien;
    void chargerListePraticiens();
    void chargerComboBoxTypePraticien();
    void modificationExistantePraticien();
    /// MEDICAMENT >>
    bool nouveauMedoc;
    QVector <QString> vecteurMedoc;
    QVector <QString> vecteurFamilleMedoc;
    void chargerListeMedicaments();
    void chargerComboBoxFamilleMedoc();
    void modificationExistanteMedoc();
    /// VISITEUR >>
    QVector <QString> vecteurVisiteur;
    QVector <QString> vecteurSecteurVisiteur;
    QVector <QString> vecteurLaboVisiteur;
    void chargerListeVisiteur();
    void chargerComboBoxSecteurVisiteur();
    void chargerComboBoxLaboVisiteur();

private slots:
    /// VISITEUR >>
    void on_pushButtonVisiteurModifier_clicked();
    void on_pushButtonVisiteurSupprimer_clicked();
    void on_pushButtonVisiteurAjout_clicked();
    void on_pushButtonVisiteurNouveau_clicked();
    void on_listWidgetVisiteur_clicked(QModelIndex index);
    void on_lineEditVisiteurFiltre_textEdited(QString );
    void on_comboBoxVisiteurSecteurFiltre_currentIndexChanged(int index);

    /// MEDICAMENT >>
    void on_lineEditMedocPrix_textEdited(QString );
    void on_textEditMedocEffet_textChanged();
    void on_textEditMedocContreIndication_textChanged();
    void on_textEditMedocComposition_textChanged();
    void on_lineEditMedocNom_textEdited(QString );
    void on_lineEditMedocDepotLegal_textEdited(QString );
    void on_lineEditMedocFiltre_textEdited(QString );

    void on_comboBoxMedocFamille_currentIndexChanged(int index);
    void on_comboBoxMedocFamilleFiltre_currentIndexChanged(int index);

    void on_pushButtonMedocSupprimer_clicked();
    void on_pushButtonMedocModifier_clicked();
    void on_pushButtonMedocAjout_clicked();
    void on_pushButtonMedocNouveau_clicked();

    void on_listWidgetMedoc_clicked(QModelIndex index);

    /// PRATICIEN >>
    void on_lineEditPraticientCoeff_textEdited(QString );
    void on_lineEditPraticientVille_textEdited(QString );
    void on_lineEditPraticientCP_textEdited(QString );
    void on_lineEditPraticientAdresse_textEdited(QString );
    void on_lineEditPraticientPrenom_textEdited(QString );
    void on_lineEditPraticientNom_textEdited(QString );
    void on_lineEditPraticienFiltre_textEdited(QString );

    void on_comboBoxPraticienType_currentIndexChanged(int index);
    void on_comboBoxPraticienTypeFiltre_currentIndexChanged(int index);

    void on_pushButtonPraticientModifier_clicked();
    void on_pushButtonPraticienNouveau_clicked();
    void on_pushButtonPraticientAjout_clicked();
    void on_pushButtonPraticientSupprimer_clicked();

    void on_listWidgetPraticiens_clicked(QModelIndex index);

    /// MENU >>
    void on_pushButtonQuitter_clicked();
    void on_pushButtonMedoc_clicked();
    void on_pushButtonPraticiens_clicked();
    void on_pushButtonVisiteurs_clicked();
};

#endif // MAINWINDOW_H

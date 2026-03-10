// src/gui/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GestoreAttivita.h" // Includi il gestore
#include "Personaggio.h"     // Includi il personaggio

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot per gestire le azioni dell'utente (es. pulsanti)
    void on_actionSalva_triggered();
    void on_actionCarica_triggered();

    // Slot per aggiornare la visualizzazione RPG
    void aggiornaStatoPersonaggio();

private:
    Ui::MainWindow *ui;
    GestoreAttivita *m_gestoreAttivita; // Istanza del Model
    Personaggio *m_personaggio;         // Istanza del Model RPG

    void setupModelConnections(); // Metodo per collegare Segnali e Slot
};

#endif // MAINWINDOW_H

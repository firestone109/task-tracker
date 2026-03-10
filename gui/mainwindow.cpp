// src/gui/MainWindow.cpp
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Creazione delle istanze del Model
    m_gestoreAttivita = new GestoreAttivita(this);
    m_personaggio = new Personaggio(this);

    // 2. Collegamento dei Segnali e Slot
    setupModelConnections();

    // 3. Inizializzazione della GUI (es. aggiorna subito lo stato RPG)
    aggiornaStatoPersonaggio();
}

MainWindow::~MainWindow() {
    delete ui;
    // m_gestoreAttivita e m_personaggio sono figli di 'this',
    // quindi Qt li elimina automaticamente.
}

void MainWindow::setupModelConnections() {
    // 1. Collegamento della logica RPG:
    // Quando il GestoreAttivita emette xpAggiornata(xp),
    // il Personaggio riceve l'XP tramite aggiungiEsperienza(xp).
    connect(m_gestoreAttivita, &GestoreAttivita::xpAggiornata,
            m_personaggio, &Personaggio::aggiungiEsperienza);

    // 2. Collegamento della GUI al Personaggio:
    // Quando lo stato del Personaggio cambia (livello/xp),
    // la MainWindow aggiorna la sua visualizzazione.
    connect(m_personaggio, &Personaggio::statoCambiato,
            this, &MainWindow::aggiornaStatoPersonaggio);

    // 3. Collegamento delle azioni Salva/Carica ai metodi del Gestore:
    connect(ui->actionSalva, SIGNAL(triggered()),
            this, SLOT(on_actionSalva_triggered()));

    connect(ui->actionCarica, SIGNAL(triggered()),
            this, SLOT(on_actionCarica_triggered()));

    // 4. Collegamento degli errori di persistenza:
    connect(m_gestoreAttivita, &GestoreAttivita::errorePersistenza,
            this, [this](const QString& msg) {
                QMessageBox::critical(this, "Errore di Persistenza", msg);
            });
}

void MainWindow::on_actionSalva_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva Attività", "", "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        m_gestoreAttivita->salvaSuFile(fileName);
    }
}

void MainWindow::on_actionCarica_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Carica Attività", "", "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        m_gestoreAttivita->caricaDaFile(fileName);
    }
}

void MainWindow::aggiornaStatoPersonaggio() {
    // aggiorna le etichette nella GUI
    ui->labelLivello->setText(QString("Livello: %1").arg(m_personaggio->livello()));
    ui->labelXP->setText(QString("XP: %1/%2").arg(m_personaggio->xpCorrente()).arg(m_personaggio->xpPerProssimoLivello()));
}

#ifndef GESTOREATTIVITA_H
#define GESTOREATTIVITA_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "Attivita.h"
// dichiarazioni forward per le classi derivate sennò mi esce un warning
class CompitoConScadenza;
class EventoProgrammato;
class AbitudineRicorrente;

// Classe che gestisce la collezione di tutte le attività e la comunicazione con la GUI
class GestoreAttivita : public QObject {
    Q_OBJECT // Macro essenziale per Segnali e Slot

public:
    explicit GestoreAttivita(QObject *parent = nullptr);

    // -------------------------------------------------------------------
    // Metodi CRUD (Creazione, Lettura, Aggiornamento, Eliminazione)
    // -------------------------------------------------------------------

    // Aggiunge una nuova attività alla collezione
    void aggiungiAttivita(QSharedPointer<Attivita> attivita);

    // Restituisce la lista di tutte le attività (Lettura)
    QList<QSharedPointer<Attivita>> getAttivita() const { return m_listaAttivita; }

    // Aggiorna lo stato di un'attività e calcola l'XP (Aggiornamento)
    void completaAttivita(int indice);

    // Rimuove un'attività (Eliminazione)
    void rimuoviAttivita(int indice);

    // -------------------------------------------------------------------
    // Metodi di Persistenza (Salvataggio e Caricamento)
    // -------------------------------------------------------------------

    // Salva la collezione su file (Vincolo 12)
    bool salvaSuFile(const QString& path);

    // Carica la collezione da file (Vincolo 12)
    bool caricaDaFile(const QString& path);

signals:
    // Segnali per notificare la GUI di un cambiamento (Cruciale per Model-View)
    void attivitaCambiata();
    void xpAggiornata(int xpGuadagnata);
    void errorePersistenza(const QString& messaggio);

private:
    // La collezione di attività (usa puntatori intelligenti per il polimorfismo)
    QList<QSharedPointer<Attivita>> m_listaAttivita;

    // Metodo Factory per istanziare l'oggetto corretto durante il caricamento
    QSharedPointer<Attivita> creaAttivitaDaJson(const QJsonObject& json);
};

#endif // GESTOREATTIVITA_H

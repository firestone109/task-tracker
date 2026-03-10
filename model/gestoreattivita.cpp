#include "GestoreAttivita.h"
#include "CompitoConScadenza.h"
#include "EventoProgrammato.h"
#include "AbitudineRicorrente.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug> // per debugging

GestoreAttivita::GestoreAttivita(QObject *parent) : QObject(parent) {
    // inizializza QObject
}

// --- Metodi CRUD

void GestoreAttivita::aggiungiAttivita(QSharedPointer<Attivita> attivita) {
    m_listaAttivita.append(attivita);
    emit attivitaCambiata(); // Notifica la GUI
}

void GestoreAttivita::completaAttivita(int indice) {
    if (indice >= 0 && indice < m_listaAttivita.size()) {
        QSharedPointer<Attivita> attivita = m_listaAttivita.at(indice);

        // 1. Aggiorna lo stato (se non è già completata)
        if (attivita->stato() != StatoAttivita::Completed) {
            attivita->setStato(StatoAttivita::Completed);

            // 2. Calcola l'XP guadagnata (Metodo Polimorfo!)
            int xp = attivita->calcolaXP();

            // 3. Emette i segnali
            emit xpAggiornata(xp);
            emit attivitaCambiata();
        }
    }
}

void GestoreAttivita::rimuoviAttivita(int indice) {
    if (indice >= 0 && indice < m_listaAttivita.size()) {
        m_listaAttivita.removeAt(indice);
        emit attivitaCambiata(); // Notifica la GUI
    }
}

// -------------------------------------------------------------------
// Metodo Factory (Cruciale per il Polimorfismo in Deserializzazione)
// -------------------------------------------------------------------

QSharedPointer<Attivita> GestoreAttivita::creaAttivitaDaJson(const QJsonObject& json) {
    QString tipo = json["tipo"].toString();
    QSharedPointer<Attivita> attivita;

    // Usa l'identificatore "tipo" salvato da toJson() per istanziare la classe corretta
    if (tipo == "CompitoConScadenza") {
        attivita = QSharedPointer<Attivita>(new CompitoConScadenza("", "", QDate(), QTime(), Priorita::Bassa));
    } else if (tipo == "EventoProgrammato") {
        attivita = QSharedPointer<Attivita>(new EventoProgrammato("", "", QDate(), "", 0));
    } else if (tipo == "AbitudineRicorrente") {
        attivita = QSharedPointer<Attivita>(new AbitudineRicorrente("", "", QDate(), Frequenza::Giornaliera, 0));
    } else {
        qWarning() << "Tipo di attività sconosciuto:" << tipo;
        return nullptr;
    }

    // Chiama il metodo polimorfo per caricare i dati specifici
    attivita->fromJsonObject(json);
    return attivita;
}

// -------------------------------------------------------------------
// Metodi di Persistenza
// -------------------------------------------------------------------

bool GestoreAttivita::salvaSuFile(const QString& path) {
    QJsonArray array;
    for (const auto& attivita : m_listaAttivita) {
        // Chiama il metodo polimorfo toJson() su ogni oggetto
        array.append(attivita->toJson());
    }

    QJsonDocument doc(array);
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        emit errorePersistenza("Impossibile aprire il file per la scrittura.");
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool GestoreAttivita::caricaDaFile(const QString& path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        emit errorePersistenza("Impossibile aprire il file per la lettura.");
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        emit errorePersistenza("Il file non contiene un array JSON valido.");
        return false;
    }

    m_listaAttivita.clear();
    QJsonArray array = doc.array();

    for (const QJsonValue& value : array) {
        if (value.isObject()) {
            QSharedPointer<Attivita> attivita = creaAttivitaDaJson(value.toObject());
            if (attivita) {
                m_listaAttivita.append(attivita);
            }
        }
    }

    emit attivitaCambiata(); // Notifica la GUI che i dati sono stati caricati
    return true;
}

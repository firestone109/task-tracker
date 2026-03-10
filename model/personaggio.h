#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#include <QObject>

class Personaggio : public QObject {
    Q_OBJECT // Essenziale per Segnali e Slot

public:
    explicit Personaggio(QObject *parent = nullptr);

    // Metodo per ricevere l'XP guadagnata dal GestoreAttivita
    Q_SLOT void aggiungiEsperienza(int xp);

    // Getter
    int livello() const { return m_livello; }
    int xpCorrente() const { return m_xpCorrente; }
    int xpTotale() const { return m_xpTotale; }
    int xpPerProssimoLivello() const { return m_xpPerProssimoLivello; }
signals:
    // Segnale emesso quando il livello o l'XP cambiano
    void statoCambiato();

private:
    int m_livello;
    int m_xpCorrente; // XP accumulata nel livello corrente
    int m_xpTotale;   // XP totale accumulata
    int m_xpPerProssimoLivello;

    void controllaLivello();
};

#endif // PERSONAGGIO_H

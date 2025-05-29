#ifndef MIECLASSI_H_INCLUDED
#define MIECLASSI_H_INCLUDED

const int DRAGO = 0;
const int LUPO_MANNARO = 1;
const int ZOMBIE = 2;
const int VAMPIRO = 3;

const int GUERRIERO = 0;
const int MAGO = 1;
const int CHIERICO = 2;
const int ARCIERE = 3;

class Mostro {
public:
    string name;
    float vita;
    float attacco;
    float difesa;
    int tipo;
    int vitaMax;

    Mostro(string n, float v, float a, float d, int t) : name(n), vita(v), attacco(a), difesa(d), tipo(t), vitaMax(v) {}

    void stampaInformazioni() {
        cout << "Nome: " << name << endl;
        cout << "HP: " << vita << endl;
        cout << "Attacco: " << attacco << endl;
        cout << "Difesa: " << difesa << endl;
        cout << "Tipo: " << tipo << endl;
    }
};

class Personaggio {

public:
    string name;
    int tipoClasse;

    // Sistema di livelli
    int livello = 1;
    int esperienza = 0;
    int esperienzaPerLivello = 100;
    int puntiStatistica = 0;

    // Statistiche base
    float vita = 800;
    int vitaMax = 800;
    float mana = 200;
    const int manaMax = 1000;
    float attacco = 100;
    float difesa = 80;
    float tassocritico = 0.10;

    // Buff temporanei
    int buffTurni = 0;
    int cooldownBuff = 0;

    // Metodi per livellare
    void guadagnaEsperienza(int exp) {
        esperienza+= exp;
        cout << name << " guadagna " << exp << " punti esperienza!" << endl;

        // Level UP
        while (esperienza >= esperienzaPerLivello){
        saliDiLivello();
        }
    }

    void saliDiLivello(){
        esperienza -= esperienzaPerLivello;
        livello++;
        esperienzaPerLivello += 50; // Progressione requisiti
        puntiStatistica += 3; // 3 punti stat per livello

        cout << "\n*** LIVELLO AUMENTATO! ***" << endl;
        cout << name << " è ora di livello " << livello << "!" << endl;
        cout << "Hai guadagnato 3 punti statistica da distribuire!" << endl;

        // Bonus automatici per ogni level up
        vitaMax += 50;
        vita+=50;
        mana += 20;

        distribuisciPuntiStatistica();
    }

    void distribuisciPuntiStatistica(){
        while (puntiStatistica > 0){
            cout << "\nPunti statistica disponibili: " << puntiStatistica << endl;
            cout << "Dove vuoi investire?" << endl;
            cout << "1. Attacco (+10)" << endl;
            cout << "2. Difesa (+8)" << endl;
            cout << "3. Vita Massima (+100)" << endl;
            cout << "4. Tasso Critico (+2%)" << endl;
            cout << "Scegli saggiamente: ";

            int scelta;
            cin >> scelta;

            switch (scelta){
                case 1:
                    attacco+= 10;
                    cout << "Attaccco aumentato a " << attacco << "!" << endl;
                  break;
                case 2:
                    difesa += 8;
                    cout << "Difesa aumentata a " << difesa << "!" << endl;
                    break;
                case 3:
                    vitaMax += 100;
                    vita += 100;
                    cout << "Vita massima aumentata a " << vitaMax << "!" << endl;
                    break;
                case 4 :
                    tassocritico += 0.02;
                    cout << "Tasso critico aumentato a " << (tassocritico*100) << "%" << endl;
                    break;
                default:
                    cout << "Scelta non valida. Fai attenzione a prender bene la mira col ditino." << endl;
                    continue;
            }
            puntiStatistica--;
        }
    }

    virtual void stampaInformazioni() {
        cout << "Nome: " << name << "(Livello " << livello << ")" << endl;
        cout << "Esperienza: " << esperienza << "/" << esperienzaPerLivello << endl;
        cout << "HP: " << vita << "/" << vitaMax << endl;
        cout << "Mana: " << mana << "/" << manaMax << endl;
        cout << "Attacco: " << attacco << endl;
        cout << "Difesa: " << difesa << endl;
        cout << "Tasso Critico: " << (tassocritico*100) << "%" << endl;
    }

    virtual ~Personaggio() {}
};

class Guerriero : public Personaggio {
public:
    Guerriero() {
        name = "Guerriero";
        tipoClasse = GUERRIERO;

        float vitaBase = vita;

        vita = vita * 1.8;
        vitaMax = vita;
        mana = mana * 0.7;
        attacco = attacco * 1.1;
        difesa = difesa * 2;
        tassocritico = tassocritico * 1.5;
    }
};

class Mago : public Personaggio {
public:
    Mago() {
        name = "Mago";
        tipoClasse = MAGO;

        float vitaBase = vita;

        vita = vita * 0.9;
        vitaMax = vita;
        mana = mana * 3;
        attacco = attacco * 2.2;
        difesa = difesa * 0.6;
        tassocritico = tassocritico * 1.3;
    }
};

class Chierico : public Personaggio {
public:
    Chierico() {
        name = "Chierico";
        tipoClasse = CHIERICO;

        float vitaBase = vita;

        vita = vita * 1.5;
        vitaMax = vita;
        mana = mana * 2.5;
        attacco = attacco * 0.8;
        difesa = difesa * 1.8;
        tassocritico = tassocritico * 0.8;
    }
};

class Arciere : public Personaggio {
public:
    Arciere() {
        name = "Arciere";
        tipoClasse = ARCIERE;

        float vitaBase = vita;

        vita = vita * 1.3;
        vitaMax = vita;
        mana = mana * 1.2;
        attacco = attacco * 1.8;
        difesa = difesa * 0.9;
        tassocritico = tassocritico * 3.5;
    }
};

#endif // MIECLASSI_H_INCLUDED

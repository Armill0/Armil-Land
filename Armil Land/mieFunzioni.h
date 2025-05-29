#ifndef MIEFUNZIONI_H_INCLUDED
#define MIEFUNZIONI_H_INCLUDED

// Dichiarazioni delle funzioni
Personaggio* creaPersonaggio();
Mossa* getMossePersonaggio(int tipoClasse);
Mossa scegliMossa(Mossa mosse[], int dimensione, Personaggio& giocatore); // Aggiunta dichiarazione
void stampaLenta(const string& testo);
void storiaIntroduttiva();
string messaggioMaestria(const string& nomeEroe, int classe);
bool colpoCritico(float tassoCritico);
float calcolaDanno(Personaggio& attaccante, Mostro& difensore);
float calcolaDannoMostro(Mostro& attaccante, Personaggio& difensore);
void barraVita(string nome, int vita, int vitaMax);
void applicaEffettoRuna(Personaggio* personaggio);
int generaIndiceCasuale(int max);
Mostro creaMostroCasuale(int livelloGiocatore);
int calcolaEsperienza(Mostro& mostro);
bool controllaGameOver(Personaggio* personaggio, int mostriSconfitti);
bool gestisciCombattimento(Personaggio* personaggio, Mostro& mostroAvversario, int& mostriSconfitti);
void mostraStatoCombattimento(Personaggio* personaggio, Mostro& mostro);
void menu();
bool salvaPartita(Personaggio* personaggio, int mostriSconfitti);
Personaggio* caricaPartita(int& mostriSconfitti);
bool esisteSalvataggio();

void stampaLenta(const string& testo){
    for (char c : testo) {
        cout << c;
        cout.flush();
        #ifdef _WIN32
            Sleep(17);
        #else
            usleep(17000);
        #endif
    }
    cout << endl;
}

void storiaIntroduttiva(){
    string storie[] {
            "In un mondo avvolto dalle fiamme dei draghi, solo un eroe può riportare la pace... \n",
            "Le forze oscure avanzano. Il destino di Armil Land è nelle tue mani... \n",
            "Un'antica profezia narra di un guerriero destinato a salvare il regno. Sarai tu? \n",
            "I mostri invadono le terre. È giunto il momento di impugnare le armi e combattere! \n",
            "Nel cuore della foresta proibita, un'oscura minaccia cresce... Solo un vero eroe può fermarla! \n"
    };
    int indiceCasuale = rand() % (sizeof(storie) / sizeof(storie[0]));
    cout << "**********************************************************************************************" << endl;
    stampaLenta(storie[indiceCasuale]);
    cout << "**********************************************************************************************" << endl;
}

Personaggio* creaPersonaggio(){
    Personaggio* personaggio = nullptr;

    while (true){
        cout << "Scegli il tuo personaggio: \n";
        cout << "1. Guerriero Indomito\n";
        cout << "2. Mago Arcano\n";
        cout << "3. Chierico Devoto\n";
        cout << "4. Arciere Letale\n";
        cout << "0. Esci dal gioco \n";
        cout << "***************************************** \n";
        int scelta;
        cin >> scelta;

        if (scelta == 0){
            cout << "Grazie per aver passato il tuo tempo nel magico mondo di Armil Land! \n";
            return nullptr; // Ritorna nullptr invece di return vuoto
        }

        switch (scelta) {
        case 1:
            personaggio = new Guerriero();
            break;
        case 2:
            personaggio = new Mago();
            break;
        case 3:
            personaggio = new Chierico();
            break;
        case 4:
            personaggio = new Arciere();
            break;
        default:
            cout << "Selezione non valida. Riprova! \n" << endl;
            continue;
        }

        cout << "Inserisci il nome del tuo eroe: \n";
        cin >> personaggio->name;
        cout << "__________________________ \n";
        personaggio->stampaInformazioni();
        cout << "__________________________ \n";
        break;
    }

    personaggio->vitaMax = personaggio->vita;
    return personaggio;
}

Mossa* getMossePersonaggio(int tipoClasse){
    switch (tipoClasse) {
        case GUERRIERO:
            return mosseGuerriero;
        case MAGO:
            return mosseMago;
        case CHIERICO:
            return mosseChierico;
        case ARCIERE:
            return mosseArciere;
        default:
            return mosseGuerriero;
    }
}

Mostro creaMostroCasuale(int livelloGiocatore) {
    // Scaling man mano che il giocatore sale di livello
    float moltiplicatoreLivello = 1.0 + (livelloGiocatore - 1) * 0.3; // 30% per livello

    // Mostri base bilanciati
    Mostro zombie("Zombie", 600 * moltiplicatoreLivello, 80 * moltiplicatoreLivello, 30 * moltiplicatoreLivello, ZOMBIE);
    Mostro lupoMannaro("Lupo Mannaro", 1000 * moltiplicatoreLivello, 100 * moltiplicatoreLivello, 45 * moltiplicatoreLivello, LUPO_MANNARO);
    Mostro vampiro("Vampiro", 1300 * moltiplicatoreLivello, 90 * moltiplicatoreLivello, 55 * moltiplicatoreLivello, VAMPIRO);
    Mostro drago("Drago", 1800 * moltiplicatoreLivello, 150 * moltiplicatoreLivello, 70 * moltiplicatoreLivello, DRAGO);

    Mostro mostri[] = { zombie, lupoMannaro, vampiro, drago };
    int indiceMostroCasuale = generaIndiceCasuale(4);
    return mostri[indiceMostroCasuale];
}


int calcolaEsperienza(Mostro& mostro) {
    switch(mostro.tipo) {
        case ZOMBIE: return 20;
        case LUPO_MANNARO: return 35;
        case VAMPIRO: return 45;
        case DRAGO: return 60;
        default: return 25;
    }
}


string messaggioMaestria(const string& nomeEroe, int classe){
    switch (classe) {
        case GUERRIERO: return "**" + nomeEroe + " scatena la sua furia indomita!**";
        case MAGO: return "**" + nomeEroe + " canalizza un potere arcano devastante!**";
        case CHIERICO: return "**" + nomeEroe + " invoca il giudizio sacro!**";
        case ARCIERE: return "**" + nomeEroe + " sferra un tiro perfetto con precisione letale!**";
        default: return "**" + nomeEroe + " esegue una tecnica impeccabile!**";
    }
}

bool colpoCritico(float tassoCritico){
    float probabilita = (float)(rand() % 100) / 100.0;
    return probabilita < tassoCritico;
}

float calcolaDanno(Personaggio& attaccante, Mostro& difensore) {
    float moltiplicatore = 1.0;

    if (attaccante.tipoClasse == GUERRIERO && difensore.tipo == LUPO_MANNARO) {
        moltiplicatore = 2.0;
    } else if (attaccante.tipoClasse == MAGO && difensore.tipo == ZOMBIE) {
        moltiplicatore = 1.5;
    } else if (attaccante.tipoClasse == CHIERICO && difensore.tipo == VAMPIRO) {
        moltiplicatore = 2.0;
    } else if (attaccante.tipoClasse == ARCIERE && difensore.tipo == DRAGO) {
        moltiplicatore = 1.5;
    }

    float variazione = (rand() % 20 - 10) / 100.00;
    float dannoBase = attaccante.attacco * moltiplicatore * (1 + variazione);

    float riduzioneDifesa = difensore.difesa * 0.5;
    float dannoFinale = max(1.0f, dannoBase - riduzioneDifesa);

    if (colpoCritico(attaccante.tassocritico)){
        dannoFinale *= 2;
        cout << messaggioMaestria(attaccante.name, attaccante.tipoClasse) << "\n Il danno raddoppia!\n";
    }
    return dannoFinale;
}

float calcolaDannoMostro(Mostro& attaccante, Personaggio& difensore){
    float variazione = (rand() % 20 - 10) / 100.0;
    float dannoBase = attaccante.attacco * (1 + variazione);

    float riduzioneDifesa = difensore.difesa * 0.5;
    float dannoFinale = max(1.0f, dannoBase - riduzioneDifesa);

    return dannoFinale;
}

void barraVita(string nome, int vita, int vitaMax) {
    int lunghezzaBarra = 20;
    int vitaCorrente = max(0, vita);
    int segmenti = (vitaCorrente * lunghezzaBarra) / vitaMax;
    segmenti = min(segmenti, lunghezzaBarra);

    cout << nome << " [";

    for (int i = 0; i < lunghezzaBarra; i++) {
        if (i < segmenti) {
            cout << "=";
        } else {
            cout << ".";
        }
    }

    cout << "] " << vita << "/" << vitaMax << " HP\n";
}

void mostraStatoCombattimento(Personaggio* personaggio, Mostro& mostro) {
    cout << "\nStai combattendo contro un " << mostro.name << "!\n";
    cout << "Ecco le sue informazioni: \n";
    mostro.stampaInformazioni();
    cout << "__________________________ \n";

    cout << "\nStato del tuo eroe:\n";
    barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);
    cout << "Mana: " << personaggio->mana << "/" << personaggio->manaMax << "\n";
    cout << "__________________________ \n";
}

Mossa scegliMossa(Mossa mosse[], int dimensione, Personaggio& giocatore) {
    cout << "\nScegli una mossa:\n";
    for (int i = 0; i < dimensione; i++) {
        cout << i + 1 << ". " << mosse[i].nome << "\n";
    }

    int scelta;
    do {
        cin >> scelta;
        if (scelta < 1 || scelta > dimensione){
            cout << "Selezione non valida. Riprova!\n";
        }
    } while (scelta < 1 || scelta > dimensione);

    switch (scelta) {
    case 1:
        if (giocatore.mana < 200) {
            cout << giocatore.name << " non ha abbastanza mana per attaccare! \n";
            return scegliMossa(mosse, dimensione, giocatore);
        }

        giocatore.mana -= 200;
        cout << "Mana residuo: " << giocatore.mana << endl;
        break;
    case 2:{
        cout << giocatore.name << " si concentra e ripristina il suo mana. \n";
        giocatore.mana += 600;
        if (giocatore.mana > giocatore.manaMax){
            giocatore.mana = giocatore.manaMax;
        }

        if (giocatore.cooldownBuff > 0) {
            cout << giocatore.name << " non può usare il buff per altri " << giocatore.cooldownBuff << " turni. \n";
            return scegliMossa(mosse, dimensione, giocatore);
        }

        if (giocatore.tipoClasse == GUERRIERO) {
            giocatore.difesa *= 1.8;
            cout << giocatore.name << " usa Scudo Infrangibile! La sua difesa aumenta. \n";
        } else if (giocatore.tipoClasse == MAGO) {
            giocatore.attacco *= 1.8;
            cout << giocatore.name << " usa Potere Occulto! Il suo focus magico aumenta. \n";
        } else if (giocatore.tipoClasse == CHIERICO) {
            giocatore.vita += giocatore.vita * 0.25;
            giocatore.difesa *= 1.2;
            cout << giocatore.name << " usa Benedizione Celeste! Recupera un po' di vita. \n";
        } else if (giocatore.tipoClasse == ARCIERE) {
            giocatore.tassocritico *= 1.2;
            giocatore.attacco *= 1.2;
            cout << giocatore.name << " usa Occhio di Falco! Le probabilità di critico aumentano. \n";
        }

        giocatore.cooldownBuff = 4;

        Mossa mossaBuff;
        mossaBuff.nome = "Buff";
        mossaBuff.danno = 0;
        return mossaBuff;
    }
    case 3:
        cout << giocatore.name << " tenta la ritirata strategica! \n";
        break;
    default:
        cout << "Selezione non valida! \n";
    }

    return mosse[scelta - 1];
}

bool gestisciCombattimento(Personaggio* personaggio, Mostro& mostroAvversario, int& mostriSconfitti) {
    Mossa* mossePersonaggio = getMossePersonaggio(personaggio->tipoClasse);
    int dimensioneMosse = 3;
    int vitaMaxMostro = (int)mostroAvversario.vita;

    mostraStatoCombattimento(personaggio, mostroAvversario);
    bool fugaEseguita = false;

    while (mostroAvversario.vita > 0 && personaggio->vita > 0 && !fugaEseguita) {
        Mossa mossaScelta = scegliMossa(mossePersonaggio, dimensioneMosse, *personaggio);

        if (mossaScelta.nome == "Fuga" || mossaScelta.nome == "Ritirata Strategica") {
            cout << "Ti sei ritirato dal combattimento! Il prossimo mostro si avvicina...\n";
            personaggio->vita -= 250;

            cout << "\nStato dopo la ritirata:\n";
            barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);
            cout << "Mana: " << personaggio->mana << "/" << personaggio->manaMax << "\n";
            cout << "__________________________ \n";

            if (controllaGameOver(personaggio, mostriSconfitti)) {
                return false;
            }

            fugaEseguita = true;
            break;
        }

        if (mossaScelta.nome == "Buff" || mossaScelta.danno == 0) {
            cout << personaggio->name << " si concentra sui propri poteri interiori. Nessun attacco effettuato.\n";
            cout << "\nStato dopo il buff:\n";
            barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);
            cout << "Mana: " << personaggio->mana << "/" << personaggio->manaMax << "\n";
            cout << "__________________________ \n";
        } else {
            float danno = calcolaDanno(*personaggio, mostroAvversario);
            mostroAvversario.vita -= danno;

            cout << "Hai inflitto " << danno << " danni al " << mostroAvversario.name << "!" << endl;
            cout << "Vita residua del " << mostroAvversario.name << ": " << mostroAvversario.vita << "! \n";
            barraVita(mostroAvversario.name, (int)mostroAvversario.vita, vitaMaxMostro);

            cout << "\nIl tuo stato attuale:\n";
            barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);
            cout << "Mana: " << personaggio->mana << "/" << personaggio->manaMax << "\n";
            cout << "__________________________ \n";
        }

        if (personaggio->cooldownBuff > 0) {
            personaggio->cooldownBuff--;
        }

        if (mostroAvversario.vita <= 0) {
            cout << "\n **Hai sconfitto il " << mostroAvversario.name << "!** \n";
            mostriSconfitti++;

            // Guadagna exp
            int exp = calcolaEsperienza(mostroAvversario);
            personaggio->guadagnaEsperienza(exp);

            if (mostriSconfitti % 5 == 0) {
                applicaEffettoRuna(personaggio);
            }

            break;
        }

        float dannoMostro = calcolaDannoMostro(mostroAvversario, *personaggio);
        personaggio->vita -= dannoMostro;

        cout << "Il " << mostroAvversario.name << " ti attacca! " << personaggio->name << " subisce " << dannoMostro << " danni. Vita residua: " << personaggio->vita << endl;

        barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);

        if (controllaGameOver(personaggio, mostriSconfitti)) {
            return false;
        }
    }

    return true;
}

void applicaEffettoRuna(Personaggio* personaggio) {
    cout << "\n Una runa antica sprigiona il suo potere! \n";
    personaggio->mana = 500;
    personaggio->vita += 200;

    cout << " Il mana di " << personaggio->name << " ora è al massimo! \n";
    cout << " Sembra anche più in forma!\n";

    cout << "\nStato dopo il potenziamento della runa:\n";
    barraVita(personaggio->name, (int)personaggio->vita, (int)personaggio->vitaMax);
    cout << "Mana: " << personaggio->mana << "/" << personaggio->manaMax << "\n";
    cout << "__________________________ \n";
}

int generaIndiceCasuale(int max) {
    return rand() % max;
}

bool controllaGameOver(Personaggio* personaggio, int mostriSconfitti) {
    if (personaggio->vita <= 0) {
        cout << "\n***************************************************\n";
        cout << "                    GAME OVER!                    \n";
        cout << "***************************************************\n";
        cout << personaggio->name << " ha sconfitto " << mostriSconfitti << " mostri!\n";

        if (mostriSconfitti >= 1) {
            cout << "Armil Land è molto più sicura ora <3\n";
            cout << personaggio->name << " è un vero eroe.\n";
        } else {
            cout << "Oh, no! Chi salverà Armil Land ora?\n";
        }
        cout << "***************************************************\n";

        delete personaggio;
        return true;
    }
    return false;
}

void menu() {
    cout << "***************************************** \n";
    cout << "Benvenuto nel magico mondo di Armil Land! \n" << endl;

    srand(time(0));

    Personaggio* personaggio = nullptr;
    int mostriSconfitti = 0;

    // Menu principale con opzione caricamento
    if (esisteSalvataggio()) {
        cout << "Salvataggio trovato!" << endl;
        cout << "1. Nuova partita" << endl;
        cout << "2. Carica partita" << endl;
        cout << "0. Esci" << endl;

        int scelta;
        cin >> scelta;

        switch (scelta) {
            case 1:
                personaggio = creaPersonaggio();
                break;
            case 2:
                personaggio = caricaPartita(mostriSconfitti);
                break;
            case 0:
                return;
            default:
                cout << "Scelta non valida, creo nuova partita..." << endl;
                personaggio = creaPersonaggio();
        }
    } else {
        cout << "Nessun salvataggio trovato. Inizierai una nuova partita!" << endl;
        personaggio = creaPersonaggio();
    }

    if (personaggio == nullptr) {
        return;
    }

    // Loop principale del gioco
    while (personaggio->vita > 0) {
        cout << "\n=== MENU COMBATTIMENTO ===" << endl;
        cout << "1. Combatti contro un mostro" << endl;
        cout << "2. Salva partita" << endl;
        cout << "3. Esci dal gioco" << endl;
        cout << "Scegli: ";

        int scelta;
        cin >> scelta;

        switch (scelta) {
            case 1: {
                Mostro mostroAvversario = creaMostroCasuale(personaggio->livello);
                if (!gestisciCombattimento(personaggio, mostroAvversario, mostriSconfitti)) {
                    return; // Game over
                }
                cout << "Preparati per il prossimo combattimento!\n";
                break;
            }
            case 2:
                salvaPartita(personaggio, mostriSconfitti);
                break;
            case 3:
                cout << "Vuoi salvare prima di uscire? (s/n): ";
                char salvare;
                cin >> salvare;
                if (salvare == 's' || salvare == 'S') {
                    salvaPartita(personaggio, mostriSconfitti);
                }
                delete personaggio;
                return;
            default:
                cout << "Scelta non valida!" << endl;
        }
    }

    delete personaggio;
}

bool salvaPartita(Personaggio* personaggio, int mostriSconfitti) {
    ofstream file("salvataggio.txt");

    if (!file.is_open()) {
        cout << "Errore nel salvare la partita!" << endl;
        return false;
    }
    // Salvataggio dei dati del personaggio
    file << personaggio->name << endl;
    file << personaggio->tipoClasse << endl;
    file << personaggio->livello << endl;
    file << personaggio->esperienza << endl;
    file << personaggio->esperienzaPerLivello << endl;
    file << personaggio->vita << endl;
    file << personaggio->vitaMax << endl;
    file << personaggio->mana << endl;
    file << personaggio->attacco << endl;
    file << personaggio->difesa << endl;
    file << personaggio->tassocritico << endl;
    file << personaggio->cooldownBuff << endl;
    file << mostriSconfitti << endl;

    file.close();
    cout << "\n*** PARTITA SALVATA CON SUCCESSO! ***" << endl;
    return true;
}

Personaggio* caricaPartita(int& mostriSconfitti) {
    ifstream file("salvataggio.txt");

    if (!file.is_open()) {
        cout << "Nessun salvataggio trovato!" << endl;
        return nullptr;
    }

    string nome;
    int tipoClasse, livello, esperienza, esperienzaPerLivello, vitaMax, cooldownBuff;
    float vita, mana, attacco, difesa, tassocritico;

    // Carica i dati
    getline(file, nome);
    file >> tipoClasse >> livello >> esperienza >> esperienzaPerLivello >> vita >> vitaMax >> mana >> attacco >> difesa >> tassocritico >> cooldownBuff >> mostriSconfitti;

    file.close();

    // Crea il personaggio giusto usando i dati del file txt
    Personaggio* personaggio = nullptr;
    switch (tipoClasse) {
        case GUERRIERO:
            personaggio = new Guerriero();
            break;
        case MAGO:
            personaggio = new Mago();
            break;
        case CHIERICO:
            personaggio = new Chierico();
            break;
        case ARCIERE:
            personaggio = new Arciere();
            break;
        default:
            cout << "Tipo non valido nel salvataggio!" << endl;
            return nullptr;
    }

    // Ripristina i valori salvati nel file txt
    personaggio->name = nome;
    personaggio->livello = livello;
    personaggio->esperienza = esperienza;
    personaggio->esperienzaPerLivello = esperienzaPerLivello;
    personaggio->vita = vita;
    personaggio->vitaMax = vitaMax;
    personaggio->mana = mana;
    personaggio->attacco = attacco;
    personaggio->difesa = difesa;
    personaggio->tassocritico = tassocritico;
    personaggio->cooldownBuff = cooldownBuff;

    // Reset punti statistica
    personaggio->puntiStatistica = 0;

    if (vita > vitaMax){
        vitaMax = vita;
    }

    cout << "\n*** PARTITA CARICATA CON SUCCESSO! ***" << endl;
    cout << "==================================" << endl;
    cout << "Benvenuto di nuovo, " << nome << "!" << endl;
    cout << "Livello: " << livello << endl;
    cout << "Esperienza: " << esperienza << "/" << esperienzaPerLivello << endl;
    cout << "Mostri sconfitti: " << mostriSconfitti << endl;
    cout << "==================================" << endl;

    cout << "\nStato attuale del tuo eroe:" << endl;
    personaggio->stampaInformazioni();
    cout << "==================================" << endl;

    return personaggio;
}

bool esisteSalvataggio() {
    ifstream file("salvataggio.txt");
    bool esiste = file.is_open();
    if (file.is_open()) {
        file.close();
    }
    return esiste;
}
#endif // MIEFUNZIONI_H_INCLUDED

#!/bin/sh
# Soluzione schematica FCP.sh
# ATTENZIONE: il file deve avere i permessi di esecuzione per l’utente

# 1️⃣ Controllo numero parametri
case $# in
0|1|2)
    echo "Errore: numero parametri $# quindi pochi parametri. Usage: $0 G1 G2 ... C"
    exit 1
    ;;
*)
    echo "DEBUG-OK: da qui in poi proseguiamo con $# parametri"
    ;;
esac

# 2️⃣ Isoliamo l'ultimo parametro e facciamo i controlli
num=1          # contatore del ciclo sui parametri
params=        # accumula tutte le directory valide
for i
do
    if test $num -ne $#  # tutti tranne l’ultimo parametro
    then
        # Controllo se è un nome assoluto e directory traversabile
        case $i in
            /*)
                if test ! -d "$i" -o ! -x "$i"
                then
                    echo "$i non è una directory o non è attraversabile"
                    exit 2
                fi
                ;;
            esac
        # Se passa i controlli, lo aggiungo a params
        params="$params $i"
    else
        # Ultimo parametro: controllo che sia un singolo carattere
        case $i in
            ?)
                echo "DEBUG-$i singolo carattere"
                ;;
            *)
                echo "ERRORE: ultimo parametro $i NON singolo carattere"
                exit 3
                ;;
        esac
        C=$i  # variabile C come richiesto dal testo
    fi
    num=`expr $num + 1`
done

# 3️⃣ Parametri validati, possiamo procedere
PATH=`pwd`:$PATH
export PATH

for G in $params
do
    echo "DEBUG-fase per $G"
    # Invocazione ricorsiva del file comandi FCR.sh con la gerarchia e il carattere
    FCR.sh "$G" "$C"
done
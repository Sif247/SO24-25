#!/bin/sh

C="$1"
DIR="$2"

cont=0
files_validi=""

for F in "$DIR"/*
do
    [ -e "$F" ] || continue

    # --- Controllo file valido ---
    if [ -f "$F" ] && [ -r "$F" ]; then
        len=$(wc -c < "$F")
        if [ $len -gt 0 ] && [ $((len % 2)) -eq 0 ]; then
            cont=$((cont + 1))
            files_validi="$files_validi $(basename "$F")"
        fi
    fi

    # --- Controllo sottodirectory ---
    if [ -d "$F" ]; then
        basename=$(basename "$F")
        # verifica nome 3 caratteri e caratteri dispari = C
        case "$basename" in
            $C?$C) 
                # nome valido, non stampare subito, gestito alla fine
                ;;
            *) 
                echo "LA DIRECTORY CON NOME ASSOLUTO $F NON HA IL NOME GIUSTO"
                ;;
        esac

        # chiamata ricorsiva
        ./FCR.sh "$C" "$F"
    fi
done

# --- Stampa directory corrente ---
if [ $cont -gt 0 ]; then
    echo "DIRECTORY TROVATA CON NOME ASSOLUTO $DIR"
else
    echo "LA DIRECTORY CON NOME ASSOLUTO $DIR NON CONTIENE ALCUN FILE LEGGIBILE DI DIMENSIONE NON NULLA O CON LUNGHEZZA IN CARATTERI PARI!"
fi

# --- Invoca parte C sui file validi ---
if [ $cont -gt 0 ]; then
    ./parteC $files_validi
fi

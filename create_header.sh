#!/bin/bash

# Vérification du nombre d'arguments
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <Nom_du_fichier>"
    exit 1
fi

# Récupérer le nom du fichier
FILENAME=$1

# Convertir en majuscules pour les macros
UPPERCASE_FILENAME=$(echo "$FILENAME" | tr '[:lower:]' '[:upper:]')

# Créer le fichier .hpp
cat << EOF > "$FILENAME.hpp"
/*
** EPITECH PROJECT, 2025
** $FILENAME
** File description:
** $FILENAME
*/

#ifndef ${UPPERCASE_FILENAME}_HPP_
    #define ${UPPERCASE_FILENAME}_HPP_

class ${FILENAME} {
    public:
        ${FILENAME}();
        ~${FILENAME}();
    private:
};

#endif
EOF

# Créer le fichier .cpp
cat << EOF > "$FILENAME.cpp"
/*
** EPITECH PROJECT, 2025
** $FILENAME
** File description:
** $FILENAME
*/

#include "$FILENAME.hpp"

${FILENAME}::${FILENAME}()
{
}

${FILENAME}::~${FILENAME}()
{
}

EOF

echo "Les fichiers $FILENAME.hpp et $FILENAME.cpp ont été créés avec succès."
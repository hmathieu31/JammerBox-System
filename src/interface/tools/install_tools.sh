#!/bin/bash

#
# Détection de l'OS
#
ISWINDOWS=false
ISLINUX=false
ISMAC=false
if [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]];then
  ISWINDOWS=true
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
  ISLINUX=true
elif [[ "$OSTYPE" == "darwin"* ]]; then
  ISMAC=true
fi

if [[ $ISWINDOWS == false ]] && [[ $ISLINUX == false ]] && [[ $ISMAC == false ]]; then
  echo "Unsupported OS: ${OSTYPE}"
fi


#
# Installation de com0com
#

# com0com n'est disponible que pour windows
if $ISWINDOWS; then
  COM0COMFILE=com0com.zip
  # Si ça n'a pas déjà été téléchargé
  if [[ ! -f /tmp/$COM0COMFILE ]]; then
    echo "Téléchargement de com0com"

    #téléchargement de l'archive de com0com sur sourceforge
    curl -k --fail -s -L https://downloads.sourceforge.net/project/com0com/com0com/3.0.0.0/com0com-3.0.0.0-i386-and-x64-signed.zip  -o /tmp/com0com.zip
    if [ $? -ne 0 ];then
      echo "Erreur de téléchargement de com0com"
      exit 1
    fi
  fi

  # Si ça n'a pas déjà été décompressé
  if [[ ! -d /tmp/com0com ]]; then
    echo "Décompression de com0com"

    #Décompression de l'archive
    unzip -d /tmp/com0com  /tmp/com0com.zip 2>&1 >  /dev/null
    if [ $? -ne 0 ];then
      echo "Erreur décompression de com0com"
      exit 1
    fi
  fi

  echo "Voulez-vous installer com0com ? [y]es, [n]o"
  read INSTALL_COM0COM
  if [[ $INSTALL_COM0COM == "y" ]]; then
    echo "Démarrage de l'installation de com0com"

    #Vérification de la version du système, 32 ou 64 bits
    uname -a | grep "64" > /dev/null
    #Execution de l'exécutable 32 ou 64 bits
    if [ $? -ne 0 ]
    then
      start /tmp/com0com/Setup_com0com_v3.0.0.0_W7_x86_signed.exe
    else
      start /tmp/com0com/Setup_com0com_v3.0.0.0_W7_x64_signed.exe
    fi
  fi
fi

#
# Installation de Qt
#

QTFILE_LINUX=qt-opensource-linux-x64-5.12.9
QTFILE_MACOS=qt-opensource-mac-x64-5.12.9
QTFILE_WINDOWS=qt-opensource-windows-x86-5.12.9

if $ISLINUX; then
  if [[ ! -f /tmp/${QTFILE_LINUX}.run ]]; then
    echo "Téléchargement de Qt"
    curl -k --fail -L https://download.qt.io/official_releases/qt/5.12/5.12.9/${QTFILE_LINUX}.run > /tmp/${QTFILE_LINUX}.run
  fi
elif $ISMAC; then
  if [[ ! -f /tmp/${QTFILE_MACOS}.dmg ]]; then
    echo "Téléchargement de Qt"
    curl -k -L https://download.qt.io/official_releases/qt/5.12/5.12.9/${QTFILE_MACOS}.dmg > /tmp/${QTFILE_MACOS}.dmg
  fi
elif $ISWINDOWS; then
  if [[ ! -f /tmp/${QTFILE_WINDOWS}.exe ]]; then
    echo "Téléchargement de Qt"
    curl -k --fail -L https://download.qt.io/official_releases/qt/5.12/5.12.9/${QTFILE_WINDOWS}.exe > /tmp/${QTFILE_WINDOWS}.exe
  fi
fi
if [ $? -ne 0 ];then
  echo "Erreur de téléchargement de Qt"
  exit 1
fi

echo "Voulez-vous installer Qt5 ? [y]es, [n]o"
read INSTALL_QT
if [[ $INSTALL_QT == "y" ]]; then
  if $ISLINUX; then
    echo "Installation de Qt"
    echo "Veuillez suivre les instructions de l'installeur Qt"
  
    chmod +x /tmp/${QTFILE_LINUX}.run
    sudo /tmp/${QTFILE_LINUX}.run
    if [[ $? -ne 0 ]]; then
      echo "L'installation de Qt a échoué"
      exit 1
    fi
  elif $ISMAC; then
    echo "Montage du drive de Qt"
  
    open /tmp/${QTFILE_MACOS}.dmg
    while [ ! -d /Volumes/${QTFILE_MACOS} ]; do
      sleep 1
    done

    echo "Installation de Qt"
    echo "Veuillez suivre les instructions de l'installeur Qt"
    open /Volumes/${QTFILE_MACOS}/${QTFILE_MACOS}.app
  elif $ISWINDOWS; then
    echo "Installation de Qt"
    echo "Veuillez suivre les instructions de l'installeur Qt"
  
    start /tmp/${QTFILE_WINDOWS}.exe

    echo "Définition des variables d'environement necessaires"
    # Les DLLs doivent être dans le path pour lancer l'executable
    echo "export PATH=\$PATH:C:/Qt/Qt5.12.9/5.12.9/mingw73_64/bin" >> ~/.bashrc
    # La variable QT_PLUGIN_PATH doit pointer sur l'installation de Qt
    echo "export QT_PLUGIN_PATH=C:/Qt/Qt5.12.9/5.12.9/mingw73_64/plugins" >> ~/.bashrc
  fi
fi

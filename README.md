# Projet_Liseuse

Un fichier .cbr sont des archies.rar contenant des images sous formes GIF, JPEG, PNG, BMP
Donc première étape : ouvrir l'archive
Deuxième étape : lire les images. On se balade dans le fichier et on ouvre les images les unes
après les autres. (pour le traitement d'image, librairie Magick++/ImageMagick)

Librairie de gestion de .zip et .rar directement sur la bibliothèque graphique wxWidgets.

1. Analyse des formats de base des différents fichiers au format .cbr et/ou .cbz (formats obligatoires: .jpg, .bmp, .png)

Formats sans perte de qualité : BMP, GIF, PNG

Format avec perte de qualité : JPEG

- BMP : lisible pas tous les programmes d'images. Ne dégrade pas la qualité car non compressé => images lourdes
- GIF : format compressé mais sans perte de qualité, images animées, gère la transparence
- PNG : pas de perte de qualité et gère la transparence en fonds
- JPG/JPEG : pas lourd, l’image se dégrade au fur et à mesure de la compression. Ce type d’image ne supporte également guère l’agrandissement au risque d’obtenir une image qui n’est pas nette, où vous pouvez même distinguer les pixels.

2. Algorithmes de redimensionnement d'images 

On va devoir utiliser l'interface graphique pour ouvrir les images après les avoir redimensionnées.

Il existe plusieurs algo pour redimensionner une image. Globalement pour l'agrandir il suffit
de déteriminer la couleur des nouveaux pixels (en prenant la même que celle d'à côté par exmple).
Pour réduire l'image par n, il suffit de prendre la moyenne des pixels de n en n.

https://clouard.users.greyc.fr/Pantheon/experiments/rescaling/index-fr.html#nearest

-> Si il faut redimensionner avec des proportions de dimensions différentes de l'image de base, algo de seam carving (redimensionne selon les zones d'importance avec la programmation dynamique) => seulement si on a le temps http://igm.univ-mlv.fr/~dr/XPOSE2012/La%20programmation%20dynamique/seamcarving.html


-> En fait sur le site du prof y a un truc : https://perso.ensta-paris.fr/~bmonsuez/Cours/doku.php?id=in204:cpp#redimensionnement_d_une_image

3. Interfaces

-> relier CMake et wxWidgets : https://docs.wxwidgets.org/trunk/overview_cmake.html
-> pour désarchiver sans wxWidgets : libarchive (chez Laura ça marchait pas)

## POUR COMPILER

cd build
cmake ..
make
./Dezip

## Travail effectué

Création des fichiers win (fenêtre d'affichage) et appli (fonction principale pour l'affichage).
Chargé et affiché les images du dossier image selon la valeur d'un indice i. Pour l'instant tout 
est dans le win.cpp il faudrait créer une fonction.

Prochain objectif : relier le tout à la fonction dezip, creer les boutons pour tourner les pages et
faire en sorte que ça modifie i et l'affichage.
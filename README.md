# Projet_Liseuse

Un fichier .cbr sont des archies.rar contenant des images sous formes GIF, JPEG, PNG, BMP
Donc première étape : ouvrir l'archive
Deuxième étape : lire les images. On se balade dans le fichier et on ouvre les images les unes
après les autres.

On va devoir utiliser l'interface graphique pour ouvrir les images après les avoir redimensionnées.

Il existe plusieurs algo pour redimensionner une image. Globalement pour l'agrandir il suffit
de déteriminer la couleur des nouveaux pixels (en prenant la même que celle d'à côté par exmple).
Pour réduire l'image par n, il suffit de prendre la moyenne des pixels de n en n.

https://clouard.users.greyc.fr/Pantheon/experiments/rescaling/index-fr.html#nearest
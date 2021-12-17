Désarchivage : wxZipInputStream / wxFFileInputStream      #include <wx/wfstream.h> et #include <wx/zipstrm.h>
- https://docs.wxwidgets.org/trunk/overview_archive.html
- Input : pour dé-ziper    (Output : pour créer une archive)

-----------------------------------

Barre d'outils : wxToolBar

-----------------------------------

Fenêtre : wxFrame     #include <wx/frame.h>
- fenêtre globale wxWidgets, classe Frame à créer en public wxFrame, en paramètre pour gérer les événements

Fenêtre : wxBoxSizer    #include <wx/sizer.h>
- forme de l'écran (option WXVERTICAL)

-----------------------------------

Evenements : wxBEGIN_EVENT_TABLE / EVT_MENU / wxEND_EVENT_TABLE / wxIMPLEMENT_APP   #include <wx/menu/h>
- dans le main 
- les EVT_MENU créent les différents éléments qui pourront être cliqués sur l'interface

-----------------------------------

Chaînes de caractères : wxString    #include <wx/string.h>

#include"win.hpp"
#include <memory>
#include <vector>
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <iostream>
#include <wx/artprov.h>

// Variables globales
std::vector<wxString> vectImages;    //vecteur contenant les images à lire
size_t i = 0;                        //Indice qui parcourt les images d'un dossier
size_t n = 0;                        //Nombre d'élement d'un dossier (nombre de pages d'une BD)

Win::Win(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
  //Création de la bar Menu
  menubar = new wxMenuBar;
  menu = new wxMenu;
  menu->Append(1, wxT("&Lire"));
  menu->Append(10, wxT("&Dezip"));
  menubar->Append(menu, wxT("&Menu"));
  SetMenuBar(menubar);

  Connect(1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Win::OnLire));
  Connect(10, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Win::OnDezip));
  Centre();

  //Création de la Toolbar
  wxToolBar *toolbar = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_BOTTOM);
  toolbar->AddStretchableSpace();

  //Zoom et Dezoom
  wxBitmap imageZoom = wxArtProvider::GetBitmap(wxART_PLUS);
  wxToolBarToolBase *imageZoomTool = toolbar->AddTool(-1, wxT("Image zoom"), imageZoom);
  Connect(imageZoomTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnZoom));

  wxBitmap imageDezoom = wxArtProvider::GetBitmap(wxART_MINUS);
  wxToolBarToolBase *imageDezoomTool = toolbar->AddTool(-1, wxT("Image dezoom"), imageDezoom);
  Connect(imageDezoomTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnDezoom));

  //Image précédente et Image suivante
  wxBitmap imagePrec = wxArtProvider::GetBitmap(wxART_GO_BACK);
  wxToolBarToolBase *imagePrecTool = toolbar->AddTool(-1, wxT("Image precedente"), imagePrec);
  Connect(imagePrecTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnPrec));

  wxBitmap imageSuiv = wxArtProvider::GetBitmap(wxART_GO_FORWARD);
  wxToolBarToolBase *imageSuivTool = toolbar->AddTool(-1, wxT("Image suivante"), imageSuiv);
  Connect(imageSuivTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnSuiv));

  toolbar->Realize();
  this->SetToolBar(toolbar);

  //Création de la fenêtre qui permet l'affichage de l'image avec possibilité de scroller
  sw = new wxScrolledWindow(this);
}


//Méthode qui permet de lire la première image du dossier dans lequel elle est et de charger en mémoire toutes les images du dossier
void Win::OnLire(wxCommandEvent& WXUNUSED(event))
{
  wxInitAllImageHandlers();       //Permet de gérer tous les types d'image

  //On ne choisit que des images que l'on peut afficher
  wxFileDialog dialog(sw, wxT("Lire"),"", "", "Fichiers (*.jpg;*.jpeg;*.png;*.bmp;*.gif)|*.jpg;*.jpeg;*.png;*.bmp;*.gif", wxFD_OPEN |wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_CANCEL)
  {
    return;
  }

  wxString filePath = dialog.GetDirectory();
  wxDir dir(filePath);
  wxString filename;
  bool still = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

  vectImages.clear();

  //On charge le nom des images dans le vecteur pour les avoir toutes disponibles
  while (still)
  {
    //On vérifie les extensions pour être sur que ce soit une image
    wxFileName fname(filePath, filename);
    const wxString &ext = fname.GetExt();
    if (ext == wxT("png") || ext == wxT("jpg") || ext == wxT("jpeg") || ext == wxT("bmp") || ext == wxT("gif"))
    {
      vectImages.push_back(dir.GetNameWithSep() + filename);
      n++;
    }
    still = dir.GetNext(&filename);
  }

  //On récupère la 1ère image
  wxString &imageName = vectImages.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);


  //Si tout se passe bien on l'affiche
  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400); //Choix de la taille de départ arbitraire (relative à la taille de la fenêtre initiale)

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG); //On créé le bitmap à partir de l'image
    sb = new wxStaticBitmap(sw, -1, bmp); //On créé le staticbitmap qui permet l'affichage
    
    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10); //Les Scrollbars sont dépendantes de la taille de l'image
  }
  
}


//Méthode qui demande à l'utilisateur de choisir une archive et qui déarchive son contenu dans un dossier image créé au préalable
void Win::OnDezip(wxCommandEvent& WXUNUSED(event))
{
  //On autorise que les fichiers que l'on peut dezipper
  wxFileDialog dialog(sw, wxT("Ouvrir une archive"),"", "", "Archives (*.zip;*.cbz)|*.zip;*.cbz;", wxFD_OPEN |wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_CANCEL)
  {
    return;
  }

  std::unique_ptr<wxZipEntry> entry;
  wxFFileInputStream in(dialog.GetPath());
  wxZipInputStream zip(in);

  //Tant que le dossier n'est pas vide on récupère le fichier, et on l'envoie dans le nouveau dossier image
  while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
  {
      wxString name = entry->GetName();
      wxString strTargetDir = "../image";
      wxString strFileName = strTargetDir + wxFileName::GetPathSeparator() + name;
      wxFileOutputStream file(strFileName);
      zip.Read(file);
  }

  //On annonce à l'utilisateur que le dezip est terminé
  wxMessageDialog message(sw, "", "Info", wxOK );
  message.SetMessage(wxT("Dezip terminé, les fichiers sont dans le dossier image !"));
  message.ShowModal();
}



//Méthode qui affiche l'image précédente dans le dossier image
void Win::OnPrec(wxCommandEvent& WXUNUSED(event))
{
  //On vérifie qu'il y a bien des images à afficher
  if (vectImages.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }

  //On verifie où en est le compteur pour ne pas être "out of range"
  if (i>0)
  {
    i--;
  }
  else
  {
    i=n-1;
  }

  //On récupère l'image correspondante au compteur i
  wxString &imageName = vectImages.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  // Si tout est ok on l'affiche
  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400);

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
    sb->SetBitmap(bmp);

    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
  else
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Problème de chargement de l'image"));
    message.ShowModal();
  }
}

//Méthode similaire à la précédente, cette fois on affiche l'image suivante
void Win::OnSuiv(wxCommandEvent& WXUNUSED(event))
{
  //On vérifie qu'il y a bien des images à afficher
  if (vectImages.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }

  //On verifie où en est le compteur pour ne pas être "out of range"
  if (i<n-1)
  {
    i++;
  }
  else
  {
    i=0;
  }

  //On récupère l'image correspondante au compteur i
  wxString &imageName = vectImages.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  // Si tout est ok on l'affiche
  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400);

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
    sb->SetBitmap(bmp);

    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
  else
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Problème de chargement de l'image"));
    message.ShowModal();
  }
}



//Méthode qui Zoom sur l'image affiché actuellement
void Win::OnZoom(wxCommandEvent& WXUNUSED(event))
{
  //On vérifie qu'il y a bien une image sur laquelle zoomer
  if (vectImages.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }

  //On récupère la taille de l'image actuellement affichée
  wxBitmap bmpData = sb->GetBitmap();
  wxImage imageData = bmpData.ConvertToImage();
  int widthI = imageData.GetWidth();
  int heightI = imageData.GetHeight();

  //On récupère l'image d'origine grâce à l'indice i
  //On utilise l'image d'origine pour augmenter la qualité qui se perd au fil des zoom et dezoom
  wxString &imageName = vectImages.at(i);

  std::shared_ptr<wxImage> imageRescale = std::make_shared<wxImage>();
  bool test = imageRescale->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  //Si tout est ok on la redimensionne et on l'affiche
  if (imageRescale->IsOk() && test)
  {
    //On zoom x2 sur la taille actuelle de l'image
    imageRescale->Rescale(widthI*2, heightI*2);

    wxBitmap bmpRescale(*imageRescale, wxBITMAP_TYPE_JPEG);
    sb->SetBitmap(bmpRescale);

    int widthB = bmpRescale.GetWidth();
    int heightB = bmpRescale.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
}

//Méthode de Dezoom similaire à la précédente
void Win::OnDezoom(wxCommandEvent& WXUNUSED(event))
{
  //On vérifie qu'il y a bien une image sur laquelle zoomer
  if (vectImages.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }

  //On récupère la taille de l'image actuellement affichée
  wxBitmap bmpData = sb->GetBitmap();
  wxImage imageData = bmpData.ConvertToImage();
  int widthI = imageData.GetWidth();
  int heightI = imageData.GetHeight();

  //On récupère l'image d'origine grâce à l'indice i
  //On utilise l'image d'origine pour augmenter la qualité qui se perd au fil des zoom et dezoom
  wxString &imageName = vectImages.at(i);

  std::shared_ptr<wxImage> imageRescale = std::make_shared<wxImage>();
  bool test = imageRescale->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  //Si tout est ok on la redimensionne et on l'affiche
  if (imageRescale->IsOk() && test)
  {
    //On Dezoom /2 par rapport à la taille actuelle de l'image
    imageRescale->Rescale(widthI/2, heightI/2);

    wxBitmap bmpRescale(*imageRescale, wxBITMAP_TYPE_JPEG);
    sb->SetBitmap(bmpRescale);

    int widthB = bmpRescale.GetWidth();
    int heightB = bmpRescale.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
}

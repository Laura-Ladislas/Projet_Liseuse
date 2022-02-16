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


std::vector<wxString> m_imageNoms;
size_t i = 0;
size_t n = 0;
wxDir dir("../image");
wxString filename;
wxScrolledWindow *sw;

Win::Win(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{

  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(ID_Lire, wxT("&Lire"));
  file->Append(ID_Dezip, wxT("&Dezip"));
  menubar->Append(file, wxT("&Menu"));
  SetMenuBar(menubar);

  Connect(ID_Lire, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(Win::OnLire));
  Connect(ID_Dezip, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(Win::OnDezip));
  Centre();

  wxToolBar *toolbar =
        new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_BOTTOM);


    toolbar->AddStretchableSpace();

    // Icone image precedente
    wxBitmap prevImageBitmap = wxArtProvider::GetBitmap(wxART_GO_BACK);
    wxToolBarToolBase *prevImage = toolbar->AddTool(-1, wxT("Image precedente"), prevImageBitmap);
    Connect(prevImage->GetId(), wxEVT_COMMAND_TOOL_CLICKED,
wxCommandEventHandler(Win::OnPrev));

    // Icone image suivante
    wxBitmap nextImageBitmap = wxArtProvider::GetBitmap(wxART_GO_FORWARD);
    wxToolBarToolBase *nextImage = toolbar->AddTool(-1, wxT("Image suivante"), nextImageBitmap);
    Connect(nextImage->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnNext));

    toolbar->Realize();
    this->SetToolBar(toolbar);

    sw = new wxScrolledWindow(this);
}

void Win::OnLire(wxCommandEvent& WXUNUSED(event))
{
  wxImage::AddHandler(new wxJPEGHandler);

  const wxString &currentDir = wxGetCwd();
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
  while (cont)
  {
    wxFileName fname(currentDir, filename);
    const wxString &ending = fname.GetExt();
    m_imageNoms.push_back(dir.GetNameWithSep() + filename);
    cont = dir.GetNext(&filename);
    n++;
  }
  wxString &imageName = m_imageNoms.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool loadOk = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}

void Win::OnDezip(wxCommandEvent& WXUNUSED(event))
{
  std::unique_ptr<wxZipEntry> entry;
  wxFFileInputStream in(wxT("test.cbz"));
  wxZipInputStream zip(in);

  //Parcourt tous les élements de l'archive et les extrait tend qu'elle est pas vide
  while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
  {
      // access meta-data
      wxString name = entry->GetName();
      //Les images vont dans ce dossier qu'on aura créer au préalable
      wxString strTargetDir = "../image";
      wxString strFileName = strTargetDir + wxFileName::GetPathSeparator() + name;

      // Ne sert pas à dezipper, sert à gérer si c'est un fichier ou un dossier
      /*wxFileName new_file;
      // read 'zip' to access the entry's data
      if (entry->IsDir())
      {
        //Ajouter des affichages pour comprendre ce qu'il se passe et si le strFileName est bien créer
        new_file.AssignDir(strFileName);
      }
      else
      {
          new_file.Assign(strFileName);
      }*/

      //strFileName doit contenir le path du dossier dans lequel on veut read (donc extraire) nos fichiers
      wxFileOutputStream file(strFileName);
      zip.Read(file);
  }
}

void Win::OnPrev(wxCommandEvent& WXUNUSED(event))
{
  if (i>0)
  {
    i--;
  }
  else
  {
    i=n-1;
  }
  wxString &imageName = m_imageNoms.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool loadOk = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}

void Win::OnNext(wxCommandEvent& WXUNUSED(event))
{
  if (i<n-1)
  {
    i++;
  }
  else
  {
    i=0;
  }
  wxString &imageName = m_imageNoms.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool loadOk = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}
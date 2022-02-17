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
wxScrolledWindow *sw;
wxStaticBitmap *sb;

Win::Win(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(ID_Lire, wxT("&Lire"));
  file->Append(ID_Dezip, wxT("&Dezip"));
  menubar->Append(file, wxT("&Menu"));
  SetMenuBar(menubar);

  Connect(ID_Lire, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Win::OnLire));
  Connect(ID_Dezip, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Win::OnDezip));
  Centre();

  wxToolBar *toolbar = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_BOTTOM);
  toolbar->AddStretchableSpace();

  wxBitmap imageZoom = wxArtProvider::GetBitmap(wxART_PLUS);
  wxToolBarToolBase *imageZoomTool = toolbar->AddTool(-1, wxT("Image zoom"), imageZoom);
  Connect(imageZoomTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnZoom));

  wxBitmap imagePrec = wxArtProvider::GetBitmap(wxART_GO_BACK);
  wxToolBarToolBase *imagePrecTool = toolbar->AddTool(-1, wxT("Image precedente"), imagePrec);
  Connect(imagePrecTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnPrec));

  wxBitmap imageSuiv = wxArtProvider::GetBitmap(wxART_GO_FORWARD);
  wxToolBarToolBase *imageSuivTool = toolbar->AddTool(-1, wxT("Image suivante"), imageSuiv);
  Connect(imageSuivTool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Win::OnSuiv));

  toolbar->Realize();
  this->SetToolBar(toolbar);

  sw = new wxScrolledWindow(this);
}

void Win::OnLire(wxCommandEvent& WXUNUSED(event))
{
  wxInitAllImageHandlers();

  wxFileDialog dialog(sw, wxT("Lire"),"", "", "Fichiers (*.jpg;*.jpeg;*.png;*.bmp;*.gif)|*.jpg;*.jpeg;*.png;*.bmp;*.gif", wxFD_OPEN |wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_CANCEL)
  {
    return;
  }
  wxString filePath = dialog.GetDirectory();

  wxDir dir(filePath);
  const wxString &currentDir = dir.GetName();
  wxString filename;
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
  while (cont)
  {
    wxFileName fname(currentDir, filename);
    const wxString &ext = fname.GetExt();
    if (ext == wxT("png") || ext == wxT("jpg") || ext == wxT("jpeg") || ext == wxT("bmp") || ext == wxT("gif"))
    {
      m_imageNoms.push_back(dir.GetNameWithSep() + filename);
      n++;
    }
    cont = dir.GetNext(&filename);
  }
  wxString &imageName = m_imageNoms.at(i);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400);

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
    sb = new wxStaticBitmap(sw, -1, bmp);

    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
  
}

void Win::OnDezip(wxCommandEvent& WXUNUSED(event))
{
  wxFileDialog dialog(sw, wxT("Ouvrir une archive"),"", "", "Archives (*.zip;*.cbz)|*.zip;*.cbz;", wxFD_OPEN |wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_CANCEL)
  {
    return;
  }

  std::unique_ptr<wxZipEntry> entry;
  wxFFileInputStream in(dialog.GetPath());
  wxZipInputStream zip(in);

  while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
  {
      wxString name = entry->GetName();
      wxString strTargetDir = "../image";
      wxString strFileName = strTargetDir + wxFileName::GetPathSeparator() + name;
      wxFileOutputStream file(strFileName);
      zip.Read(file);
  }
  wxMessageDialog message(sw, "", "Info", wxOK );
  message.SetMessage(wxT("Dezip terminé, les fichiers sont dans le dossier image !"));
  message.ShowModal();
}

void Win::OnPrec(wxCommandEvent& WXUNUSED(event))
{
  if (m_imageNoms.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }
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
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400);

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
    sb = new wxStaticBitmap(sw, -1, bmp);

    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
}

void Win::OnSuiv(wxCommandEvent& WXUNUSED(event))
{
  if (m_imageNoms.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }
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
  bool test = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);

  if (image->IsOk() && test)
  {
    int widthI = image->GetWidth();
    int heightI = image->GetHeight();
    image->Rescale(widthI*400/heightI, 400);

    wxBitmap bmp(*image, wxBITMAP_TYPE_JPEG);
    sb = new wxStaticBitmap(sw, -1, bmp);

    int widthB = bmp.GetWidth();
    int heightB = bmp.GetHeight();

    sw->SetScrollbars(10, 10, widthB/10, heightB/10);
  }
}

void Win::OnZoom(wxCommandEvent& WXUNUSED(event))
{
  if (m_imageNoms.empty())
  {
    wxMessageDialog message(sw, "", "Info", wxOK );
    message.SetMessage(wxT("Cliquez sur Lire pour choisir une BD"));
    message.ShowModal();
    return;
  }

  wxBitmap bmp = sb->GetBitmap();
  wxImage image = bmp.ConvertToImage();

  int widthI = image.GetWidth();
  int heightI = image.GetHeight();
  std::cout<<heightI<<std::endl;
  image.Rescale(widthI*2, heightI*2);

  wxBitmap bmp2(image, wxBITMAP_TYPE_JPEG);
  sb = new wxStaticBitmap(sw, -1, bmp2);

  int widthB = bmp2.GetWidth();
  int heightB = bmp2.GetHeight();

  sw->SetScrollbars(10, 10, widthB/10, heightB/10);
}

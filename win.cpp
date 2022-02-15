#include"win.hpp"
#include <memory>
#include <vector>
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>


std::vector<wxString> m_imageNoms;
size_t i = 0;
size_t n = 0;
wxDir dir("../image");
wxString filename;

/*ScrWindow::ScrWindow(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
  wxImage::AddHandler(new wxJPEGHandler);
  wxScrolledWindow *sw = new wxScrolledWindow(this);

  //std::vector<wxString> m_imageNoms;
  //wxDir dir("../image");
  //wxString filename;
  const wxString &currentDir = wxGetCwd();
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
  //size_t i = 0;
  //size_t n = 0;
  while (cont)
  {
    wxFileName fname(currentDir, filename);
    const wxString &ending = fname.GetExt();
    m_imageNoms.push_back(dir.GetNameWithSep() + filename);
    cont = dir.GetNext(&filename);
    n++;
  }

  wxString &imageName = m_imageNoms.at(1);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool loadOk = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);
  wxBitmap bmp(*image, wxBITMAP_SCREEN_DEPTH);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}*/

SimpleMenu::SimpleMenu(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{

  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(wxID_EXIT, wxT("&Lire"));
  menubar->Append(file, wxT("&File"));
  SetMenuBar(menubar);

  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(SimpleMenu::OnLire));
  Centre();

}

void SimpleMenu::OnLire(wxCommandEvent& WXUNUSED(event))
{
  i++;
  wxImage::AddHandler(new wxJPEGHandler);
  wxScrolledWindow *sw = new wxScrolledWindow(this);

  //std::vector<wxString> m_imageNoms;
  //wxDir dir("../image");
  //wxString filename;
  const wxString &currentDir = wxGetCwd();
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
  //size_t i = 0;
  //size_t n = 0;
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
  wxBitmap bmp(*image, wxBITMAP_SCREEN_DEPTH);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}

/*BEGIN_EVENT_TABLE(MyButton, wxFrame)
    EVT_BUTTON(wxID_EXIT,  MyButton::OnLire)
END_EVENT_TABLE()*/
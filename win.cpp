#include"win.hpp"
#include <memory>
#include <vector>
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>

ScrWindow::ScrWindow(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
  wxImage::AddHandler(new wxJPEGHandler);
  wxScrolledWindow *sw = new wxScrolledWindow(this);

  std::vector<wxString> m_imageNoms;
  wxDir dir("../image");
  wxString filename;
  const wxString &currentDir = wxGetCwd();
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
  size_t i = 0;
  size_t n = 0;
  while (cont)
  {
    wxFileName fname(currentDir, filename);
    const wxString &ending = fname.GetExt();
    m_imageNoms.push_back(dir.GetNameWithSep() + filename);
    cont = dir.GetNext(&filename);
    n++;
  }

  wxString &imageName = m_imageNoms.at(4);

  std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
  bool loadOk = image->LoadFile(imageName, wxBITMAP_TYPE_ANY);
  wxBitmap bmp(*image, wxBITMAP_SCREEN_DEPTH);
  //wxBitmap bmp(wxT("test.jpg"), wxBITMAP_TYPE_JPEG);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

  sw->SetScrollbars(10, 10, width/10, height/10);
  sw->Scroll(50,10);

  Center();
}

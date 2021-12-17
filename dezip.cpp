#include <wx/wx.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <iostream>
#include <memory>

int main()
{
	std::auto_ptr<wxZipEntry> entry;
	wxFFileInputStream in(wxT("test.cbz"));
	wxZipInputStream zip(in);

	while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
	{
	    // access meta-data
	    wxString name = entry->GetName();
	    wxFileName new_file;
	    // read 'zip' to access the entry's data
	    if (entry->IsDir())
	    {
	    	new_file.AssignDir(name);
	    }
	    else
	    {
	        new_file.Assign(name);
	    }

	    wxFileOutputStream file(name);
	    zip.Read(file);
	}
	return 0;
}

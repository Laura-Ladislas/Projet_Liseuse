#include <wx/wx.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	std::auto_ptr<wxZipEntry> entry;
	wxFFileInputStream in(wxT("test.cbz"));
	wxZipInputStream zip(in);

	//Parcourt tous les élements de l'archive et les extrait tend qu'elle est pas vide
	while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
	{
	    // access meta-data
	    wxString name = entry->GetName();
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
	return 0;
}


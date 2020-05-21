#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

//#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
//#include <wx/colourdata.h>
//#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <wx/rawbmp.h>

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void UpdateUI( wxUpdateUIEvent& event );
		void m_cb_Kontur_Click( wxCommandEvent& event );
		void m_cb_Mapa_Click( wxCommandEvent& event );
		void m_tb_function_1_click( wxCommandEvent& event );
		void m_tb_function_2_click( wxCommandEvent& event );
		void m_tb_function_3_click( wxCommandEvent& event );
		void m_tb_function_4_click( wxCommandEvent& event );
		void m_s_ile_poziomic_scroll( wxScrollEvent& event );
		void m_tb_pokaz_punkty_toggle( wxCommandEvent& event );
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members
  wxBitmap MemoryBitmap;
  wxImage image;
  float   FunctionData[100][3];
  int     NoLevels = 5, ColoringType = 0, NoPoints = 4;
  bool    ContourFlag = true;
  bool    ShowPoints = false;
  void PrepareData(int fun);
  void DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints);
  void Repaint();

};

#endif // __GUIMyFrame1__

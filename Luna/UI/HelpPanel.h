#pragma once

#include "LunaGenerated.h"

namespace Luna
{
    class HelpPanel : public HelpPanelGenerated
    {
    public:
        HelpPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL );

        void SetText( const tchar* text );
    };
}

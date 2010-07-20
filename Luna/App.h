#pragma once

#include "Platform/Compiler.h"
#include "Foundation/InitializerStack.h"

#include "UI/MainFrame.h"
#include "DocumentManager.h"
#include "Vault/Vault.h"

#include <wx/app.h>
#include <wx/xrc/xmlres.h>

namespace Luna
{
    class App : public wxApp
    {
    public:
        App();
        ~App();

        virtual bool    OnInit() NOC_OVERRIDE;
        virtual int     OnRun() NOC_OVERRIDE;
        virtual int     OnExit() NOC_OVERRIDE;
        virtual void    OnAssertFailure(const wxChar *file, int line, const wxChar *func, const wxChar *cond, const wxChar *msg) NOC_OVERRIDE;

        DocumentManager& GetDocumentManager()
        {
            return m_DocumentManager;
        }

        MainFrame* GetFrame()
        {
            if ( !m_Frame )
            {
                m_Frame = new MainFrame();
            }
            return m_Frame;
        }

        Vault& GetVault()
        {
            if ( !m_Vault )
            {
                m_Vault = new Vault();
            }
            return *m_Vault;
        }

    protected:
        Nocturnal::InitializerStack m_InitializerStack;
        DocumentManager m_DocumentManager;
        Vault* m_Vault;

        MainFrame* m_Frame;

    };

    DECLARE_APP( App );
}
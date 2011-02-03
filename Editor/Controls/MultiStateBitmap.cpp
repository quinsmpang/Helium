#include "Precompile.h"
#include "MultiStateBitmap.h"

#include "Editor/ArtProvider.h"
#include "Foundation/Flags.h"

using namespace Helium;
using namespace Helium::Editor;


///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( MultiStateBitmap, wxStaticBitmap );

MultiStateBitmap::MultiStateBitmap()
: wxStaticBitmap()
, m_CurrentState( wxButtonBase::State_Normal )
{
    Initialize();
}

MultiStateBitmap::MultiStateBitmap( wxWindow *parent, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style )
: wxStaticBitmap( parent, wxID_ANY, label, pos, size, style )
, m_CurrentState( wxButtonBase::State_Normal )
{
    Initialize();
}

MultiStateBitmap::MultiStateBitmap( wxWindow *parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
: wxStaticBitmap( parent, id, label, pos, size, style, name )
, m_CurrentState( wxButtonBase::State_Normal )
{
    Initialize();
}

MultiStateBitmap::~MultiStateBitmap()
{
    Cleanup();
}

void MultiStateBitmap::Initialize()
{
    for ( int32_t state = 0; state < wxButton::State_Max; state++ )
    {
        m_Bitmaps[state] = NULL;
        m_WasStateSetByUser[state] = false;
    }

    m_Bitmaps[m_CurrentState] = new wxBitmap( GetBitmap() );
}

void MultiStateBitmap::Cleanup()
{
    wxStaticBitmap::Free();

    for ( int32_t state = 0; state < wxButton::State_Max; state++ )
    {
        if ( m_Bitmaps[state] )
        {
            delete m_Bitmaps[state];
            m_Bitmaps[state] = NULL;
        }
    }
}

void MultiStateBitmap::RefreshBitmapFromState()
{
    wxButtonBase::State state = IsEnabled() ? m_CurrentState : wxButtonBase::State_Disabled;
    SetImage( m_Bitmaps[state] );
    Refresh();
}

bool MultiStateBitmap::Enable( bool enable )
{
    bool result = __super::Enable( enable );
    if ( result )
    {
        RefreshBitmapFromState();
    }
    return result;
}

void MultiStateBitmap::SetState( wxButtonBase::State state )
{
    if ( state != m_CurrentState )
    {
        m_CurrentState = state;
        RefreshBitmapFromState();
    }
}

wxButtonBase::State MultiStateBitmap::GetState() const
{
    return m_CurrentState;
}

void MultiStateBitmap::SetBitmap( const wxBitmap& bitmap )
{
    SetBitmap( bitmap, wxButtonBase::State_Normal );
}

//void MultiStateBitmap::SetIcon( const wxIcon& icon )
//{
//    SetBitmap( icon, wxButtonBase::State_Normal );
//}

// See also: wxButton::DoSetBitmap and wxBitmapButton::DoSetBitmap
void MultiStateBitmap::SetBitmap( const wxBitmap& bitmap, wxButtonBase::State state )
{
    if ( bitmap.IsOk() )
    {
        DoSetBitmap( bitmap, state );

        switch ( state )
        {
            default:
                // nothing special to do but include the default clause to
                // suppress gcc warnings
                //HELIUM_ASSERT();
                break;

            case wxButtonBase::State_Normal:
                m_WasStateSetByUser[wxButtonBase::State_Normal] = true;
#if wxUSE_IMAGE
                if ( !m_WasStateSetByUser[wxButtonBase::State_Disabled] )
                {
                    wxImage disabledImage( bitmap.ConvertToImage().ConvertToGreyscale() );
                    DoSetBitmap( disabledImage, wxButtonBase::State_Disabled );
                }
#endif // wxUSE_IMAGE
                break;

            case wxButtonBase::State_Current:
                m_WasStateSetByUser[wxButtonBase::State_Current] = true;
                break;

            case wxButtonBase::State_Pressed:
                m_WasStateSetByUser[wxButtonBase::State_Pressed] = true;
                break;

            case wxButtonBase::State_Disabled:
                m_WasStateSetByUser[wxButtonBase::State_Disabled] = true;
                break;

            case wxButtonBase::State_Focused:
                m_WasStateSetByUser[wxButtonBase::State_Focused] = true;

                // if the focus bitmap is specified but current one isn't, use
                // the focus bitmap for hovering as well if this is consistent
                // with the current Windows version look and feel
                //
                // rationale: this is compatible with the old wxGTK behaviour
                // and also makes it much easier to do "the right thing" for
                // all platforms (some of them, such as Windows XP, have "hot"
                // buttons while others don't)
                if ( !m_WasStateSetByUser[wxButtonBase::State_Current] )
                {
                    DoSetBitmap( bitmap, wxButtonBase::State_Current );
                }
                break;
        }
    }
}

// See also: wxButton::DoSetBitmap and wxBitmapButton::DoSetBitmap
void MultiStateBitmap::DoSetBitmap( const wxBitmap& bitmap, wxButtonBase::State state )
{
    if ( m_Bitmaps[state] )
    {
        *m_Bitmaps[state] = bitmap;
    }
    else
    {
        m_Bitmaps[state] = new wxBitmap( bitmap );
    }
    //MakeOwnerDrawn();

    // it should be enough to only invalidate the best size when the normal
    // bitmap changes as all bitmaps assigned to the button should be of the
    // same size anyhow
    if ( state == wxButtonBase::State_Normal )
    {
        InvalidateBestSize();
    }

    RefreshBitmapFromState();
}

wxBitmap MultiStateBitmap::GetBitmap( wxButtonBase::State state ) const
{
    return m_Bitmaps[state] ? wxBitmap( *m_Bitmaps[state] ) : wxBitmap();
}

#pragma once

#include "baseviewmodel_shared.h"

#include "weapons/zmr_base.h"

#ifdef CLIENT_DLL
#define CZMViewModel C_ZMViewModel
#endif

class CZMViewModel : public CBaseViewModel
{
public:
    DECLARE_CLASS( CZMViewModel, CBaseViewModel );
    DECLARE_NETWORKCLASS();
#ifdef CLIENT_DLL
    DECLARE_PREDICTABLE();
#endif

    CZMViewModel();
    ~CZMViewModel();

#ifdef CLIENT_DLL
    virtual int                 CalcOverrideModelIndex() OVERRIDE;
    virtual CStudioHdr*         OnNewModel() OVERRIDE;
    virtual int                 DrawModel( int flags ) OVERRIDE;
    virtual bool                ShouldReceiveProjectedTextures( int flags ) OVERRIDE;
    virtual C_BaseAnimating*    FindFollowedEntity() OVERRIDE;

    virtual void                UpdateClientSideAnimation() OVERRIDE;

    virtual bool                ShouldPredict() OVERRIDE;
    virtual bool                Interpolate( float currentTime ) OVERRIDE;

    CZMBaseWeapon* GetWeapon() const { return static_cast<CZMBaseWeapon*>( CBaseViewModel::GetWeapon() ); }


    bool CanAnimBob() const;
    bool PerformOldBobbing( Vector& vecPos, QAngle& ang );
    void PerformAnimBobbing();
    bool PerformIronSight( Vector& vecPos, QAngle& ang );
    bool PerformLag( Vector& vecPos, QAngle& ang, const QAngle& origAng );
#endif

    CZMPlayer* GetOwner() const { return static_cast<CZMPlayer*>( CBaseViewModel::GetOwner() ); };

    virtual void CalcViewModelView( CBasePlayer* pOwner, const Vector& eyePosition, const QAngle& eyeAngles ) OVERRIDE;


    void SetWeaponModelEx( const char* pszModel, CBaseCombatWeapon* pWep, bool bOverriden );

    virtual CBaseCombatWeapon* GetOwningWeapon() OVERRIDE;

#ifdef GAME_DLL
    void SetModelColor2( float r, float g, float b ) { m_flClr.Set( 0, r ); m_flClr.Set( 1, g ); m_flClr.Set( 2, b ); };
#else
    void GetModelColor2( float& r, float& g, float& b ) { r = m_flClr[0]; g = m_flClr[1]; b = m_flClr[2]; };

    void SetDrawVM( bool state ) { m_bDrawVM = state; };
#endif

private:
    CNetworkArray( float, m_flClr, 3 );

#ifdef CLIENT_DLL
    bool m_bDrawVM; // We have to override this so the client can decide whether to draw it.

    int m_iOverrideModelIndex;
    CBaseCombatWeapon* m_pOverrideModelWeapon;
    CBaseCombatWeapon* m_pLastWeapon;

    bool m_bInIronSight;
    float m_flIronSightFrac;

    int m_iPoseParamMoveX;
    int m_iPoseParamVertAim;
    int m_iAttachmentIronsight;
#endif
};

#ifdef CLIENT_DLL
/*
class C_ZMViewModelClient : public C_PredictedViewModel
{
public:
    DECLARE_CLASS( C_ZMViewModelClient, C_PredictedViewModel );

    ~C_ZMViewModelClient();

    virtual C_BaseAnimating* FindFollowedEntity() OVERRIDE;
    virtual bool ShouldInterpolate() OVERRIDE;
    virtual void UpdateVisibility() OVERRIDE;
    virtual void SetWeaponModel( const char* pszModelname, CBaseCombatWeapon* weapon );

};
*/
#endif

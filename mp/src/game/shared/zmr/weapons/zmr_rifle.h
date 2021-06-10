#pragma once


#include "zmr_basepump.h"


#ifdef CLIENT_DLL
#define CZMWeaponRifle C_ZMWeaponRifle
#endif

class CZMWeaponRifle : public CZMBasePumpWeapon
{
public:
    DECLARE_CLASS( CZMWeaponRifle, CZMBasePumpWeapon );
    DECLARE_NETWORKCLASS();
    DECLARE_PREDICTABLE();

    CZMWeaponRifle();
    ~CZMWeaponRifle();


    virtual Vector GetBulletSpread() const OVERRIDE;
    virtual bool Holster( CBaseCombatWeapon* pSwitchTo = nullptr ) OVERRIDE;
    virtual void Drop( const Vector& vecVelocity ) OVERRIDE;
    virtual void ItemBusyFrame() OVERRIDE;
    virtual void ItemPostFrame() OVERRIDE;

    virtual Activity GetIdleActivity() const OVERRIDE { return IsZoomed() ? ACT_VM_IDLE_SPECIAL : BaseClass::GetIdleActivity(); }
    virtual Activity GetReloadStartAct() const OVERRIDE { return ACT_VM_RELOAD_START; }
    virtual Activity GetReloadEndAct() const OVERRIDE { return ACT_VM_RELOAD_FINISH; }
    virtual Activity GetPrimaryAttackActivity() OVERRIDE;
    virtual Activity GetPumpAct() const OVERRIDE;

    virtual bool IsZoomed() const OVERRIDE { return m_bInZoom; }
    virtual bool CanZoom() const;

    virtual void StartReload() OVERRIDE;

    void CheckToggleZoom();
    void CheckUnZoom();
    void ToggleZoom();
    void Zoom( CZMPlayer* pOwner ); // ZMRTODO: Do something more reasonable...
    void UnZoom( CZMPlayer* pOwner );

protected:
    CNetworkVar( bool, m_bInZoom );
};

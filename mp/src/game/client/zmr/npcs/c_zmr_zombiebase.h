#pragma once

#include "c_basecombatcharacter.h"



#include "zmr/c_zmr_charcircle.h"
#include "c_zmr_hat.h"

#include "zmr/zmr_player_shared.h"
#include "zmr/zmr_shareddefs.h"


#define MAX_GROUP_INDEX             9
#define INVALID_GROUP_INDEX         -1


// ZMRTODO: Predict selector index.
class C_ZMBaseZombie : public C_BaseCombatCharacter
{
public:
	DECLARE_CLASS( C_ZMBaseZombie, C_BaseCombatCharacter )
	DECLARE_CLIENTCLASS()
	DECLARE_PREDICTABLE();
    DECLARE_DATADESC()

    C_ZMBaseZombie();
    ~C_ZMBaseZombie();

    virtual void Spawn( void ) OVERRIDE;

    virtual int     DrawModel( int flags ) OVERRIDE;
    int             DrawModelAndEffects( int flags );


    virtual bool    IsNPCR() const OVERRIDE { return true; }



    virtual Vector          GetObserverCamOrigin() OVERRIDE { return WorldSpaceCenter(); }
    virtual const QAngle&   EyeAngles() OVERRIDE;
    virtual Vector          EyePosition() OVERRIDE;

    virtual const char* GetZombieLocalization() const { return ""; }
    
    //virtual void TraceAttack( const CTakeDamageInfo&, const Vector&, trace_t*,CDmgAccumulator* ) OVERRIDE;
    
    // Implemented in zmr_zombiebase_shared
    static bool             IsValidClass( ZombieClass_t zclass );
    static ZombieClass_t    NameToClass( const char* name );
    static const char*      ClassToName( ZombieClass_t zclass );
    static int              GetPopCost( ZombieClass_t zclass );
    static int              GetCost( ZombieClass_t zclass );
    static bool             HasEnoughPopToSpawn( ZombieClass_t zclass );
    int                     GetSelectorIndex() const;
    C_ZMPlayer*             GetSelector() const;
    void                    SetSelector( C_ZMPlayer* pPlayer );
    void                    SetSelector( int index );
    ZombieClass_t           GetZombieClass() const;
    int                     GetPopCost() const;
    int                     GetCost() const;
protected:
    void                    SetZombieClass( ZombieClass_t zclass );
public:


    inline int  GetGroup() const { return m_iGroup; };
    inline void SetGroup( int group ) { m_iGroup = group; };


    virtual CStudioHdr* OnNewModel() OVERRIDE;
    virtual C_BaseAnimating* BecomeRagdollOnClient() OVERRIDE;
    virtual void UpdateVisibility() OVERRIDE;
protected:
    virtual bool    CreateEventAccessories();
    void            ReleaseHat();
    virtual bool    IsAffectedByEvent( HappyZombieEvent_t iEvent ) const { return false; }
    virtual const char* GetEventHatModel( HappyZombieEvent_t iEvent ) const { return ""; }


protected:
    CZMCharCircle* m_fxHealth;
    CZMCharCircle* m_fxInner;

private:
    CNetworkVar( int, m_iSelectorIndex );
    CNetworkVar( float, m_flHealthRatio );

    int m_iGroup;
    ZombieClass_t m_iZombieClass;

    QAngle m_angEyeAttachment;


    C_ZMHolidayHat* m_pHat;
};

inline C_ZMBaseZombie* ToZMBaseZombie( C_BaseEntity* pEnt )
{
    //if ( !pEnt || !pEnt->IsNPC() )
    //    return nullptr;

    // We have to dynamic cast due to npc_crow, etc.
    return dynamic_cast<C_ZMBaseZombie*>( pEnt );
}

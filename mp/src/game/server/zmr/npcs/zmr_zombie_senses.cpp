#include "cbase.h"
#include "takedamageinfo.h"
#include "soundent.h"

#include "npcr/npcr_basenpc.h"

#include "zmr_zombie_senses.h"


CZMZombieSenses::CZMZombieSenses( NPCR::CBaseNPC* pNPC ) : NPCR::CBaseSenses( pNPC )
{

}

CZMZombieSenses::~CZMZombieSenses()
{
}

void CZMZombieSenses::OnDamaged( const CTakeDamageInfo& info )
{
    // Give the zombie free knowledge of our attacker.

    CBaseEntity* pAttacker = info.GetAttacker();

    if ( pAttacker && GetNPC()->IsEnemy( pAttacker ) )
    {
        auto* pVision = GetEntityOf( pAttacker );

        if ( !pVision )
        {
            pVision = new NPCR::VisionEntity( pAttacker );
            

            m_vVisionEnts.AddToTail( pVision );
            
            GetNPC()->OnSightGained( pAttacker );
        }

        // Give them some time to think about it.
        pVision->SetLastSeen( gpGlobals->curtime + 3.0f );
    }
}

void CZMZombieSenses::OnHeardSound( CSound* pSound )
{
    // Give the zombie free knowledge of our sound origin.


    CBaseEntity* pSrc = pSound->m_hOwner.Get();

    // This specific type comes only from player movement.
    // Ignore all other sound types.
    if ( (pSound->SoundType() & SOUND_PLAYER) == SOUND_PLAYER && pSrc )
    {
        auto* pVision = GetEntityOf( pSrc );

        if ( !pVision )
        {
            pVision = new NPCR::VisionEntity( pSrc );
            

            m_vVisionEnts.AddToTail( pVision );
            
            GetNPC()->OnSightGained( pSrc );
        }

        // Give them some time to think about it.
        pVision->SetLastSeen( gpGlobals->curtime + 3.0f );
    }
}

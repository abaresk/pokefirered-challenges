#include "global.h"
#include "gflib.h"
#include "strings.h"
#include "task.h"
#include "field_message_box.h"
#include "script.h"
#include "event_data.h"
#include "fldeff.h"
#include "party_menu.h"
#include "field_poison.h"
#include "constants/battle.h"

static bool32 IsMonValidSpecies(struct Pokemon *pokemon)
{
    u16 species = GetMonData(pokemon, MON_DATA_SPECIES2);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return FALSE;
    return TRUE;
}

static bool32 AllMonsFainted(void)
{
    int i;

    struct Pokemon *pokemon = gPlayerParty;
    for (i = 0; i < PARTY_SIZE; i++, pokemon++)
        if (IsMonValidSpecies(pokemon) && GetMonData(pokemon, MON_DATA_HP))
            return FALSE;
    return TRUE;
}

// Returns TRUE if `mon` faints
static bool8 ReduceHealth(struct Pokemon *mon, u32 delta)
{
    u32 newHP;
    u32 status;

    if (GetMonData(mon, MON_DATA_HP) == 0)
    {
        return FALSE;
    }

    newHP = max(GetMonData(mon, MON_DATA_HP) - delta, 0);
    SetMonData(mon, MON_DATA_HP, &newHP);

    if (newHP == 0)
    {
        status = STATUS1_KILLED_OUTSIDE;
        SetMonData(mon, MON_DATA_STATUS, &status);
        return TRUE;
    }
    return FALSE;
}

static void FaintFromFieldEffect(u8 partyIdx)
{
    struct Pokemon *pokemon = gPlayerParty + partyIdx;
    u32 status = STATUS1_NONE;
    AdjustFriendship(pokemon, FRIENDSHIP_EVENT_FAINT_OUTSIDE_BATTLE);
    SetMonData(pokemon, MON_DATA_STATUS, &status);
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    StringGetEnd10(gStringVar1);
}

static bool32 MonFaintedOutside(u8 partyIdx)
{
    struct Pokemon *pokemon = gPlayerParty + partyIdx;
    if (IsMonValidSpecies(pokemon) && 
        GetMonData(pokemon, MON_DATA_HP) == 0 &&
        GetMonData(pokemon, MON_DATA_STATUS) == STATUS1_KILLED_OUTSIDE)
    {
        return TRUE;
    }
    return FALSE;
}

#define tState   data[0]
#define tPartyId data[1]

static void Task_TryFieldPoisonWhiteOut(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (tState)
    {
    case 0:
        for (; tPartyId < PARTY_SIZE; tPartyId++)
        {
                if (MonFaintedOutside(data[1]))
                {
                    FaintFromFieldEffect(data[1]);
                    if (!gSaveBlock2Ptr->optionsNotifyFaintOff) {
                        ShowFieldMessage(gText_PkmnFainted3);
                    }
                    data[0]++;
                    return;
                }
        }
        tState = 2;
        break;
    case 1:
        if (IsFieldMessageBoxHidden())
            tState--;
        break;
    case 2:
        if (AllMonsFainted())
            gSpecialVar_Result = TRUE;
        else
            gSpecialVar_Result = FALSE;
        EnableBothScriptContexts();
        DestroyTask(taskId);
        break;
    }
}

void TryFieldPoisonWhiteOut(void)
{
    CreateTask(Task_TryFieldPoisonWhiteOut, 80);
    ScriptContext1_Stop();
}

s32 DoPoisonFieldEffect(void)
{
    int i;
    u32 hp;
    struct Pokemon *pokemon = gPlayerParty;
    u32 poisonEffect = FALSE;
    u32 faintEffect = FALSE;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        // Damage from poison
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES) && GetAilmentFromStatus(GetMonData(pokemon, MON_DATA_STATUS)) == AILMENT_PSN)
        {
            faintEffect |= ReduceHealth(pokemon, 1);
            poisonEffect |= TRUE;
        }
        // Damage from nuclear radiation
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES))
        {
            faintEffect |= ReduceHealth(pokemon, 1);
            poisonEffect |= TRUE;
        }
        pokemon++;
    }
    if (faintEffect || poisonEffect)
    {
        FldEffPoison_Start();
    }
    if (faintEffect)
    {
        return FLDPSN_FNT;
    }
    if (poisonEffect)
    {
        return FLDPSN_PSN;
    }
    return FLDPSN_NONE;
}
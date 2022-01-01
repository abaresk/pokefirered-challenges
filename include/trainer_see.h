#ifndef GUARD_TRAINER_SEE_H
#define GUARD_TRAINER_SEE_H

#include "global.h"

enum
{
    TRSEE_NONE,
    TRSEE_EXCLAMATION,
    TRSEE_EXCLAMATION_WAIT,
    TRSEE_MOVE_TO_PLAYER,
    TRSEE_PLAYER_FACE,
    TRSEE_PLAYER_FACE_WAIT,
    TRSEE_REVEAL_DISGUISE,
    TRSEE_REVEAL_DISGUISE_WAIT,
    TRSEE_REVEAL_BURIED,
    TRSEE_BURIED_POP_OUT,
    TRSEE_BURIED_JUMP,
    TRSEE_REVEAL_BURIED_WAIT,
    TRSEE_OFFSCREEN_CREATE_CAMERA,
    TRSEE_OFFSCREEN_CREATE_MOVE_UP,
    TRSEE_OFFSCREEN_CREATE_MOVE_DOWN,
    TRSEE_PLAYER_FACE_AWAY,
    TRSEE_EXCLAMATION_FACE_AWAY_WAIT,
};

bool8 CheckForTrainersWantingBattle(void);
void MovementAction_RevealTrainer_RunTrainerSeeFuncList(struct ObjectEvent *var);
u8 FldEff_ExclamationMarkIcon1(void);
u8 FldEff_DoubleExclMarkIcon(void);
u8 FldEff_XIcon(void);
u8 FldEff_SmileyFaceIcon(void);
u8 FldEff_QuestionMarkIcon(void);
void Task_RunTrainerSeeFuncList(u8 taskId);
void Task_TrainerEncounterWhiteOut(u8 taskId);
void Task_EndTrainerApproach(u8 taskId);

#endif //GUARD_TRAINER_SEE_H

/*
 ==============================================================================
 
 RandomEffects.cpp
 Created: 23 May 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "RandomEffects.h"
#include "../Definitions/Definitions.h"
#include <random>

void RandomEffects::newQuickQuiz()
{
    if (QUICKQUIZ.isValid())
        vt.removeChild(QUICKQUIZ, nullptr);
    
    ValueTree qq(IDs::QuickQuiz);
    ValueTree p(IDs::Player);
    qq.addChild(p, -1, nullptr);
    vt.addChild(qq, -1, nullptr);
    
    /* create and set 3 random Effects
        RightEffect    = "Right_Effect"     ->   int EffectNumber
        WrongEffectA   = "Wrong_Effect_A"   ->   int EffectNumber
        WrongEffectB   = "Wrong_Effect_B"   ->   int EffectNumber
     */
    
    int numEffects (EFFECTLIST.getNumChildren());
    int right = r.nextInt(numEffects);
    QUICKQUIZ.setProperty(IDs::RightEffect, right, nullptr);
    
    int wrong1 = r.nextInt(numEffects);
    while (wrong1 == right) {
        wrong1 = r.nextInt(numEffects);
    }
    QUICKQUIZ.setProperty(IDs::WrongEffectA, wrong1, nullptr);
    
    int wrong2 = r.nextInt(numEffects);
    while (wrong2 == right || wrong2 == wrong1) {
        wrong2 = r.nextInt(numEffects);
    }
    QUICKQUIZ.setProperty(IDs::WrongEffectB, wrong2, nullptr);
    
    /* set the 3 possibilities at random positions so that the right answer isn't always on the same button
     Identifier RightButton    = "Right_Button_Num"; int ButtonNumber
     Identifier WrongButtonA   = "Wrong_Button_A";   int ButtonNumber
     Identifier WrongButtonB   = "Wrong_Button_B";   int ButtonNumber
     */
    
    Array<int> order = {0, 1, 2};
    std::random_device randomDevice;
    std::mt19937 mersenneTwister (randomDevice());
    std::shuffle (order.begin(), order.end(), mersenneTwister);
    
    QUICKQUIZ.setProperty(IDs::RightButton, order[0], nullptr);
    QUICKQUIZ.setProperty(IDs::WrongButtonA, order[1], nullptr);
    QUICKQUIZ.setProperty(IDs::WrongButtonB, order[2], nullptr);
    
    
//    DBG("Right EffectNumber: " << right);
//    DBG("WrongA EffectNumber: " << wrong1);
//    DBG("WrongB EffectNumber: " << wrong2);
//    DBG("Right Button at position: " << QUICKQUIZ[IDs::RightButton].toString());
//    DBG("WrongA Button at position: " << QUICKQUIZ[IDs::WrongButtonA].toString());
//    DBG("WrongB Button at position: " << QUICKQUIZ[IDs::WrongButtonB].toString());
}

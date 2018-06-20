/*
 ==============================================================================

 DataHandler.cpp
 Created: 3 May 2018 9:18:38pm
 Author:  Lambert Schulze

 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "DataHandler.h"
#include "../Definitions/Definitions.h"

DataHandler::DataHandler()
: vt()
{
    auto appDataDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Application Support").getChildFile(JUCEApplication::getInstance()->getApplicationName());
    
    if (!appDataDir.exists())
        appDataDir.createDirectory();
    
    saveFile = appDataDir.getChildFile ("Save");
    
    loadData(saveFile);
    setupProperties();
}

DataHandler::~DataHandler()
{
    saveData(saveFile);
}

ValueTree& DataHandler::getValueTree()
{
    return vt;
}

void DataHandler::setupProperties()
{
    if (!vt.isValid()) {
        DBG ("No valid ValueTree..");
        vt = ValueTree(IDs::Main);
    }
    
    if (vt[IDs::Version].toString() != "alpha 1.2") {
        DBG ("Version number incorrect. Creating clean App state");
        vt = ValueTree(IDs::Main);
    }
    
    // checking for MAIN
    if (!vt.hasProperty(IDs::Version))      vt.setProperty(IDs::Version, "alpha 1.2", nullptr);
    if (!vt.hasProperty(IDs::WindowHeight)) vt.setProperty(IDs::WindowHeight, 600, nullptr);
    if (!vt.hasProperty(IDs::WindowWidth))  vt.setProperty(IDs::WindowWidth, 1000, nullptr);
    
    // checking for FILELIST
    if (!vt.getChildWithName(IDs::FileList).isValid())
    {
        // setting up a fresh FILELIST child
        ValueTree fileList (IDs::FileList);
        fileList.setProperty(IDs::Repeat, false, nullptr);
        fileList.setProperty(IDs::Shuffle, false, nullptr);
        vt.addChild(fileList, -1, nullptr);
    }
    
    // checking for EFFECTLIST
    if (!vt.getChildWithName(IDs::EffectList).isValid())
    {
        // setting up a new FILELIST with Level 0 Effects
        
        ValueTree effectList    (IDs::EffectList);
        
        ValueTree noEffect      (IDs::Effect);
        noEffect    .setProperty(IDs::Number, 0, nullptr);
        noEffect    .setProperty(IDs::EffectName, "No Effect", nullptr);
        noEffect    .setProperty(IDs::EffectType, "Other", nullptr);
        ValueTree sumVolUp      (IDs::Effect);
        sumVolUp    .setProperty(IDs::Number, 1, nullptr);
        sumVolUp    .setProperty(IDs::EffectName, "Sum Vol Up", nullptr);
        sumVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        ValueTree sumVolDown    (IDs::Effect);
        sumVolDown  .setProperty(IDs::Number, 2, nullptr);
        sumVolDown  .setProperty(IDs::EffectName, "Sum Vol Down", nullptr);
        sumVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        ValueTree leftSolo      (IDs::Effect);
        leftSolo    .setProperty(IDs::Number, 3, nullptr);
        leftSolo    .setProperty(IDs::EffectName, "Left Solo", nullptr);
        leftSolo    .setProperty(IDs::EffectType, "Solo", nullptr);
        ValueTree rightSolo     (IDs::Effect);
        rightSolo   .setProperty(IDs::Number, 4, nullptr);
        rightSolo   .setProperty(IDs::EffectName, "Right Solo", nullptr);
        rightSolo   .setProperty(IDs::EffectType, "Solo", nullptr);
        ValueTree mono          (IDs::Effect);
        mono        .setProperty(IDs::Number, 5, nullptr);
        mono        .setProperty(IDs::EffectName, "Mono", nullptr);
        mono        .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        ValueTree lrswitched    (IDs::Effect);
        lrswitched  .setProperty(IDs::Number, 6, nullptr);
        lrswitched  .setProperty(IDs::EffectName, "LR Switched", nullptr);
        lrswitched  .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        ValueTree midVolUp      (IDs::Effect);
        midVolUp    .setProperty(IDs::Number, 7, nullptr);
        midVolUp    .setProperty(IDs::EffectName, "Mid Vol Up", nullptr);
        midVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        ValueTree midVolDown    (IDs::Effect);
        midVolDown  .setProperty(IDs::Number, 8, nullptr);
        midVolDown  .setProperty(IDs::EffectName, "Mid Vol Down", nullptr);
        midVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        ValueTree sideVolUp      (IDs::Effect);
        sideVolUp   .setProperty(IDs::Number, 9, nullptr);
        sideVolUp   .setProperty(IDs::EffectName, "Side Vol Up", nullptr);
        sideVolUp   .setProperty(IDs::EffectType, "Volume", nullptr);
        ValueTree sideVolDown    (IDs::Effect);
        sideVolDown .setProperty(IDs::Number, 10, nullptr);
        sideVolDown .setProperty(IDs::EffectName, "Side Vol Down", nullptr);
        sideVolDown .setProperty(IDs::EffectType, "Volume", nullptr);
        
        effectList.addChild(noEffect,       -1, nullptr);
        effectList.addChild(sumVolUp,       -1, nullptr);
        effectList.addChild(sumVolDown,     -1, nullptr);
        effectList.addChild(leftSolo,       -1, nullptr);
        effectList.addChild(rightSolo,      -1, nullptr);
        effectList.addChild(mono,           -1, nullptr);
        effectList.addChild(lrswitched,     -1, nullptr);
        effectList.addChild(midVolUp,       -1, nullptr);
        effectList.addChild(midVolDown,     -1, nullptr);
        effectList.addChild(sideVolUp,      -1, nullptr);
        effectList.addChild(sideVolDown,    -1, nullptr);
        
        for (auto effect : effectList) {
            effect.setProperty(IDs::Level, 1, nullptr);
            effect.setProperty(IDs::Velocity, 1, nullptr);
        }
        vt.addChild(effectList, -1, nullptr);
    }
    
    //DBG ("Property Setup done! Here's the ValueTree:");
    //DBG (vt.toXmlString());
}

void DataHandler::loadData(File file)
{
    DBG("Loading Data...");
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (XmlDocument::parse (file));
        
        if (e == NULL)
        {
            vt = ValueTree();
            DBG("Loading failed..");
        }
        else
        {
            vt = ValueTree::fromXml(*e);
            DBG("...Loading done!");
            //DBG(vt.toXmlString());
        }
    }
    else
    {
        DBG("File doesn't exist.");
        Result creation (file.create());
        
        if (creation.wasOk())       DBG("created a new file! Hurray!");
        else                        DBG("could not create a new file :-(" + creation.getErrorMessage());
    }
}

void DataHandler::saveData(File file)
{    
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (vt.createXml());
        e->writeToFile(file, "");
        DBG("Data saved.");
        //DBG("This is the saved ValueTree:");
        //DBG(vt.toXmlString());
    }
    if (!file.exists()) DBG("Save file doesn't exist. Could't save..");
}

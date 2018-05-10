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
: mainVT()
{
    auto appDataDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Application Support").getChildFile(JUCEApplication::getInstance()->getApplicationName());
    
    if (!appDataDir.exists())
        appDataDir.createDirectory();
    
    saveFile = appDataDir.getChildFile ("Save");
    
    setupProperties();
//    DBG("setting up the properties.");
}

DataHandler::~DataHandler()
{
    saveData(saveFile);
}

ValueTree& DataHandler::getValueTree()
{
//    DBG("DataHandler: returning the ValueTree.");
    return mainVT;
}

void DataHandler::setupProperties()
{
    loadData(saveFile);
    
    // if VT is not valid, create a new one.
    if (!mainVT.isValid())
    {
        //DBG ("No valid ValueTree..");
        mainVT = ValueTree(IDs::Main);
    }
    
    
    // checking for MAIN
    if (!mainVT.hasProperty(IDs::WindowHeight)) mainVT.setProperty(IDs::WindowHeight, 600, nullptr);
    if (!mainVT.hasProperty(IDs::WindowWidth))  mainVT.setProperty(IDs::WindowWidth, 1000, nullptr);
    
    
    // checking for TRANSPORT
    if (!mainVT.getChildWithName(IDs::Transport).isValid())
    {
        // setting up a fresh TRANSPORT child.
        ValueTree transport (IDs::Transport);
        transport.setProperty(IDs::LimitPlayback, false, nullptr);
        mainVT.addChild(transport, -1, nullptr);
    }
    // nulling TRANSPORT
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState,    "Stopped",  nullptr);
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing,      false,      nullptr);
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::EffectToPlay,      -1,         nullptr);
    
    
    // checking for FILELIST
    if (!mainVT.getChildWithName(IDs::FileList).isValid())
    {
        // setting up a fresh FILELIST child
        ValueTree fileList (IDs::FileList);
        fileList.setProperty(IDs::SelectedFile, 0, nullptr);
        mainVT.addChild(fileList, -1, nullptr);
    }
    mainVT.getChildWithName(IDs::FileList).setProperty(IDs::SelectedFile, 0, nullptr);
    
    // checking for EFFECTLIST
    if (!mainVT.getChildWithName(IDs::EffectList).isValid())
    {
        // setting up a new FILELIST with Level 0 Effects
        
        ValueTree effectList    (IDs::EffectList);
        
        ValueTree noEffect      (IDs::Effect);
        noEffect    .setProperty(IDs::Number, 0, nullptr);
        noEffect    .setProperty(IDs::EffectName, "No Effect", nullptr);
        noEffect    .setProperty(IDs::EffectType, "Other", nullptr);
        noEffect    .setProperty(IDs::Level, 0, nullptr);
        ValueTree sumVolUp      (IDs::Effect);
        sumVolUp    .setProperty(IDs::Number, 1, nullptr);
        sumVolUp    .setProperty(IDs::EffectName, "Sum Vol Up", nullptr);
        sumVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        sumVolUp    .setProperty(IDs::Level, 0, nullptr);
        ValueTree sumVolDown    (IDs::Effect);
        sumVolDown  .setProperty(IDs::Number, 2, nullptr);
        sumVolDown  .setProperty(IDs::EffectName, "Sum Vol Down", nullptr);
        sumVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        sumVolDown  .setProperty(IDs::Level, 0, nullptr);
        ValueTree leftSolo      (IDs::Effect);
        leftSolo    .setProperty(IDs::Number, 3, nullptr);
        leftSolo    .setProperty(IDs::EffectName, "Left Solo", nullptr);
        leftSolo    .setProperty(IDs::EffectType, "Solo", nullptr);
        leftSolo    .setProperty(IDs::Level, 0, nullptr);
        ValueTree rightSolo     (IDs::Effect);
        rightSolo   .setProperty(IDs::Number, 4, nullptr);
        rightSolo   .setProperty(IDs::EffectName, "Right Solo", nullptr);
        rightSolo   .setProperty(IDs::EffectType, "Solo", nullptr);
        rightSolo   .setProperty(IDs::Level, 0, nullptr);
        ValueTree mono          (IDs::Effect);
        mono        .setProperty(IDs::Number, 5, nullptr);
        mono        .setProperty(IDs::EffectName, "Mono", nullptr);
        mono        .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        mono        .setProperty(IDs::Level, 0, nullptr);
        ValueTree lrswitched    (IDs::Effect);
        lrswitched  .setProperty(IDs::Number, 6, nullptr);
        lrswitched  .setProperty(IDs::EffectName, "LR Switched", nullptr);
        lrswitched  .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        lrswitched  .setProperty(IDs::Level, 0, nullptr);
        ValueTree midVolUp      (IDs::Effect);
        midVolUp    .setProperty(IDs::Number, 7, nullptr);
        midVolUp    .setProperty(IDs::EffectName, "Mid Vol Up", nullptr);
        midVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        midVolUp    .setProperty(IDs::Level, 0, nullptr);
        ValueTree midVolDown    (IDs::Effect);
        midVolDown  .setProperty(IDs::Number, 8, nullptr);
        midVolDown  .setProperty(IDs::EffectName, "Mid Vol Down", nullptr);
        midVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        midVolDown  .setProperty(IDs::Level, 0, nullptr);
        ValueTree sideVolUp      (IDs::Effect);
        sideVolUp   .setProperty(IDs::Number, 9, nullptr);
        sideVolUp   .setProperty(IDs::EffectName, "Side Vol Up", nullptr);
        sideVolUp   .setProperty(IDs::EffectType, "Volume", nullptr);
        sideVolUp   .setProperty(IDs::Level, 0, nullptr);
        ValueTree sideVolDown    (IDs::Effect);
        sideVolDown .setProperty(IDs::Number, 10, nullptr);
        sideVolDown .setProperty(IDs::EffectName, "Side Vol Down", nullptr);
        sideVolDown .setProperty(IDs::EffectType, "Volume", nullptr);
        sideVolDown .setProperty(IDs::Level, 0, nullptr);
        
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
        mainVT.addChild(effectList, -1, nullptr);
    }
    
    //    if (!mainVT.getChildWithName(IDs::Quiz).isValid())
    //    {
    //        ValueTree quizTree (IDs::Quiz);
    //        quizTree.setProperty(IDs::QuizState, 3, nullptr);
    //
    //        for (int i=0; i<3; ++i)
    //        {
    //            ValueTree choiceTree (IDs::Choice);
    //            choiceTree.setProperty(IDs::Name, "", nullptr);
    //            choiceTree.setProperty(IDs::isRight, "", nullptr);
    //            quizTree.addChild(choiceTree, -1, nullptr);
    //        }
    //        mainVT.addChild(quizTree, -1, nullptr);
    //    }
    //    if (mainVT.getChildWithName(IDs::Quiz).getChildWithProperty(IDs::isRight, true).isValid()) mainVT.getChildWithName(IDs::Quiz).getChildWithProperty(IDs::isRight, true).setProperty(IDs::isRight, false, nullptr);
    
    //DBG ("Property Setup done! Here's the ValueTree:");
    //DBG ("mainVT.toXmlString()");
}

void DataHandler::loadData(File file)
{
    DBG("Loading Data...");
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (XmlDocument::parse (file));
        
        if (e == NULL)
        {
            mainVT = ValueTree();
            DBG("Loading failed..");
        }
        else
        {
            mainVT = ValueTree::fromXml(*e);
            DBG("...Loading done!");
        }
    }
    else
    {
        DBG("File doesn't exist.");
        Result creation (file.create());
        
        if (creation.wasOk())       DBG("created a new file! Hurray!");
        else                        {DBG("could not create a new file :-(");
            DBG(creation.getErrorMessage());}
    }
}

void DataHandler::saveData(File file)
{
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (mainVT.createXml());
        e->writeToFile(file, "");
        DBG("Data saved.");
        DBG("This is the saved ValueTree:");
        DBG(mainVT.toXmlString());
    }
    if (!file.exists()) DBG("Save file doesn't exist. Could't save..");
}

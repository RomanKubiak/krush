/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "KrushSync.h"
//[/Headers]

#include "KrushTransportInfo.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KrushMain  : public Component,
                   public KrushSync::Listener
{
public:
    //==============================================================================
    KrushMain ();
    ~KrushMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void realtimeEvent(const RealtimeEvent e);
	KrushSync &getSync() { return krushSync;  }
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	KrushSync krushSync;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<KrushTransportInfo> transportInfo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KrushMain)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

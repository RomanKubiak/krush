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
class KrushMain;

class KrushTransportIndicator : public Component
{
	public:
		KrushTransportIndicator(const Colour &_c) : c(_c)
		{ }
		void paint(Graphics &g)
		{
			g.setColour(c);
			g.fillRect(getLocalBounds().toFloat().reduced(1.0f, 1.0f));
		}

		Colour c;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KrushTransportInfo  : public Component,
                            public KrushSync::Listener
{
public:
    //==============================================================================
    KrushTransportInfo (KrushMain &_krush);
    ~KrushTransportInfo();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void realtimeEventAsync(const RealtimeEvent e);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	KrushMain & krush;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> tempo;
    std::unique_ptr<KrushTransportIndicator> quarterIndicator;
    std::unique_ptr<KrushTransportIndicator> syncedToMaster;
    std::unique_ptr<KrushTransportIndicator> generatesClock;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KrushTransportInfo)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

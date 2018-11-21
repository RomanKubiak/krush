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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "KrushMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KrushMain::KrushMain ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    transportInfo.reset (new KrushTransportInfo (*this));
    addAndMakeVisible (transportInfo.get());

    //[UserPreSize]
    //[/UserPreSize]

    setSize (128, 96);


    //[Constructor] You can add your own custom stuff here..
	krushSync.addListener(this);
	krushSync.setTempo(120.0);
	krushSync.start();
    //[/Constructor]
}

KrushMain::~KrushMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    transportInfo = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KrushMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xffa3a3a3), fillColour2 = Colour (0xff717171);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       static_cast<float> ((getWidth() / 2)) - 0.0f + x,
                                       static_cast<float> ((getHeight() / 2)) - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KrushMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    transportInfo->setBounds (0, 0, getWidth() - 0, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void KrushMain::realtimeEvent(const RealtimeEvent e)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KrushMain" componentName=""
                 parentClasses="public Component, public KrushSync::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.33" fixedSize="1" initialWidth="128"
                 initialHeight="96">
  <BACKGROUND backgroundColour="0">
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 0C 0C, 0=ffa3a3a3, 1=ff717171"
          hasStroke="0"/>
  </BACKGROUND>
  <JUCERCOMP name="" id="9d80682c06317078" memberName="transportInfo" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 12" sourceFile="KrushTransportInfo.cpp"
             constructorParams="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

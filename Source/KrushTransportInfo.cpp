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

#include "KrushTransportInfo.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "KrushMain.h"
//[/MiscUserDefs]

//==============================================================================
KrushTransportInfo::KrushTransportInfo (KrushMain &_krush)
    : krush(_krush)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    tempo.reset (new Label (String(),
                            TRANS("120")));
    addAndMakeVisible (tempo.get());
    tempo->setFont (Font ("Terminus (TTF)", 12.0f, Font::bold));
    tempo->setJustificationType (Justification::centred);
    tempo->setEditable (false, false, false);
    tempo->setColour (TextEditor::textColourId, Colours::black);
    tempo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    quarterIndicator.reset (new KrushTransportIndicator (Colour(0xff3ddbb5)));
    addAndMakeVisible (quarterIndicator.get());

    syncedToMaster.reset (new KrushTransportIndicator (Colour(0xff00ca4b)));
    addAndMakeVisible (syncedToMaster.get());

    generatesClock.reset (new KrushTransportIndicator (Colour(0xff3ddbb5)));
    addAndMakeVisible (generatesClock.get());


    //[UserPreSize]
    //[/UserPreSize]

    setSize (320, 12);


    //[Constructor] You can add your own custom stuff here..
	// Desktop::getInstance().getAnimator().fadeOut(quarterIndicator.get(), 1500);
	// Desktop::getInstance().getAnimator().fadeOut(syncedToMaster.get(), 1500);
	// Desktop::getInstance().getAnimator().fadeOut(generatesClock.get(), 1500);
	krush.getSync().addListener(this);
    //[/Constructor]
}

KrushTransportInfo::~KrushTransportInfo()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	Desktop::getInstance().getAnimator().cancelAllAnimations(false);
	krush.getSync().removeListener(this);
    //[/Destructor_pre]

    tempo = nullptr;
    quarterIndicator = nullptr;
    syncedToMaster = nullptr;
    generatesClock = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KrushTransportInfo::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KrushTransportInfo::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tempo->setBounds (0, 0, 42, getHeight() - 0);
    quarterIndicator->setBounds (((getWidth() - 36) + 12) + 12, 0, 12, 12);
    syncedToMaster->setBounds ((getWidth() - 36) + 12, 0, 12, 12);
    generatesClock->setBounds (getWidth() - 36, 0, 12, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void KrushTransportInfo::realtimeEventAsync(const RealtimeEvent e)
{
	if (e == ClockQuarterNote)
	{
		quarterIndicator->setAlpha(1.0f);
		quarterIndicator->setVisible(true);
		Desktop::getInstance().getAnimator().fadeOut(quarterIndicator.get(), 200);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KrushTransportInfo" componentName=""
                 parentClasses="public Component, public KrushSync::Listener"
                 constructorParams="KrushMain &amp;_krush" variableInitialisers="krush(_krush)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="1" initialWidth="320" initialHeight="12">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="" id="c808eb56f1b69ae" memberName="tempo" virtualName=""
         explicitFocusOrder="0" pos="0 0 42 0M" edTextCol="ff000000" edBkgCol="0"
         labelText="120" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Terminus (TTF)" fontsize="12.0"
         kerning="0.0" bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
  <GENERICCOMPONENT name="" id="9d25d7883580c2c5" memberName="quarterIndicator" virtualName=""
                    explicitFocusOrder="0" pos="0R 0 12 12" posRelativeX="fd49077b977a48a6"
                    class="KrushTransportIndicator" params="Colour(0xff3ddbb5)"/>
  <GENERICCOMPONENT name="" id="fd49077b977a48a6" memberName="syncedToMaster" virtualName=""
                    explicitFocusOrder="0" pos="0R 0 12 12" posRelativeX="129cfe88b40c17bd"
                    class="KrushTransportIndicator" params="Colour(0xff00ca4b)"/>
  <GENERICCOMPONENT name="" id="129cfe88b40c17bd" memberName="generatesClock" virtualName=""
                    explicitFocusOrder="0" pos="36R 0 12 12" class="KrushTransportIndicator"
                    params="Colour(0xff3ddbb5)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

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

#include "KrushPadComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KrushPadComponent::KrushPadComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (32, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

KrushPadComponent::~KrushPadComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KrushPadComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff00ca4b));

    {
        int x = 1, y = 1, width = getWidth() - 2, height = getHeight() - 2;
        Colour strokeColour1 = Colour (0x4fffffff), strokeColour2 = Colour (0x80ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (strokeColour1,
                                       static_cast<float> ((getWidth() / 2)) - 1.0f + x,
                                       0.0f - 1.0f + y,
                                       strokeColour2,
                                       static_cast<float> (proportionOfWidth (1.0f)) - 1.0f + x,
                                       static_cast<float> (proportionOfHeight (1.0f)) - 1.0f + y,
                                       false));
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KrushPadComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KrushPadComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="1" initialWidth="32" initialHeight="32">
  <BACKGROUND backgroundColour="ff00ca4b">
    <RECT pos="1 1 2M 2M" fill="solid: 2aa5a5" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="linear: 0C 0, 100% 100%, 0=4fffffff, 1=80ffffff"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

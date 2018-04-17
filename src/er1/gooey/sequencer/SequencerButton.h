//
// Created by mzapp on 4/16/18.
//

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"

class SequencerButton
    : public KorgButton
{
public:
    SequencerButton(int sequencerStep);

    const int stepID;
private:
};

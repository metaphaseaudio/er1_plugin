//
// Created by mzapp on 4/16/18.
//

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"

class GridButton
    : public KorgButton
{
public:
    GridButton(int sequencerStep);
    const int stepID;
private:
};

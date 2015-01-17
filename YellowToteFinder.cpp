#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "YellowToteFinder.h"
#include "Contour.h"

YellowToteFinder::YellowToteFinder()
{
}

bool YellowToteFinder::findTote(Mat* img)
{   
    vector<Contour> contours = detectContours_YellowFilter(img, 6, 25);
    
    // Find Shapes
    foundTote = ytm.findMatch(&contours, img, &contourTote, &rectTote);
    foundL = lm.findMatch(&contours, img, &contourL, &rectL);
    foundBL = blm.findMatch(&contours, img, &contourBL, &rectBL);
    
    // Check for proper nesting
    checkNesting();
    cout << "Found (" << foundTote << "," << foundBL << "," << foundL << ")" << endl;
    cout << "Properly Nested? " << isProperlyNested << endl;
    
    // If we're missing the tote, try to infer the tote's position from the L's.
    
    /*
     1. Found tote, L, BL & They are properly nested: Good :)
     2. Found L, BL, missing Tote or bad nesting, trust L's infer shape of tote
     3. Found one L, found tote & properly nested: Good :)
     4. Found one L, missing l and tote: Assume location of tote based on L.
    */
    
    return foundTote;
}

void YellowToteFinder::checkNesting()
{
    // If there is no tote, we only need to see if the L's are not nested.
    if (!foundTote) {
        
        // We are missing tote and an L. No nesting is possible. Assume it is ok.
        if (!foundL || !foundBL) {
            isProperlyNested = true;
            return;
        }
        
        // We have two L's - If they are nested, that is BAD. Just assume we never found them
        if (contourNested(&contourL, &contourBL) || contourNested(&contourBL, &contourL)) {
            foundL = foundBL = false;
            isProperlyNested = true;
            return;
        } 
        
        // L's are NOT nested,this is GOOD.
        isProperlyNested = true;
        return;
    }
    
    // We found a tote. Any L's we found should be nested in the tote
    else {
        
        // L is not in the tote. Ignore it.
        if (foundL && !contourNested(&contourTote, &contourL))
            foundL = false;
        
        // BL is not in the tote. Ignore it.
        if (foundBL && !contourNested(&contourTote, &contourBL))
            foundBL = false;
        
        isProperlyNested = true;
        return;
    }  
}

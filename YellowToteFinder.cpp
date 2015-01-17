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
        
        // We have two L's - If they are nested, that is BAD.
        if (contourNested(&contourL, &contourBL) || contourNested(&contourBL, &contourL)) {
            isProperlyNested = false;
            return;
        } 
        
        // L's are NOT nested,this is GOOD.
        isProperlyNested = false;
        return;
    }
    
    // We found a tote. Any L's we found should be nested in the tote
    else {
        
        if (foundL && !contourNested(&contourTote, &contourL)) {
            isProperlyNested = false;
            return;
        }
        
        if (foundBL && !contourNested(&contourTote, &contourBL)) {
            isProperlyNested = false;
            return;
        }
        
        isProperlyNested = true;
        return;
    }  
}

/*
 
 ofxKinectFeatures
 Universitat Pompeu Fabra / Escola Superior de Música de Catalunya
 
 Copyright (c) 2014 Álvaro Sarasúa <alvaro.sarasua@upf.edu>
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 */

#ifndef openNiWorm_ofxKinectFeatures_h
#define openNiWorm_ofxKinectFeatures_h

#include "ofMain.h"
#include "ofxMocapElement.h"
#include <numeric>

namespace coord
{
	enum
	{
		X = 0,
		Y = 1,
		Z = 2
	};    
} // namespace coord

namespace filter
{
    enum
    {
        SOFT = 0,
        MED = 1,
        HARD = 2
    };
} // namespace filter

class ofxKinectFeatures {
public:
    ofxKinectFeatures();
    
    void update();
    ofxMocapElement* getElement(Joint _id);
    
    void setKinect(ofxOpenNI* device);
    void setFilterLevel(int filterLevel);
    
    void setDepth(int newDepth);
    int getDepth();
    
    //DESCIPTOR GETTERS
    //JOINT DESCRIPTORS
    float getPos(Joint j, unsigned int axis);
    ofPoint get3DPos(Joint j);
    
    float getFiltPos(Joint j, unsigned int axis);
    ofPoint get3DFiltPos(Joint j);
    vector<ofPoint> get3DFiltPosVector(Joint j);
    
    float getVel(Joint j, unsigned int axis);
    ofPoint get3DVel(Joint j);
    
    float getAcc(Joint j, unsigned int axis);
    vector<float> getAccVector(Joint j, unsigned int axis);
    
    float getAccTr(Joint j);
    vector<float> getAccTrVector (Joint j);
    
    float getDistToTorso(Joint j);
    
    float getRelPosToTorso(Joint j, unsigned int axis);
    
    //OVERALL DESCRIPTORS
    float getQom();
    float getCI();
    float getSymmetry();
    float getYMaxHands();
    
    bool isNewDataAvailable();
    
private:
    float *aFilter;
    float *bFilter;
    float *aLpd1;
    float *bLpd1;
    float *aLpd2;
    float *bLpd2;
    
    //overall descriptors
    float qom, ci, symmetry, yMaxHands;
    vector<float> meanVels;
    
    bool newValues;
    
    ofxOpenNI* kinect;
    vector<ofxMocapElement> elements;
    
    int depth;
    
    void computeJointDescriptors(ofxOpenNIJoint joint, const float &h);
    void computeOverallDescriptors();
    ofPoint applyFilter (vector<ofPoint> x, vector<ofPoint> y, float *a, float *b);
    
    //Functor to look for elements matching an id
    struct MatchId
    {
        MatchId(const Joint& j) : j_(j) {}
        bool operator()(ofxMocapElement& obj) const
        {
            return obj.getElementId() == j_;
        }
    private:
        const Joint& j_;
    };
};

#endif
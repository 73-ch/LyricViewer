#pragma once

#include "ofMain.h"
#include "TextMesh.h"
#include "ofxPubSubOsc.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofTrueTypeFont font;
    ofEasyCam cam;
    ofLight light;
    string main_text;
    TextMesh* text_mesh;
    
    ofMesh iikanjiText(const ofTrueTypeFont& font, const string text, const float roughness) {
        auto font_paths = font.getStringAsPoints(text);
        ofMesh m;
        for (auto p : font_paths) {
            p.setStrokeWidth(20);
        
            // side
            vector<ofPolyline> outlines = p.getOutline();
            
            for (auto& l : outlines) {
                l = l.getResampledBySpacing(roughness);
                ofMesh temp;
                // side verts
                temp.addVertices(l.getVertices());
                
//                auto temp_verts = l.getVertices();
                // side indices
//                unsigned int len = l.getVertices().size();
//
//                for (unsigned int i =0 ; i< len-1; ++i) temp.addIndices({i, i+1, i + len, i +len, i+len+1, i + 1});
//
                m.append(temp);
            }
        }
        return m;
    }

};

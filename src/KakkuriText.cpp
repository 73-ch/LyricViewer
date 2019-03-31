#include "KakkuriText.h"

KakkuriText::KakkuriText(ofTrueTypeFont& font_) : font(font_) {
    
}

void KakkuriText::setFont(ofTrueTypeFont &font_) {
    font = font_;
    setText(current_text, current_roughness);
}

void KakkuriText::setText(const string text, const float roughness) {
    mesh.clear();
    num_verts.clear();
    line_indices.clear();
    triangle_indices.clear();
    
    current_text = text;
    current_roughness = roughness;
    
    auto font_paths = font.getStringAsPoints(text);
    ofMesh m;
    for (auto p : font_paths) {
        p.setStrokeWidth(20);
        
        // side
        vector<ofPolyline> outlines = p.getOutline();
        
        for (auto& l : outlines) {
            l = l.getResampledBySpacing(roughness);
            unsigned int len = l.getVertices().size();
            unsigned int start = mesh.getNumVertices();
            num_verts.push_back(len);
            
            // side verts
            mesh.addVertices(l.getVertices());
            vector<ofIndexType> indices;
            
            for (unsigned int i = start; i < start + len - 1; ++i) {
                line_indices.insert(line_indices.end(), {i,i + 1});
                
                triangle_indices.insert(triangle_indices.end(), {i, i + 1, i + 2});
            }
            
            triangle_indices.pop_back();
            triangle_indices.pop_back();
            triangle_indices.pop_back();
        }
    }
    
//    mesh.addIndices(line_indices);
    
    
    calcOffset();
};

void KakkuriText::calcOffset() {
    auto bounding_box = font.getStringBoundingBox(current_text, 0, 0);
    offset = vec3(bounding_box.getWidth(), bounding_box.getHeight(), 0) * .5;
}

void KakkuriText::setPrimitiveMode(const ofPrimitiveMode mode, const bool auto_index) {
    mesh.setMode(mode);
    current_mode = mode;
    
    if (auto_index) {
        switch (mode) {
            case OF_PRIMITIVE_TRIANGLES:
                setIndexMode(KAKKURI_INDEX_TRIANGLE);
                break;
                
            case OF_PRIMITIVE_LINES:
                setIndexMode(KAKKURI_INDEX_LINE);
                break;
            default:
                break;
        }
    }
}

void KakkuriText::setIndexMode(const KakkuriIndexMode mode, vector<ofIndexType> indices) {
    mesh.clearIndices();
    
    switch(mode) {
        case KAKKURI_NO_INDEX:
            mesh.disableIndices();
            break;
            
        case KAKKURI_INDEX_LINE:
            ofLogNotice() << line_indices.size();
            mesh.addIndices(line_indices);
            break;
        case KAKKURI_INDEX_TRIANGLE:
            mesh.addIndices(triangle_indices);
            break;
        case KAKKURI_INDEX_CUSTOM:
            mesh.addIndices(indices);
            break;
    }
}

void KakkuriText::draw() {
    ofPushMatrix();
    ofRotateXDeg(180);
    ofTranslate(-offset);
    mesh.setMode(current_mode);
    mesh.draw();
    
    ofPopMatrix();
};

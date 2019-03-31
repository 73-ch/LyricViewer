#include "TextMesh.h"
TextMesh::TextMesh(ofTrueTypeFont& font_) : font(font_) {
    
}

void TextMesh::setFont(ofTrueTypeFont &font_) {
    font = font_;
    setText(current_text, current_thickness);
}

void TextMesh::setText(const string text, const float thickness) {
    mesh.clear();
    
    current_text = text;
    current_thickness = thickness;
    
    auto font_paths = font.getStringAsPoints(text);
    
    for (auto p : font_paths) {
        p.setStrokeWidth(20);
        
        // front mesh
        mesh.append(p.getTessellation());
        
        // back mesh
        auto back = ofMesh(p.getTessellation());
        for (auto& v : back.getVertices()) v.z = thickness;
        mesh.append(back);
        
        // side
        vector<ofPolyline> outlines = p.getOutline();
        
        for (auto& l : outlines) {
            ofMesh temp;
            // side verts
            temp.addVertices(l.getVertices());
            
            auto temp_verts = l.getVertices();
            for (auto& v : temp_verts) v.z = thickness;
            temp.addVertices(temp_verts);
            
            // side indices
            unsigned int len =temp_verts.size();
            
            for (unsigned int i =0 ; i< len-1; ++i) temp.addIndices({i, i+1, i + len, i +len, i+len+1, i + 1});
            
            mesh.append(temp);
        }
    }
    
    calcOffset();
};

void TextMesh::calcOffset() {
    auto bounding_box = font.getStringBoundingBox(current_text, 0, 0);
    offset = vec3(bounding_box.getWidth(), bounding_box.getHeight(), current_thickness) * .5;
}

void TextMesh::draw(ofPolyRenderMode render_type) {
    ofPushMatrix();
    ofRotateXDeg(180);
    ofTranslate(-offset);
    
    mesh.draw(render_type);
    
    ofPopMatrix();
};

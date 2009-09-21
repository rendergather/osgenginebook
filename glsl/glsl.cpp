/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create states using OpenGL shading language
*/

#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

static const char* vertSource = {
    "varying vec3 normal;\n"
    "void main()\n"
    "{\n"
    "    normal = normalize(gl_NormalMatrix * gl_Normal);\n"
    "    gl_Position = ftransform();\n"
    "}\n"
};

static const char* fragSource = {
    "uniform vec4 mainColor;\n"
    "varying vec3 normal;\n"
    "void main()\n"
    "{\n"
    "    float intensity = dot(vec3(gl_LightSource[0].position), normal);\n"
    "    if (intensity > 0.95) gl_FragColor = mainColor;\n"
    "    else if (intensity > 0.5) gl_FragColor = vec4(0.6,0.3,0.3,1.0);\n"
    "    else if (intensity > 0.25) gl_FragColor = vec4(0.4,0.2,0.2,1.0);\n"
    "    else gl_FragColor = vec4(0.2,0.1,0.1,1.0);\n"
    "}\n"
};

class ColorCallback : public osg::Uniform::Callback
{
public:
    ColorCallback() : _incRed(false) {}
    
    virtual void operator()( osg::Uniform* uniform, osg::NodeVisitor* nv )
    {
        if ( !uniform ) return;
        
        osg::Vec4 color;
        uniform->get( color );
        
        if ( _incRed==true )
        {
            if ( color.x()<1.0 ) color.x() += 0.01;
            else _incRed = false;
        }
        else
        {
            if ( color.x()>0.0 ) color.x() -= 0.01;
            else _incRed = true;
        }
        uniform->set( color );
    }

protected:
    bool _incRed;
};

void createShaders( osg::StateSet& ss )
{
    osg::ref_ptr<osg::Shader> vertShader = new osg::Shader( osg::Shader::VERTEX, vertSource );
    osg::ref_ptr<osg::Shader> fragShader = new osg::Shader( osg::Shader::FRAGMENT, fragSource );
    
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader( vertShader.get() );
    program->addShader( fragShader.get() );
    
    osg::ref_ptr<osg::Uniform> mainColor = new osg::Uniform( "mainColor", osg::Vec4(1.0,0.5,0.5,1.0) );
    mainColor->setUpdateCallback( new ColorCallback );
    
    ss.addUniform( mainColor.get() );
    ss.setAttributeAndModes( program.get() );
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "cow.osg" );
    
    createShaders( *(model->getOrCreateStateSet()) );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( model );
    return viewer.run();
}

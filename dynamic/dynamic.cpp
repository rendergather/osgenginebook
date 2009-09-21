/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a dynamic line
*/

#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

class DynamicLineCallback : public osg::Drawable::UpdateCallback
{
public:
    DynamicLineCallback() : _angle(0.0) {}
    
    virtual void update( osg::NodeVisitor* nv, osg::Drawable* drawable )
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>( drawable );
        if ( !geom ) return;
        
        osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>( geom->getVertexArray() );
        if ( vertices )
        {
            for ( osg::Vec3Array::iterator itr=vertices->begin(); itr!=vertices->end()-1; ++itr )
                itr->set( (*(itr+1)) );
            
            _angle += 1.0 / 10.0;
            osg::Vec3& pt = vertices->back();
            pt.set( 10.0*cos(_angle), 0.0, 10.0*sin(_angle) );
            vertices->dirty();
        }
    }

protected:
    float _angle;
};

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array( 10 );
    for ( unsigned int i=0; i<10; ++i )
        (*vertices)[i].set( float(i), 0.0, 0.0 );
    
    osg::ref_ptr<osg::Geometry> lineGeom = new osg::Geometry;
    lineGeom->setVertexArray( vertices.get() );
    lineGeom->addPrimitiveSet( new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 10) );
    
    lineGeom->setInitialBound( osg::BoundingBox(osg::Vec3(-10.0,-10.0,-10.0), osg::Vec3(10.0,10.0,10.0)) );
    lineGeom->setUpdateCallback( new DynamicLineCallback );
    lineGeom->setUseDisplayList( false );
    lineGeom->setUseVertexBufferObjects( true );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    geode->getOrCreateStateSet()->setAttribute( new osg::LineWidth(2.0) );
    geode->addDrawable( lineGeom.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();
}

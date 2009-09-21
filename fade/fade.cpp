/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create fade in-out animations
*/

#include <osg/BlendFunc>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgAnimation/EaseMotion>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class FadeCallback : public osg::NodeCallback
{
public:
    FadeCallback()
    { _motion = new osgAnimation::InOutCubicMotion; }
    
    virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
    {
        osg::Geode* geode = dynamic_cast<osg::Geode*>( node );
        if ( geode )
        {
            osg::ShapeDrawable* shape =
                dynamic_cast<osg::ShapeDrawable*>( geode->getDrawable(0) );
            if ( shape )
            {
                _motion->update( 0.005 );
                float alpha = _motion->getValue();
                if ( alpha>1.0 ) alpha = 2.0 - alpha;
                
                shape->setColor( osg::Vec4(1.0, 1.0, 1.0, alpha) );
            }
        }
        traverse( node, nv );
    }
    
protected:
    osg::ref_ptr<osgAnimation::InOutCubicMotion> _motion;
};

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::ShapeDrawable> shape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.0, 0.0, 0.0), 1.0) );
    shape->setColor( osg::Vec4(1.0, 1.0, 1.0, 1.0) );
    shape->setSupportsDisplayList( false );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( shape.get() );
    geode->setUpdateCallback( new FadeCallback );
    geode->getOrCreateStateSet()->setAttributeAndModes(
        new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();
}

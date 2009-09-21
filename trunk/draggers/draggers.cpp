/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to manipulate 3D objects with draggers
*/

#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class PickModelHandler : public osgGA::GUIEventHandler
{
public:
    PickModelHandler() : _activeDragger(0) {}
    
    bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor* )
    {
        osgViewer::View* view = dynamic_cast<osgViewer::View*>( &aa );
        if ( !view ) return false;
        
        if ( (ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT)==0 )
            return false;
        
        switch ( ea.getEventType() )
        {
            case osgGA::GUIEventAdapter::PUSH:
            {
                _pointer.reset();
                
                osgUtil::LineSegmentIntersector::Intersections intersections;
                if ( view->computeIntersections(ea.getX(), ea.getY(), intersections) )
                {
                    _pointer.setCamera( view->getCamera() );
                    _pointer.setMousePosition( ea.getX(), ea.getY() );
                    
                    for ( osgUtil::LineSegmentIntersector::Intersections::iterator hitr=intersections.begin();
                          hitr != intersections.end(); ++hitr)
                    {
                        _pointer.addIntersection( hitr->nodePath, hitr->getLocalIntersectPoint() );
                    }
                    
                    for ( osg::NodePath::iterator itr=_pointer._hitList.front().first.begin();
                          itr != _pointer._hitList.front().first.end(); ++itr )
                    {
                        osgManipulator::Dragger* dragger = dynamic_cast<osgManipulator::Dragger*>( *itr );
                        if ( dragger )
                        {
                            dragger->handle( _pointer, ea, aa );
                            _activeDragger = dragger;
                            break;
                        }                   
                    }
                }
                break;
            }
            
            case osgGA::GUIEventAdapter::DRAG:
            case osgGA::GUIEventAdapter::RELEASE:
            {
                if ( _activeDragger )
                {
                    _pointer._hitIter = _pointer._hitList.begin();
                    _pointer.setCamera( view->getCamera() );
                    _pointer.setMousePosition( ea.getX(), ea.getY() );
                    
                    _activeDragger->handle( _pointer, ea, aa );
                }
                
                if ( ea.getEventType()==osgGA::GUIEventAdapter::RELEASE )
                {
                    _activeDragger = NULL;
                    _pointer.reset();
                }
                break;
            }
            
            default:
                break;
        }
        return true;
    }

protected:
    osgManipulator::Dragger* _activeDragger;
    osgManipulator::PointerInfo _pointer;
};

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "cow.osg" );
    
    osg::ref_ptr<osgManipulator::Selection> selection = new osgManipulator::Selection;
    selection->addChild( model );
    
    float scale = model->getBound().radius() * 1.6;
    osg::ref_ptr<osgManipulator::TranslateAxisDragger> dragger = new osgManipulator::TranslateAxisDragger;
    dragger->setupDefaultGeometry();
    dragger->setMatrix( osg::Matrix::scale(scale, scale, scale) *
                        osg::Matrix::translate(model->getBound().center()) );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( dragger.get() );
    root->addChild( selection.get() );
    root->addChild( osgDB::readNodeFile("axes.osg") );
    
    osg::ref_ptr<osgManipulator::CommandManager> manager = new osgManipulator::CommandManager;
    manager->connect( *dragger, *selection );
    
    osgViewer::Viewer viewer;
    viewer.addEventHandler( new PickModelHandler );
    viewer.setSceneData( root.get() );
    return viewer.run();
}

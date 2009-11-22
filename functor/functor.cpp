/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a functor to collect geometry information
*/

#include <osg/io_utils>
#include <osg/TriangleFunctor>
#include <osg/Drawable>
#include <osgDB/ReadFile>
#include <iostream>

class AttributePrinter : public osg::Drawable::AttributeFunctor
{
public:
    typedef osg::Drawable::AttributeType AttributeType;
    inline const char* getTypeName( AttributeType type )
    {
        static const char* typeNames[] =
        {
            "Vertices", "Weights", "Normals", "Colors", "Secondary Colors",
            "Fog Coords", "Attribute 6", "Attribute 7",
            "Texture Coords 0", "Texture Coords 1", "Texture Coords 2",
            "Texture Coordinates 3", "Texture Coords 4", "Texture Coords 5",
            "Texture Coords 6", "Texture Coords 7"
        };
        return typeNames[type];
    }
    
    template<typename T>
    void printInfo( AttributeType type, unsigned int size, T* front )
    {
        std::cout << "*** " << getTypeName(type) << ": " << size << std::endl;
        for ( unsigned int i=0; i<size; ++i )
            std::cout << "(" << *(front+i) << "); ";
        std::cout << std::endl << std::endl;
    }
    
    virtual void apply( AttributeType type, unsigned int size, float* front )
    { printInfo( type, size, front ); }
    
    virtual void apply( AttributeType type, unsigned int size, osg::Vec2* front )
    { printInfo( type, size, front ); }
    
    virtual void apply( AttributeType type, unsigned int size, osg::Vec3* front )
    { printInfo( type, size, front ); }
    
    virtual void apply( AttributeType type, unsigned int size, osg::Vec4* front )
    { printInfo( type, size, front ); }
};

struct TrianglePrinter
{
    TrianglePrinter()
    { std::cout << "*** Triangles ***" << std::endl; }
    
    void operator()( const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, bool ) const
    { std::cout << "(" << v1 << ");(" << v2 << ");(" << v3 << ")" << std::endl; }
};

class FindGeometryVisitor : public osg::NodeVisitor
{
public:
    FindGeometryVisitor() : osg::NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
    
    virtual void apply( osg::Node& node )
    { traverse( node ); }
    
    virtual void apply( osg::Geode& node )
    {
        for ( unsigned int i=0; i<node.getNumDrawables(); ++i )
        {
            osg::Drawable* drawable = node.getDrawable( i );
            if ( !drawable ) continue;
            std::cout << "[" << drawable->libraryName() << "::" << drawable->className() << "]" << std::endl;
            
            AttributePrinter attrPrinter;
            drawable->accept( attrPrinter );
            
            osg::TriangleFunctor<TrianglePrinter> triPrinter;
            drawable->accept( triPrinter );
            
            std::cout << std::endl;
        }
        traverse( node );
    }
};

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "house.ive" );
    
    FindGeometryVisitor fgv;
    if ( model ) model->accept( fgv );
    return 0;
}

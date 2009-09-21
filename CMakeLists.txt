# Copyright (C) 2009 by Wang Rui <wangray84 at gmail dot com>
# OpenSceneGraph Engine Book - Design and Implementation

PROJECT( osgEngineBook )

CMAKE_MINIMUM_REQUIRED( VERSION 2.4.7 )

IF( COMMAND CMAKE_POLICY )
    CMAKE_POLICY( SET CMP0003 NEW )
ENDIF( COMMAND CMAKE_POLICY )

SET( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}" )
SET( CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows" )

FIND_PACKAGE( OpenGL )
FIND_PACKAGE( OpenThreads )
FIND_PACKAGE( osg )
FIND_PACKAGE( osgAnimation )
FIND_PACKAGE( osgDB )
FIND_PACKAGE( osgFX )
FIND_PACKAGE( osgGA )
FIND_PACKAGE( osgIntrospection )
FIND_PACKAGE( osgManipulator )
FIND_PACKAGE( osgParticle )
FIND_PACKAGE( osgShadow )
FIND_PACKAGE( osgSim )
FIND_PACKAGE( osgTerrain )
FIND_PACKAGE( osgText )
FIND_PACKAGE( osgUtil )
FIND_PACKAGE( osgViewer )
FIND_PACKAGE( osgVolume )
FIND_PACKAGE( osgWidget )

IF( WIN32 )
    IF( MSVC )
        ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
        ADD_DEFINITIONS( -D_CRT_SECURE_NO_DEPRECATE )
    ENDIF( MSVC )
ENDIF( WIN32 )

INCLUDE( CustomModules )

ADD_SUBDIRECTORY( simplest )

ADD_SUBDIRECTORY( refptr )

ADD_SUBDIRECTORY( visitor )
ADD_SUBDIRECTORY( callback )
ADD_SUBDIRECTORY( transform )
ADD_SUBDIRECTORY( switch )
ADD_SUBDIRECTORY( lod )
ADD_SUBDIRECTORY( proxy )

ADD_SUBDIRECTORY( house )
ADD_SUBDIRECTORY( dynamic )
ADD_SUBDIRECTORY( functor )
ADD_SUBDIRECTORY( bitmap )
ADD_SUBDIRECTORY( texts )

ADD_SUBDIRECTORY( textures )
ADD_SUBDIRECTORY( mipmaps )
ADD_SUBDIRECTORY( statecallback )
ADD_SUBDIRECTORY( glsl )

ADD_SUBDIRECTORY( birdseye )
ADD_SUBDIRECTORY( rtt )
ADD_SUBDIRECTORY( multiwindows )
ADD_SUBDIRECTORY( viewers )

ADD_SUBDIRECTORY( keyboard )
ADD_SUBDIRECTORY( draggers )
ADD_SUBDIRECTORY( gui )

ADD_SUBDIRECTORY( keyframe )
ADD_SUBDIRECTORY( path )
ADD_SUBDIRECTORY( multichannels )
ADD_SUBDIRECTORY( skeleton )
ADD_SUBDIRECTORY( morph )
ADD_SUBDIRECTORY( fade )
ADD_SUBDIRECTORY( texturemovie )

ADD_SUBDIRECTORY( simpleplugin )
ADD_SUBDIRECTORY( progress )

ADD_SUBDIRECTORY( pagedlod )

ADD_SUBDIRECTORY( thread )

ADD_SUBDIRECTORY( data )

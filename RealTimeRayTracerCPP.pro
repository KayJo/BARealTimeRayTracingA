#-------------------------------------------------
#
# Project created by QtCreator 2013-08-12T10:30:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RealTimeRayTracerCPP
TEMPLATE = app


SOURCES += main.cpp \
    geometry.cpp \
    ray.cpp \
    plane.cpp \
    sphere.cpp \
    camera.cpp \
    pinholecam.cpp \
    viewplane.cpp \
    shaderec.cpp \
    light.cpp \
    ambient.cpp \
    directional.cpp \
    pointlight.cpp \
    sampler.cpp \
    regularsampler.cpp \
    brdf.cpp \
    lambertian.cpp \
    glossyspecular.cpp \
    perfectspecular.cpp \
    btdf.cpp \
    perfecttransmitter.cpp \
    material.cpp \
    phong.cpp \
    transparent.cpp \
    reflective.cpp \
    raytracer.cpp \
    whittedtracer.cpp \
    world.cpp \
    rgb.cpp

HEADERS  += \
    geometry.h \
    ray.h \
    plane.h \
    sphere.h \
    camera.h \
    pinholecam.h \
    viewplane.h \
    shaderec.h \
    light.h \
    ambient.h \
    directional.h \
    pointlight.h \
    sampler.h \
    regularsampler.h \
    brdf.h \
    lambertian.h \
    glossyspecular.h \
    perfectspecular.h \
    btdf.h \
    perfecttransmitter.h \
    material.h \
    phong.h \
    transparent.h \
    reflective.h \
    raytracer.h \
    whittedtracer.h \
    world.h \
    constants.h \
    rgb.h

FORMS    +=

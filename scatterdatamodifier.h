#ifndef SCATTERDATAMODIFIER_H
#define SCATTERDATAMODIFIER_H

#include <QtDataVisualization>
#include <QtGui>
#include <QtWidgets>
#include <QtCore/qmath.h>
#include <QObject>
#include <QSpinBox>
#include <QDoubleSpinBox>

using namespace QtDataVisualization;

class ScatterDataModifier : public QObject
{
    Q_OBJECT
public:
    explicit ScatterDataModifier(Q3DScatter *scatter);
    ~ScatterDataModifier();

    void addData();
    void changePresetCamera();
    void changeAngle(const int &__agle);
    void changeInduction(const double &__induction);
    void changeSpeed(const double &__speed);
    void addInfo() const;

private:
    Q3DScatter *m_graph;
    double m_angle, m_induction, m_speed;
    const double el_mass = 9.11 / pow(10, 31);
    const double el_charge = 1.6 / pow(10, 19);
};

#endif

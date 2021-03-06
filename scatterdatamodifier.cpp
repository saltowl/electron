#include "scatterdatamodifier.h"

using namespace QtDataVisualization;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter) : m_graph(scatter)
{
    m_graph->activeTheme()->setType(Q3DTheme::ThemeStoneMoss);

    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(40.0f);
    m_graph->activeTheme()->setFont(font);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    QScatterDataProxy *proxy = new QScatterDataProxy;
    QScatter3DSeries *series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat(QStringLiteral("X: @xLabel*10⁻³ м, Y: @yLabel*10⁻³ м, Z: @zLabel*10⁻² м"));
    series->setMeshSmooth(true);
    series->setMesh(QAbstract3DSeries::MeshSphere);
    series->setItemSize(0.1f);
    m_graph->addSeries(series);
}

ScatterDataModifier::~ScatterDataModifier()
{
    delete m_graph;
}

void ScatterDataModifier::addData()
{
    m_graph->axisX()->setTitle("X, *10⁻³");
    m_graph->axisY()->setTitle("Y, *10⁻³");
    m_graph->axisZ()->setTitle("Z, *10⁻²");
    m_graph->axisX()->setTitleVisible(true);
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisZ()->setTitleVisible(true);

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(1000);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    double m_radius = (el_mass * m_speed * qSin(m_angle)) / (el_charge * m_induction);
    double m_move = (m_speed * qCos(m_angle) * el_mass) / (el_charge * m_induction);

    for (float i = 0; i < 100; i += 0.1)
    {
        ptrToDataArray->setPosition(QVector3D(m_radius * qCos(i) * 1000, m_radius * qSin(i) * 1000,
                                              m_move * i * 100));
        ptrToDataArray++;
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    radius->setText(QString::number(m_radius) + " м");
    step->setText(QString::number(m_move) + " м");
}

void ScatterDataModifier::changePresetCamera()
{
    static int preset = Q3DCamera::CameraPresetFrontLow;

    m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

    if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
        preset = Q3DCamera::CameraPresetFrontLow;
}

void ScatterDataModifier::changeAngle(const int &__angle)
{
    if (__angle == 180 || __angle == 360)
        this->m_angle = 0;
    else this->m_angle = __angle;
    m_angle = qDegreesToRadians((float)m_angle);
}

void ScatterDataModifier::changeInduction(const double &__induction)
{
    this->m_induction = __induction / pow(10, 4);
}

void ScatterDataModifier::changeSpeed(const double &__speed)
{
    this->m_speed = __speed * pow(10, 6);
}

void ScatterDataModifier::addInfo() const
{
    QString text = "Данная программа моделирует траекторию электрона, \n"
                   "движущегося в однородном магнитном поле. \n\n\n"
                   "Для того, чтобы изменить положение камеры, вы можете\n"
                   "использовать правую кнопку мыши, для уменьшения/уве-\n"
                   "личения изображения - колесико мыши (или специальные\n"
                   "жесты тачпада). Также, для смены положения камеры, вы\n"
                   "можете воспользоваться кнопкой, расположенной справа.\n\n\n"
                   "Автор: студент М3206 Шакирова Владислава.";
    QMessageBox::information(0, "Справка", text);
}

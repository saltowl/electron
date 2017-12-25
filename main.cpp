#include "scatterdatamodifier.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    widget->setWindowTitle(QStringLiteral("Траектория электрона в однородном магнитном поле"));
    //widget->setWindowIcon(QIcon(":/img/icon.png"));

    const double c_angle = 60,
                 c_induction = 25.3,
                 c_speed = 1.5;

    QPushButton *cameraButton = new QPushButton(widget);
    cameraButton->setText(QStringLiteral("Изменить положение камеры"));

    QSpinBox *angle = new QSpinBox(widget);
    angle->setRange(0, 360);
    angle->setValue(c_angle);
    angle->setSuffix(" °");

    QDoubleSpinBox *induction = new QDoubleSpinBox(widget);
    induction->setValue(c_induction);
    induction->setSuffix(" * 10⁻⁴ Тл");

    QDoubleSpinBox *speed = new QDoubleSpinBox(widget);
    speed->setValue(c_speed);
    speed->setSuffix(" * 10⁶ м/с");

    QPushButton *go = new QPushButton(widget);
    go->setText(QStringLiteral("Построить!"));

    vLayout->addWidget(cameraButton, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("")));
    vLayout->addWidget(new QLabel(QStringLiteral("Угол между направлениями скорости")));
    vLayout->addWidget(new QLabel(QStringLiteral("и магнитной индукции")));
    vLayout->addWidget(angle, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("Магнитная индукцию")));
    vLayout->addWidget(induction, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("Скорость электрона")));
    vLayout->addWidget(speed, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("")));
    vLayout->addWidget(go, 1, Qt::AlignTop);

    ScatterDataModifier *modifier = new ScatterDataModifier(graph);
    modifier->changeAngle(c_angle);
    modifier->changeInduction(c_induction);
    modifier->changeSpeed(c_speed);
    modifier->addData();

    QObject::connect(cameraButton, &QPushButton::clicked,
                     modifier, &ScatterDataModifier::changePresetCamera);
    QObject::connect(angle, QOverload<int>::of(&QSpinBox::valueChanged),
                     modifier, &ScatterDataModifier::changeAngle);
    QObject::connect(induction, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                     modifier, &ScatterDataModifier::changeInduction);
    QObject::connect(speed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                     modifier, &ScatterDataModifier::changeSpeed);
    QObject::connect(go, &QPushButton::clicked,
                     modifier, &ScatterDataModifier::addData);
    widget->show();
    return app.exec();
}

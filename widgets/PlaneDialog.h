#pragma once

#include <core/domain/Plane.h>

#include <QDialog>

namespace Ui {
class PlaneDialog;
}

class PlaneDialog : public QDialog {
    Q_OBJECT

public:
    explicit PlaneDialog( domain::PlanePtr plane, QWidget* parent = nullptr );
    ~PlaneDialog() override;

    void accept() override;

private:
    Ui::PlaneDialog* ui;
    domain::PlanePtr plane_;
};

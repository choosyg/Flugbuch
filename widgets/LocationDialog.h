#pragma once

#include <core/domain/Location.h>

#include <QDialog>

namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog {
    Q_OBJECT

public:
    explicit LocationDialog( domain::LocationPtr loc, QWidget* parent = nullptr );
    ~LocationDialog() override;

    void accept() override;

private:
    Ui::LocationDialog* ui;

    domain::LocationPtr loc_;
};

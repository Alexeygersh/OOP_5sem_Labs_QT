#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include "Player.h"
#include <memory>

namespace Ui {
class PlayerDialog;
}

//наслед QDialog
class PlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = nullptr);
    ~PlayerDialog();

public slots:
    void onAddPlayerButtonClicked();

signals:
    void playerAdded(const std::shared_ptr<Player>& player);

// protected:
//     void closeEvent(QCloseEvent *event) override;

private:
    Ui::PlayerDialog *ui;
    std::shared_ptr<Player> createPlayerFromInputs();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // PLAYERDIALOG_H


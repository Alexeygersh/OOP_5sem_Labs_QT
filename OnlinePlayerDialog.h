#ifndef ONLINEPLAYERDIALOG_H
#define ONLINEPLAYERDIALOG_H

#include <QDialog>
#include "OnlinePlayer.h"
#include <memory>

namespace Ui {
class OnlinePlayerDialog;
}

class OnlinePlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit OnlinePlayerDialog(QWidget *parent = nullptr);
    ~OnlinePlayerDialog();

public slots:
    void onAddPlayerButtonClicked();

signals:
    void onlinePlayerAdded(const std::shared_ptr<OnlinePlayer>& onlinePlayer); // Сигнал для добавления игрока

private:
    Ui::OnlinePlayerDialog *ui;
    std::shared_ptr<OnlinePlayer> createPlayerFromInputs();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // ONLINEPLAYERDIALOG_H

